extern void _syscall();
void sys_init(){
    idt_set_gate(0x80, (uint32)_syscall, 0x1 << 3, 0x8E);
}

void syscall_c(regs* r){
    print_str((uint8*)"Syscall ");
    print_str((uint8*)num_to_char(r->eax));
}