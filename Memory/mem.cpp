void* memset(void* dest, unsigned char val, int count){ 
	unsigned char* destC = (unsigned char*)dest;
	int i;
	for (i = 0; i < count; i++)
		destC[i] = val;
	return dest;
}

/* Copy blocks of memory */
void memcp(unsigned char* source, unsigned char* dest, int count){
    for (int i = 0; i < count; i++)
        *(dest + i) = *(source + i);
}
#ifdef STATIC_MEMORY_ALLOCATOR
#define FREE_MEM 0x10000;
#define MAX_MEM 0xff



int freeMem = FREE_MEM;

void initializeMem(){
    freeMem = FREE_MEM;
}

/* allocate space linearly, starting from address 0x10000 */
void* kmalloc(int size){
    memset((void*)freeMem, 0, size); 
    void* address = (void*)freeMem;
    freeMem += size;
    if (freeMem > MAX_MEM) {
        kill_flag = 1;
    }
    return address;
}
/* "free" last bytes of memory */
void memcut(int size) {freeMem -= size;}

/* free the whole dynamic memory */
void memreset(){freeMem = FREE_MEM;}


/* the following two functions can be called at the beginning and end of a function; they implement a sort of "scoping" for dynamic memory, that makes the whole system a bit less shit */
int tmpMem;
void memrec(){
    tmpMem = freeMem;
}

void memunrec(){
    freeMem = tmpMem;
}

int getFreeMem(){
   return freeMem; 
}
#else
typedef struct dynamic_mem_node {
    uint32 size;
    bool used;
    struct dynamic_mem_node *next;
    struct dynamic_mem_node *prev;
} dynamic_mem_node_t;

#define NULL_POINTER ((void*)0)
#define DYNAMIC_MEM_TOTAL_SIZE 4*1024
#define DYNAMIC_MEM_NODE_SIZE sizeof(dynamic_mem_node_t) // 16

static uint8 dynamic_mem_area[DYNAMIC_MEM_TOTAL_SIZE];
static dynamic_mem_node_t *dynamic_mem_start;

void init_dynamic_mem() {
    dynamic_mem_start = (dynamic_mem_node_t *) dynamic_mem_area;
    dynamic_mem_start->size = DYNAMIC_MEM_TOTAL_SIZE - DYNAMIC_MEM_NODE_SIZE;
    dynamic_mem_start->next = (dynamic_mem_node_t*)(NULL_POINTER);
    dynamic_mem_start->prev = (dynamic_mem_node_t*)(NULL_POINTER);
}

void *find_best_mem_block(dynamic_mem_node_t *dynamic_mem, int size) {
    // initialize the result pointer with NULL and an invalid block size
    dynamic_mem_node_t *best_mem_block = (dynamic_mem_node_t *) NULL_POINTER;
    uint32 best_mem_block_size = DYNAMIC_MEM_TOTAL_SIZE + 1;

    // start looking for the best (smallest unused) block at the beginning
    dynamic_mem_node_t *current_mem_block = dynamic_mem;
    while (current_mem_block) {
        // check if block can be used and is smaller than current best
        if ((!current_mem_block->used) &&
            (current_mem_block->size >= (size + DYNAMIC_MEM_NODE_SIZE)) &&
            (current_mem_block->size <= best_mem_block_size)) {
            // update best block
            best_mem_block = current_mem_block;
            best_mem_block_size = current_mem_block->size;
        }

        // move to next block
        current_mem_block = current_mem_block->next;
    }
    return best_mem_block;
}

void* kmalloc(int size) {
    dynamic_mem_node_t *best_mem_block =
            (dynamic_mem_node_t *) find_best_mem_block(dynamic_mem_start, size);

    // check if we actually found a matching (free, large enough) block
    if (best_mem_block != (dynamic_mem_node_t*)(NULL_POINTER)) {
        // subtract newly allocated memory (incl. size of the mem node) from selected block
        best_mem_block->size = best_mem_block->size - size - DYNAMIC_MEM_NODE_SIZE;

        // create new mem node after selected node, effectively splitting the memory region
        dynamic_mem_node_t *mem_node_allocate = (dynamic_mem_node_t *) (((uint8 *) best_mem_block) +
                                                                        DYNAMIC_MEM_NODE_SIZE +
                                                                        best_mem_block->size);
        mem_node_allocate->size = size;
        mem_node_allocate->used = true;
        mem_node_allocate->next = best_mem_block->next;
        mem_node_allocate->prev = best_mem_block;

        // reconnect the doubly linked list
        if (best_mem_block->next != (dynamic_mem_node_t*)(NULL_POINTER)) {
            best_mem_block->next->prev = mem_node_allocate;
        }
        best_mem_block->next = mem_node_allocate;

        // return pointer to newly allocated memory (right after the new list node)
        return (void *) ((uint8 *) mem_node_allocate + DYNAMIC_MEM_NODE_SIZE);
    }

    return (dynamic_mem_node_t*)(NULL_POINTER);
}

void *merge_next_node_into_current(dynamic_mem_node_t *current_mem_node) {
    dynamic_mem_node_t *next_mem_node = current_mem_node->next;
    if (next_mem_node != (dynamic_mem_node_t*)(NULL_POINTER) && !next_mem_node->used) {
        // add size of next block to current block
        current_mem_node->size += current_mem_node->next->size;
        current_mem_node->size += DYNAMIC_MEM_NODE_SIZE;

        // remove next block from list
        current_mem_node->next = current_mem_node->next->next;
        if (current_mem_node->next != (dynamic_mem_node_t*)(NULL_POINTER)) {
            current_mem_node->next->prev = current_mem_node;
        }
    }
    return current_mem_node;
}

void *merge_current_node_into_previous(dynamic_mem_node_t *current_mem_node) {
    dynamic_mem_node_t *prev_mem_node = current_mem_node->prev;
    if (prev_mem_node != NULL_POINTER && !prev_mem_node->used) {
        // add size of previous block to current block
        prev_mem_node->size += current_mem_node->size;
        prev_mem_node->size += DYNAMIC_MEM_NODE_SIZE;

        // remove current node from list
        prev_mem_node->next = current_mem_node->next;
        if (current_mem_node->next != (dynamic_mem_node_t*)(NULL_POINTER)) {
            current_mem_node->next->prev = prev_mem_node;
        }
    }
    return NULL_POINTER;
}


void memcut(void *p) {
    // move along, nothing to free here
    if (p == (dynamic_mem_node_t*)(NULL_POINTER)) {
        return;
    }

    // get mem node associated with pointer
    dynamic_mem_node_t *current_mem_node = (dynamic_mem_node_t *) ((uint8 *) p - DYNAMIC_MEM_NODE_SIZE);

    // pointer we're trying to free was not dynamically allocated it seems
    if (current_mem_node == (dynamic_mem_node_t*)(NULL_POINTER)) {
        return;
    }

    // mark block as unused
    current_mem_node->used = false;

    // merge unused blocks
    current_mem_node = (dynamic_mem_node_t*)merge_next_node_into_current(current_mem_node);
    merge_current_node_into_previous(current_mem_node);
}
#endif