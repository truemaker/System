int tty_pos = 0;
uint16* tty_buffer;

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

void tty_set(uint8 ttyIdx) {
    switch (ttyIdx) {
        case 0: tty_buffer = tty0; tty_pos = tty0_pos; break;
        case 1: tty_buffer = tty1; tty_pos = tty1_pos; break;
        case 2: tty_buffer = tty2; tty_pos = tty2_pos; break;
        case 3: tty_buffer = tty3; tty_pos = tty3_pos; break;
        case 4: tty_buffer = tty4; tty_pos = tty4_pos; break;
        case 5: tty_buffer = tty5; tty_pos = tty5_pos; break;
        case 6: tty_buffer = tty6; tty_pos = tty6_pos; break;
        case 7: tty_buffer = tty7; tty_pos = tty7_pos; break;
        default: print_str("Error: invalid ttyIdx\n");
    }
}

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