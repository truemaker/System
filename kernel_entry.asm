extern disable_cursor
extern kernel_exit
section .text
    [bits 32]
    [extern main]
    [extern start_user_mode]
    in al, 0x92
    or al, 2
    out 0x92, al
    call is_A20_on?
    ;call main
    
    ; call kernel_exit
    ; put system into infinite loop
    main_loop:
    jmp main_loop
is_A20_on?:
pushad
mov edi,0x112345  ;odd megabyte address.
mov esi,0x012345  ;even megabyte address.
mov [esi],esi     ;making sure that both addresses contain diffrent values.
mov [edi],edi     ;(if A20 line is cleared the two pointers would point to the address 0x012345 that would contain 0x112345 (edi)) 
cmpsd             ;compare addresses to see if the're equivalent.
popad
jne A20_on        ;if not equivalent , A20 line is set.
ret               ;if equivalent , the A20 line is cleared.
 
A20_on:
; *your code from here*

    call main
    ret

%include "CPU/interrupt.asm"
%include "UserMode/Libraries/libs.asm"
%include "UserMode/Applications/applications.asm"

section .data
    hello dw "Hello World!"

section .rodata
%include "IncBins/incbins.asm"
