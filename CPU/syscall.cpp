extern void _syscall();

void sys_0(regs* r) {
    kernel_exit();
}
void sys_1(regs* r) {
    tfs_mkfile((uint8*)r->ebx, r->ecx);
}
void sys_2(regs* r) {
    int (*func)(){(int (*)())&r->ebx};
    if (((*func)()) > 0) {
        kernel_exit();
    }
}
void sys_3(regs* r) {
    tty_out((char*)"Syscall 3");
}
void sys_4(regs* r) {
    tty_out((char*)"Syscall 4");
}
void sys_5(regs* r) {
    tty_out((char*)"Syscall 5");
}
void sys_6(regs* r) {
    tty_out((char*)"Syscall 6");
}
void sys_7(regs* r) {
    tty_out((char*)"Syscall 7");
}
void sys_8(regs* r) {
    tty_out((char*)"Syscall 8");
}
void sys_9(regs* r) {
    tty_out((char*)"Syscall 9");
}
void sys_10(regs* r) {
    tty_out((char*)"Syscall 10");
}
void sys_11(regs* r) {
    tty_out((char*)"Syscall 11");
}
void sys_12(regs* r) {
    tty_out((char*)"Syscall 12");
}
void sys_13(regs* r) {
    tty_out((char*)"Syscall 13");
}
void sys_14(regs* r) {
    tty_out((char*)"Syscall 14");
}
void sys_15(regs* r) {
    tty_out((char*)"Syscall 15");
}
void sys_16(regs* r) {
    tty_out((char*)r->ebx);
}
void sys_17(regs* r) {
    tty_next_line();
}

void sys_undefined(regs* r) {
    r->err_code = r->eax;
    kpanic((uint8*)"Invalid syscall", r);
}

void sys_init(){
    idt_set_gate(0x80, (uint32)_syscall, 0x1 << 3, 0x8E);
}

void syscall_c(regs* r){
    switch(r->eax) {
        case 0x00: sys_0(r); break;
        case 0x01: sys_1(r); break;
        case 0x02: sys_2(r); break;
        case 0x03: sys_3(r); break;
        case 0x04: sys_4(r); break;
        case 0x05: sys_5(r); break;
        case 0x06: sys_6(r); break;
        case 0x07: sys_7(r); break;
        case 0x08: sys_8(r); break;
        case 0x09: sys_9(r); break;
        case 0x0A: sys_10(r); break;
        case 0x0B: sys_11(r); break;
        case 0x0C: sys_12(r); break;
        case 0x0D: sys_13(r); break;
        case 0x0E: sys_14(r); break;
        case 0x0F: sys_15(r); break;
        case 0x10: sys_16(r); break;
        case 0x11: sys_17(r); break;
        default: sys_undefined(r); break;
    }
}