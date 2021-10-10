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

// Interaction
#include "Interaction/ports.cpp"

// Drivers
#include "Drivers/vga.cpp"
#include "Drivers/keyboard.cpp"

// TTY
#include "TTY/tty.cpp"

// CPU
#include "CPU/idt.cpp"
#include "CPU/isr.cpp"
#include "CPU/irq.cpp"
#include "CPU/timer.cpp"

// Input
#include "Input/keyboard.cpp"

void hello() {
    print_str((char*)"Hello\n");
}
}

void init() {
    tty_set(0);
    set_cursor_pos(-1);
    disable_input();
    tty_out((char*)"Initializing Interrupt Descriptor Table...");
    print_raw(tty_buffer);
    idt_install();
    tty_out((char*)"OK\n");
    tty_out((char*)"Initializing Interrupt Service(s)...");
    print_raw(tty_buffer);
	isrs_install();
    tty_out((char*)"OK\n");
    tty_out((char*)"Initializing Interrupt Request Handler(s)...");
    print_raw(tty_buffer);
    irq_install();
    tty_out((char*)"OK\n");
    tty_out((char*)"Initializing Dynamic Memory...");
    print_raw(tty_buffer);
    initializeMem();
    tty_out((char*)"OK\n");
    asm volatile("sti");
    tty_out((char*)"Installing Interrupt Request Handler for Timer...");
    print_raw(tty_buffer);
    timer_install();
    tty_out((char*)"OK\n");
    tty_out((char*)"Installing Interrupt Request Handler for Keyboard...");
    print_raw(tty_buffer);
    kb_install();
    tty_out((char*)"OK\n");
    print_raw(tty_buffer);
    sleep(1);
    enable_input();
    set_cursor_pos(0);
}

extern "C" void main(){
    init();
    tty_set(1);
    tty_out((char*)"Hi this is tty1\n");
    print_raw(tty_buffer);
    sleep(1);
    tty_set(1);
    tty_out((char*)"Hi this is tty2\n");
    print_raw(tty_buffer);
    sleep(1);
    tty_set(1);
    tty_out((char*)"Hi this is tty3\n");
    print_raw(tty_buffer);
    sleep(1);
    tty_set(1);
    tty_out((char*)"Hi this is tty4\n");
    print_raw(tty_buffer);
    sleep(1);
    tty_set(0);
    print_raw(tty_buffer);
    // enable_input();
    return;
}
