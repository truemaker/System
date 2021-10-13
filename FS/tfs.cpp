// This is a own File System

uint8 file_type_file = 0;
uint8 file_type_device = 1;

struct File_Descriptor {
    uint8* sector;
    uint8* pos_in_sector;
    uint8* size;
    uint8* name;
    uint8* type;
};

File_Descriptor* file_descriptors = (File_Descriptor*)kmalloc(255);
int file_index = 0;
uint8 current_sector = 0;
uint8 current_pos_in_sector = 0;

File_Descriptor* tfs_mkfile(uint8 *path, uint8 size) {
    file_descriptors[file_index] = *((File_Descriptor*)kmalloc(5));
    file_descriptors[file_index].sector = &current_sector;
    file_descriptors[file_index].pos_in_sector = &current_pos_in_sector;
    file_descriptors[file_index].size = &size;
    file_descriptors[file_index].name = path;
    file_descriptors[file_index].type = &file_type_file;
    File_Descriptor* fd = &file_descriptors[file_index];
    current_sector++;
    current_pos_in_sector = 0;
    file_index++;
    return fd;
}

File_Descriptor* tfs_mkdevice(uint8* path, uint8 size) {
    file_descriptors[file_index] = *((File_Descriptor*)kmalloc(5));
    file_descriptors[file_index].sector = &current_sector;
    file_descriptors[file_index].pos_in_sector = &current_pos_in_sector;
    file_descriptors[file_index].size = &size;
    file_descriptors[file_index].name = path;
    file_descriptors[file_index].type = &file_type_device;
    File_Descriptor* fd = &file_descriptors[file_index];
    current_sector++;
    current_pos_in_sector = 0;
    file_index++;
    return fd;
}

uint8* tfs_read_file(File_Descriptor fd) {
    if (*fd.type == file_type_device) {
        if (fd.name == (uint8*)"/dev/null") {
            memrec();
            uint8* zeros = (uint8*)kmalloc(512);
            memset(zeros, 0, 512);
            memunrec();
            return zeros;
        }
    }
    return ram_read_sector(*fd.sector);
}

void tfs_write_file(File_Descriptor fd, uint8* buf) {
    ram_write_sector(*fd.sector,buf);
} 
