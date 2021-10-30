int* tty_pos;

/*
uint16 tty0[2200];
uint16 tty1[2200];
uint16 tty2[2200];
uint16 tty3[2200];
uint16 tty4[2200];
uint16 tty5[2200];
uint16 tty6[2200];
uint16 tty7[2200];
*/

uint16* tty0;
uint16* tty1;
uint16* tty2;
uint16* tty5;
uint16* tty3;
uint16* tty4;
uint16* tty6;
uint16* tty7;

void setup_tty() {
    tty0 = (uint16*)kmalloc(2200 * 2);
    tty1 = (uint16*)kmalloc(2200 * 2);
    tty2 = (uint16*)kmalloc(2200 * 2);
    tty3 = (uint16*)kmalloc(2200 * 2);
    tty4 = (uint16*)kmalloc(2200 * 2);
    tty5 = (uint16*)kmalloc(2200 * 2);
    tty6 = (uint16*)kmalloc(2200 * 2);
    tty7 = (uint16*)kmalloc(2200 * 2);
}

int tty0_pos = 0;
int tty1_pos = 0;
int tty2_pos = 0;
int tty3_pos = 0;
int tty4_pos = 0;
int tty5_pos = 0;
int tty6_pos = 0;
int tty7_pos = 0;

void tty_set_pos(int pos) {
    *tty_pos = pos;
}

void tty_sync() {
    set_cursor_pos(*tty_pos);
}

void scrollPageUp(){
    for(int i = 160*2; i < 4000 - 160; i++) *(tty_buffer + i - 160) = *(tty_buffer + i);
}

void tty_next_line() {
    tty_set_pos(((*tty_pos / 80) * 80) + 80);
    // scrollPageUp();
}

void tty_char(uint8 c) {
    if (c == '\n') {
        tty_next_line();
    } else if (c == '\t') {
        tty_set_pos(*tty_pos + 4);
    } else if (c == '\b') {
        tty_buffer[*tty_pos - 1] = vga_entry(0, 0x0F, 0x00);
        tty_set_pos(*tty_pos - 1);
    } else {
        tty_buffer[*tty_pos] = vga_entry(c, 0x0F, 0x00);
        tty_set_pos(*tty_pos + 1);
    }
    // print_char(c);
}

void tty_color_char(uint8 c, uint8 color, uint8 bg) {
    if (c == '\n') {
        tty_next_line();
    } else if (c == '\t') {
        tty_set_pos(*tty_pos + 4);
    } else if (c == '\b') {
        tty_buffer[*tty_pos - 1] = vga_entry(0, color, bg);
        tty_set_pos(*tty_pos - 1);
    } else {
        tty_buffer[*tty_pos] = vga_entry(c, color, bg);
        tty_set_pos(*tty_pos + 1);
    }
    // print_char(c);
}

void tty_out(char* str) {
    for (int i = 0; i < strlen((char*)str); i++) {
        tty_char(str[i]);
    }
}

void tty_color_out(char* str, uint8 color, uint8 bg) {
    for (int i = 0; i < strlen((char*)str); i++) {
        tty_color_char(str[i], color, bg);
    }
}

void tty_show_tty_num(uint8 num) {
    tty_buffer = tty0;
    tty_pos = &tty0_pos;
    tty_out("Switched to TTY");
    tty_out(num_to_char(num));
    tty_out("\n");
}

void tty_clear() {
    *tty_pos = 0;
    for (int i = 0; i < 2200; i++) {
        tty_buffer[i] = vga_entry(0,0x0f,0x00);
    }
}

void tty_clear_color(uint8 color) {
    *tty_pos = 0;
    for (int i = 0; i < 2200; i++) {
        tty_buffer[i] = vga_entry(0,0x0f,color);
    }
}

void tty_set(uint8 ttyIdx) {
    if (ttyIdx > 0) {
        tty_show_tty_num(ttyIdx);
    }
    switch (ttyIdx) {
        case 0: tty_buffer = tty0; tty_pos = &tty0_pos; tty_out("Switched to TTY0\n"); break;
        case 1: tty_buffer = tty1; tty_pos = &tty1_pos; break;
        case 2: tty_buffer = tty2; tty_pos = &tty2_pos; break;
        case 3: tty_buffer = tty3; tty_pos = &tty3_pos; break;
        case 4: tty_buffer = tty4; tty_pos = &tty4_pos; break;
        case 5: tty_buffer = tty5; tty_pos = &tty5_pos; break;
        case 6: tty_buffer = tty6; tty_pos = &tty6_pos; break;
        case 7: tty_buffer = tty7; tty_pos = &tty7_pos; break;
        default: print_str((uint8*)"Error: invalid ttyIdx\n");
    }
}

