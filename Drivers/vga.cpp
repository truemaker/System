int cursor_pos = 0;
uint16* buffer = (uint16*) 0xB8000;
uint8 fg_color = 0x0f;
uint8 bg_color = 0x01;

void disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void enable_cursor(uint8 cursor_start, uint8 cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void SetCursorPosRaw(uint16 pos){
	outb(0x3d4, 0x0f);
	outb(0x3d5, (uint8)(pos & 0xff));
	outb(0x3d4, 0x0e);
	outb(0x3d5, (uint8)((pos >> 8) & 0xff));
	return;
}

uint16 vga_entry(uint8 ch, uint8 fore_color, uint8 back_color) 
{
  uint16 ax = 0;
  uint8 ah = 0, al = 0;

  ah = back_color;
  ah <<= 4;
  ah |= fore_color;
  ax = ah;
  ax <<= 8;
  al = ch;
  ax |= al;

  return ax;
}

void set_cursor_pos(int pos) {
    cursor_pos = pos;
    SetCursorPosRaw(cursor_pos);
}

void next_line() {
    set_cursor_pos(((cursor_pos / 80) * 80) + 80);
}

void print_char(uint8 c) {
    if (c == '\n') {
        next_line();
    } else if (c == '\t') {
        set_cursor_pos(cursor_pos + 4);
    } else if (c == '\b') {
        buffer[cursor_pos - 1] = vga_entry(0, fg_color, bg_color);
        set_cursor_pos(cursor_pos - 1);
    } else {
        buffer[cursor_pos] = vga_entry(c, fg_color, bg_color);
        set_cursor_pos(cursor_pos + 1);
    }
}

void input_char(uint8 c, bool caps) {
    if (caps) {
        if (0 < (c - 96)) {
            print_char(c - 32);
        } else {
            print_char(c);
        }
    } else {
        print_char(c);
    }
}

void print_str(const char* str) {
    for (int i = 0; i < strlen((char*)str); i++) {
        print_char(str[i]);
    }
}

void clear() {
    cursor_pos = 0;
    for (int i = 0; i < 2200; i++) {
        buffer[i] = vga_entry(0,fg_color,bg_color);
    }
}

void print_raw(uint16* raw) {
    for (uint32 i = 0; i < 2200; i++) {
        buffer[i] = raw[i];
    }
}
