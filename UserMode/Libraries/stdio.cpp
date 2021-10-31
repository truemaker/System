extern void _out(uint8* str);

void cls() {
    tty_clear();
}

uint8* inputk() {
    return kb_listen(1);
}

uint8* passwdk() {
    return kb_listen(0);
}

void outc(char* str) {
    tty_out(str);
    // _out((uint8*)str);
}

void outu(uint8* str) {
    outc((char*)str);
}

void out(const char* str) {
    outc((char*)str);
}
