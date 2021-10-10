extern hello
extern disable_cursor
section .text
    [bits 32]
    [extern main]
    call main
    jmp $
%include "CPU/interrupt.asm"

section .rodata
%include "IncBins/incbins.asm"
