// This is a own File System

struct File_Descriptor {
    uint8* sector;
    uint8* pos_in_sector;
    uint8* size;
    uint8* name;
};

File_Descriptor* file_descriptors = (File_Descriptor*)kmalloc(255);
int file_index = 0;
uint8 current_sector = 0;
uint8 current_pos_in_sector = 0;

File_Descriptor* tfs_mkfile(uint8 *path, uint8 size) {
    file_descriptors[file_index] = *((File_Descriptor*)kmalloc(4));
    file_descriptors[file_index].sector = &current_sector;
    file_descriptors[file_index].pos_in_sector = &current_pos_in_sector;
    file_descriptors[file_index].size = &size;
    file_descriptors[file_index].name = path;
    File_Descriptor* fd = &file_descriptors[file_index];
    current_sector++;
    current_pos_in_sector = 0;
    file_index++;
    return fd;
}

uint8* tfs_read_file(File_Descriptor fd) {
    return ram_read_sector(*fd.sector);
}

void tfs_write_file(File_Descriptor fd, uint8* buf) {
    ram_write_sector(*fd.sector,buf);
} 
