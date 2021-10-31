extern disable_cursor
extern kernel_exit
section .text
    [bits 32]
    [extern main]
    call main
    call kernel_exit
    ; put system into infinite loop
    main_loop:
    jmp main_loop
%include "CPU/interrupt.asm"
%include "UserMode/Libraries/libs.asm"

section .data
    hello dw "Hello World!"

section .rodata
%include "IncBins/incbins.asm"
