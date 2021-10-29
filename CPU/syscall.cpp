extern void _syscall();

void sys_0(regs* r) {
    print_str((uint8*)"Syscall 0");
}
void sys_1(regs* r) {
    print_str((uint8*)"Syscall 1");
}
void sys_2(regs* r) {
    print_str((uint8*)"Syscall 2");
}
void sys_3(regs* r) {
    print_str((uint8*)"Syscall 3");
}
void sys_4(regs* r) {
    print_str((uint8*)"Syscall 4");
}
void sys_5(regs* r) {
    print_str((uint8*)"Syscall 5");
}
void sys_6(regs* r) {
    print_str((uint8*)"Syscall 6");
}
void sys_7(regs* r) {
    print_str((uint8*)"Syscall 7");
}
void sys_8(regs* r) {
    print_str((uint8*)"Syscall 8");
}
void sys_9(regs* r) {
    print_str((uint8*)"Syscall 9");
}
void sys_10(regs* r) {
    print_str((uint8*)"Syscall 10");
}
void sys_11(regs* r) {
    print_str((uint8*)"Syscall 11");
}
void sys_12(regs* r) {
    print_str((uint8*)"Syscall 12");
}
void sys_13(regs* r) {
    print_str((uint8*)"Syscall 13");
}
void sys_14(regs* r) {
    print_str((uint8*)"Syscall 14");
}
void sys_15(regs* r) {
    print_str((uint8*)"Syscall 15");
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
        default: sys_undefined(r); break;
    }
}