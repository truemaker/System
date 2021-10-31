void fallback() {
    asm("cli");
    clear();
    set_cursor_pos(0);
    print_str((uint8*)"A Program Crashed the Kernel!\nFallback Kernel Activated!\n");
    print_str((uint8*)"All Interrupts are disabled!\n");
    print_str((uint8*)"Stopping CPU!\n");
    for (;;) {
        asm("nop");
    }
}