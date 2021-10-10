int tty_pos = 0;
uint16 tty_buffer[2200];

void tty_set_pos(int pos) {
    tty_pos = pos;
}

void tty_next_line() {
    tty_set_pos(((tty_pos / 80) * 80) + 80);
}

void tty_char(uint8 c) {
    if (c == '\n') {
        tty_next_line();
    } else if (c == '\t') {
        tty_set_pos(tty_pos + 4);
    } else if (c == '\b') {
        tty_buffer[tty_pos - 1] = vga_entry(0, 0xFF, 0x01);
        tty_set_pos(tty_pos - 1);
    } else {
        tty_buffer[tty_pos] = vga_entry(c, 0x0F, 0x00);
        tty_set_pos(tty_pos + 1);
    }
    // print_char(c);
}

void tty_out(char* str) {
    for (int i = 0; i < strlen((char*)str); i++) {
        tty_char(str[i]);
    }
}