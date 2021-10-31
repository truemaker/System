global _out
extern tty_out
_out:
    pop ebx
    mov eax, 0x10
    int 0x80
    push ebx
    ret
