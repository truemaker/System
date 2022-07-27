char kill_flag = 0;
#define STATIC_MEMORY_ALLOCATOR

extern "C" {
// Defines
#include "Defines/mouse_and_keyboard.cpp"

// Types
#include "Utils/types.cpp"

// Graphics
#include "UserMode/Libraries/graphics.h"

// IncBins
#include "IncBins/incbins.cpp"

// Memory
#include "Memory/mem.cpp"

// Utils
#include "Utils/num.cpp"
#include "Utils/convert.cpp"
#include "Utils/str.cpp"

// Informations
uint32 eax = 0;
uint32 ebx = 0;
uint32 ecx = 0;
uint32 edx = 0;
uint8 user_mode = 0x00;

// Interaction
#include "Interaction/ports.cpp"

#include "UserMode/Libraries/input.cpp"

// Drivers
#include "Drivers/vga.cpp"
#include "Drivers/keyboard.cpp"
//#include "Drivers/disk.cpp"

// Fallback system
#include "Fallback/kernel.cpp"

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

void kernel_exit() {
    clear_color(0x00);
    print_colored_str("Shutting down...", 0x0F, 0x00);
    asm("cli");
    outw(0x604, 0x2000);
    asm("hlt");
}

// Input
#include "Input/keyboard.cpp"

// File system
//#include "FS/tfs.cpp"

#include "CPU/syscall.cpp"
void hello() {
    print_str((uint8*)"Hello\n");
}

#include "UserMode/user_mode.cpp"
}

void init() {
    cpuid(0x01, &eax, &ebx, &ecx, &edx);
    initializeMem();
    //init_dynamic_mem();
    //setup_devices();
    setup_tty();
    tty_set(0);
    tty_clear();
    set_cursor_pos(-1);
    disable_input();
    tty_out((char*)"MyOS Kernel v0.1\n");
    print_raw(tty_buffer);
    tty_out((char*)"Initializing Interrupt Descriptor Table");
    print_raw(tty_buffer);
    idt_install();
    tty_set_pos(((*tty_pos / 80) * 80) + 80 - 5);
    tty_color_out((char*)"[OK]\n", 0x0A, 0x00);
    tty_out((char*)"Initializing Interrupt Service(s)");
    print_raw(tty_buffer);
	isrs_install();
    tty_set_pos(((*tty_pos / 80) * 80) + 80 - 5);
    tty_color_out((char*)"[OK]\n", 0x0A, 0x00);
    tty_out((char*)"Initializing Interrupt Request Handler(s)");
    print_raw(tty_buffer);
    irq_install();
    tty_set_pos(((*tty_pos / 80) * 80) + 80 - 5);
    tty_color_out((char*)"[OK]\n", 0x0A, 0x00);
    tty_out((char*)"Enabling Interrupt Requests");
    print_raw(tty_buffer);
    asm volatile("sti");
    tty_set_pos(((*tty_pos / 80) * 80) + 80 - 5);
    tty_color_out((char*)"[OK]\n", 0x0A, 0x00);
    tty_out((char*)"Installing Interrupt Request Handler for Timer");
    print_raw(tty_buffer);
    timer_install();
    tty_set_pos(((*tty_pos / 80) * 80) + 80 - 5);
    tty_color_out((char*)"[OK]\n", 0x0A, 0x00);
    tty_out((char*)"Installing Interrupt Request Handler for Keyboard");
    print_raw(tty_buffer);
    kb_install();
    tty_set_pos(((*tty_pos / 80) * 80) + 80 - 5);
    tty_color_out((char*)"[OK]\n", 0x0A, 0x00);
    print_raw(tty_buffer);
    tty_out((char*)"Installing Interrupt Request Handler for Syscall");
    print_raw(tty_buffer);
    sys_init();
    tty_set_pos(((*tty_pos / 80) * 80) + 80 - 5);
    tty_color_out((char*)"[OK]\n", 0x0A, 0x00);
    print_raw(tty_buffer);
    tty_out((char*)"Finishing Kernel Init...");
    print_raw(tty_buffer);
    enable_input();
    set_cursor_pos(0);
    tty_set_pos(((*tty_pos / 80) * 80) + 80 - 5);
    tty_color_out((char*)"[OK]\n", 0x0A, 0x00);
    tty_out((char*)"Welcome to MyOS\n");
    print_raw(tty_buffer);
    
    tty_out((char*)"Starting Init");
    print_raw(tty_buffer);
    setup_user_mode();
    set_cursor_pos(0);
    int i = 10/0;
    start_user_mode();
    
    // Fix my Error
    /*asm("cli");
    asm("hlt");*/
}

extern "C" void kernel_loop() {
    static char kernel_killed = 0;
    if (kernel_killed == 1) {
        kpanic((uint8*)"Critical Process died", 0x00);
    }
}

extern "C" void main() {
    init();
}