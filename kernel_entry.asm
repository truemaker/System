extern hello
extern disable_cursor
section .text
    [bits 32]
    [extern main]
    call main
    mov eax, 0x00
    int 0x80
    jmp $
%include "CPU/interrupt.asm"

section .rodata
%include "IncBins/incbins.asm"
