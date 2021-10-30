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
#include "FS/tfs.cpp"

#include "CPU/syscall.cpp"
uint16 shell_pos = 0;
void hello() {
    print_str((uint8*)"Hello\n");
}

#include "UserMode/user_mode.cpp"

}

void init() {
    cpuid(0x01, &eax, &ebx, &ecx, &edx);
    setup_devices();
    setup_tty();
    tty_set(0);
    tty_clear();
    set_cursor_pos(-1);
    disable_input();
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
    tty_out((char*)"Initializing Dynamic Memory");
    print_raw(tty_buffer);
    initializeMem();
    tty_set_pos(((*tty_pos / 80) * 80) + 80 - 5);
    tty_color_out((char*)"[OK]\n", 0x0A, 0x00);
    asm volatile("sti");
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
    sleep(1);
    enable_input();
    set_cursor_pos(0);
    tty_set_pos(((*tty_pos / 80) * 80) + 80 - 5);
    tty_color_out((char*)"[OK]\n", 0x0A, 0x00);
    print_raw(tty_buffer);
    tty_out((char*)"Starting Init\n");
    print_raw(tty_buffer);
    sleep(1);
    setup_user_mode();
    tty_set_pos(((*tty_pos / 80) * 80) + 80 - 5);
    tty_color_out((char*)"[OK]\n", 0x0A, 0x00);
    print_raw(tty_buffer);
    set_cursor_pos(0);
    start_user_mode();
    shell_pos = *tty_pos;
}

extern "C" void kernel_loop() {
    static char kernel_killed = 0;
    if (kernel_killed == 1) {
        kpanic((uint8*)"Critical Process died", 0x00);
    }
}

extern "C" void main(){
    init();
    for (;;) {}
}
