char kill_flag = 0;

extern "C" {

// IncBins
#include "IncBins/incbins.cpp"

// Memory
#include "Memory/mem.cpp"

// Utils
#include "Utils/types.cpp"
#include "Utils/num.cpp"
#include "Utils/convert.cpp"
#include "Utils/str.cpp"

// Informations
uint32 eax = 0;
uint32 ebx = 0;
uint32 ecx = 0;
uint32 edx = 0;

// Interaction
#include "Interaction/ports.cpp"

// Drivers
#include "Drivers/vga.cpp"
#include "Drivers/keyboard.cpp"
#include "Drivers/disk.cpp"

// BSOD
#include "Utils/bsod.cpp"

// TTY
#include "TTY/tty.cpp"

// CPU
#include "CPU/cpuid.cpp"
#include "CPU/idt.cpp"
#include "CPU/isr.cpp"
#include "CPU/irq.cpp"
#include "CPU/timer.cpp"
#include "CPU/syscall.cpp"

// Input
#include "Input/keyboard.cpp"

// File system
#include "FS/tfs.cpp"

void hello() {
    print_str((uint8*)"Hello\n");
}
}

void init() {
    cpuid(0x01, &eax, &ebx, &ecx, &edx);
    setup_devices();
    setup_tty();
    tty_set(0);
    tty_clear();
    set_cursor_pos(-1);
    disable_input();
    tty_out((char*)"Initializing Interrupt Descriptor Table...");
    print_raw(tty_buffer);
    idt_install();
    tty_color_out((char*)"OK\n", 0x0A, 0x00);
    tty_out((char*)"Initializing Interrupt Service(s)...");
    print_raw(tty_buffer);
	isrs_install();
    tty_color_out((char*)"OK\n", 0x0A, 0x00);
    tty_out((char*)"Initializing Interrupt Request Handler(s)...");
    print_raw(tty_buffer);
    irq_install();
    tty_color_out((char*)"OK\n", 0x0A, 0x00);
    tty_out((char*)"Initializing Dynamic Memory...");
    print_raw(tty_buffer);
    initializeMem();
    tty_color_out((char*)"OK\n", 0x0A, 0x00);
    asm volatile("sti");
    tty_out((char*)"Installing Interrupt Request Handler for Timer...");
    print_raw(tty_buffer);
    timer_install();
    tty_color_out((char*)"OK\n", 0x0A, 0x00);
    tty_out((char*)"Installing Interrupt Request Handler for Keyboard...");
    print_raw(tty_buffer);
    kb_install();
    tty_color_out((char*)"OK\n", 0x0A, 0x00);
    print_raw(tty_buffer);
    tty_out((char*)"Installing Interrupt Request Handler for Syscall...");
    print_raw(tty_buffer);
    sys_init();
    tty_color_out((char*)"OK\n", 0x0A, 0x00);
    print_raw(tty_buffer);
    sleep(1);
    enable_input();
    set_cursor_pos(0);
}

extern "C" void main(){
    init();
    tty_set(1);
    tty_clear_color(0x08);
    tty_color_out((char*)"Hi this is tty1 with a grey background\n", 0x0F, 0x08);
    print_raw(tty_buffer);
    sleep(1);
    tty_set(2);
    tty_out((char*)"Hi this is tty2\n");
    print_raw(tty_buffer);
    sleep(1);
    tty_set(3);
    tty_out((char*)"Hi this is tty3\n");
    print_raw(tty_buffer);
    sleep(1);
    tty_set(4);
    tty_out((char*)"Hi this is tty4\n");
    print_raw(tty_buffer);
    sleep(1);
    tty_set(5);
    tty_out((char*)"Hi this is tty5\n");
    print_raw(tty_buffer);
    sleep(1);
    tty_set(6);
    tty_out((char*)"Hi this is tty6\n");
    print_raw(tty_buffer);
    sleep(1);
    tty_set(7);
    tty_out((char*)"Hi this is tty7\n");
    print_raw(tty_buffer);
    sleep(1);
    tty_set(0);
    print_raw(tty_buffer);
    clear();
    print_colored_str((char*)"Im Green in the front and red in the back", 0x0A, 0x0C);
    File_Descriptor* fd = tfs_mkfile((uint8*)"/hello.txt", (uint8)5);
    uint8* buf = ram_get_sector(*fd->sector); // tfs_read_file(*fd);
    buf[0] = 'H';
    buf[1] = 'e';
    buf[2] = 'l';
    buf[3] = 'l';
    buf[4] = 'o';
    tfs_write_file(*fd, buf);
    next_line();
    print_str(fd->name);
    next_line();
    print_str(tfs_read_file(*fd));
    File_Descriptor* fd2 = tfs_mkfile((uint8*)"/files/bye.txt", (uint8)3);
    uint8* buf2 = ram_get_sector(*fd->sector); // tfs_read_file(*fd);
    buf2[0] = 'B';
    buf2[1] = 'y';
    buf2[2] = 'e';
    tfs_write_file(*fd2, buf2);
    next_line();
    print_str(fd2->name);
    next_line();
    print_str(tfs_read_file(*fd2));
    print_str(tfs_read_file(*devnull));
    next_line();
    print_binary(eax);
    next_line();
    print_binary(ebx);
    next_line();
    print_binary(ecx);
    next_line();
    print_binary(edx);
    return;
}
