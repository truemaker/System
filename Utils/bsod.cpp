#include "../CPU/regs.h"

void tty_set(uint8 tty);

void fill_reg(struct regs *reg) {
    uint32 eaxres, ebxres, ecxres, edxres;
    uint32 espres, ebpres, eipres, esires;
    asm("movl\t%%eax, %0" : "=m" (eaxres));
    asm("movl\t%%ebx, %0" : "=m" (ebxres));
    asm("movl\t%%ecx, %0" : "=m" (ecxres));
    asm("movl\t%%edx, %0" : "=m" (edxres));
    asm("movl\t%%esp, %0" : "=m" (espres));
    asm("movl\t%%ebp, %0" : "=m" (ebpres));
    asm("movl\t%%esi, %0" : "=m" (esires));
    reg->eax = eaxres;
    reg->ebx = ebxres;
    reg->ecx = ecxres;
    reg->edx = edxres;
    reg->esp = espres;
    reg->ebp = ebpres;
    reg->esi = esires;
}

void kpanic(uint8* message, regs* r) {
    if (r == 0) {
        fill_reg(r);
    }
    asm("cli");
    clear();
    print_str((uint8*)"System crashed with exeption: ");
    print_str((uint8*)message);
    next_line();
	next_line();
	print_str((uint8*)"And here is some information:\n");
	print_str((uint8*)"  EDI       : ");
	print_binary(r->edi);
    next_line();
	print_str((uint8*)"  ESI       : ");
    print_binary(r->esi);
	next_line();
	print_str((uint8*)"  EBP       : ");
	print_binary(r->ebp);
    next_line();
	print_str((uint8*)"  ESP       : ");
    print_binary(r->esp);
    next_line();
    print_str((uint8*)"  EBX       : ");
    print_binary(r->ebx);
    next_line();
    print_str((uint8*)"  EDX       : ");
    print_binary(r->edx);
    next_line();
    print_str((uint8*)"  ECX       : ");
    print_binary(r->ecx);
    next_line();
    print_str((uint8*)"  EAX       : ");
    print_binary(r->eax);
    next_line();
    print_str((uint8*)"  GS        : ");
    print_binary(r->gs);
    next_line();
    print_str((uint8*)"  FS        : ");
    print_binary(r->fs);
    next_line();
    print_str((uint8*)"  ES        : ");
    print_binary(r->es);
    next_line();
    print_str((uint8*)"  DS        : ");
    print_binary(r->ds);
    next_line();
    print_str((uint8*)"  EIP       : ");
    print_binary(r->eip);
    next_line();
    print_str((uint8*)"  CS        : ");
    print_binary(r->cs);
    next_line();
    print_str((uint8*)"  EFLAGS    : ");
    print_binary(r->eflags);
    next_line();
    print_str((uint8*)"  USERESP   : ");
    print_binary(r->useresp);
    next_line();
    print_str((uint8*)"  SS        : ");
    print_binary(r->ss);
    next_line();
    print_str((uint8*)"  ERROR-CODE: ");
    print_str((uint8*)num_to_char(r->err_code));
    next_line();
    print_str((uint8*)"  INT-NUMBER: ");
    print_str((uint8*)num_to_char(r->int_no));
    next_line();
    disable_input();
    next_line();
	next_line();
	print_str((uint8*)"System Halted!");
loop:
    asm("nop");
    goto loop;
}