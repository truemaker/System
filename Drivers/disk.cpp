// RAM Disk
// Very simple implementation of a RAM disk

uint8* ram_disk = (uint8*) kmalloc(512 * 255 * 2);

uint8* ram_read_sector(uint8 sector) {
    uint8* sector_ret = (uint8*)kmalloc(512);
    for (uint16 i = 0; i < 512; i++) {
        sector_ret[i] = ram_disk[sector * 512 + i];
    } 
    return sector_ret;
}

uint8* ram_get_sector(uint8 sector) {
    return &ram_disk[sector * 512];
}

void ram_write_sector(uint8 sector, uint8* sector_write) {
    for (uint16 i = 0; i < 512; i++) {
        ram_disk[sector * 512 + i] = sector_write[i];
    }
}
