int cursor_pos = 0;
uint16* buffer = (uint16*) 0xB8000;
#define fg_color 0x0f
#define bg_color 0x01
uint8 last_char = 0x00;
uint8 listen = 0x00;
uint32 listen_start = 0x00;
uint8 show = 0x01;

void tty_char(uint8 c);
void tty_sync();
void tty_next_line();
uint32* tty_pos;
uint16* tty_buffer;

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

void tty_set_pos(int pos);

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

void print_colored_char(uint8 c, uint8 color, uint8 bg) {
    if (c == '\n') {
        next_line();
    } else if (c == '\t') {
        set_cursor_pos(cursor_pos + 4);
    } else if (c == '\b') {
        buffer[cursor_pos - 1] = vga_entry(0, color, bg);
        set_cursor_pos(cursor_pos - 1);
    } else {
        buffer[cursor_pos] = vga_entry(c, color, bg);
        set_cursor_pos(cursor_pos + 1);
    }
}

void input_char(uint8 c, bool caps) {
    if (show == 0) {
        if (c == '\n') {
            tty_next_line();
            last_char = '\n';
        } if (c == '\b') {
            tty_char('\b');
            last_char = 0;
        } else {
            tty_char((uint8)'*');
            last_char = c;
        }
        return;
    } else {
        tty_char(c);
    }
    if (c == '\b') {
        last_char = '\b';
        return;
    }
    last_char = c;
}

uint8* kb_listen(uint8 passwd) {
    uint8* listen_buffer = (uint8*)kmalloc(255);
    char listen_index = 0;
    listen_start = *tty_pos;
    listen = 1;
    show = passwd;
    while (listen_index < 255 && listen_buffer[listen_index] != '\n' && listen_index >= 0) {
        if (last_char != 0x00) {
            if (last_char == '\n') {
                last_char = 0;
                show = 1;
                listen = 0;
                return listen_buffer;
            } else if (last_char == '\b' && listen_index > 0) {
                listen_index--;
                listen_buffer[listen_index] = 0;
                last_char = 0;
            } else {
                listen_buffer[listen_index] = last_char;
                listen_index++;
                last_char = 0;
            }
        }
    }
    listen = 0;
    next_line();
    show = 1;
    return listen_buffer;
}

void print_str(uint8* str) {
    for (int i = 0; i < strlen((char*)str); i++) {
        print_char(str[i]);
    }
}

void print_binary(uint32 num)
{
  char bin_arr[32];
  uint32 index = 31;
  uint32 i;
  while (num > 0){
    if(num & 1){
      bin_arr[index] = '1';
    }else{
      bin_arr[index] = '0';
    }
    index--;
    num >>= 1;
  }

  for(i = 0; i < 32; ++i){
   if(i <= index)
      print_char('0');
   else
     print_char(bin_arr[i]);
  }
}

void print_colored_str(const char* str, uint8 color, uint8 bg) {
    for (int i = 0; i < strlen((char*)str); i++) {
        print_colored_char(str[i], color, bg);
    }
}

void clear() {
    cursor_pos = 0;
    for (int i = 0; i < 2200; i++) {
        buffer[i] = vga_entry(0,fg_color,bg_color);
    }
}

void clear_color(uint8 color) {
    cursor_pos = 0;
    for (int i = 0; i < 2200; i++) {
        buffer[i] = vga_entry(0,fg_color,color);
    }
}

void print_raw(uint16* raw) {
    for (uint32 i = 0; i < 2200; i++) {
        buffer[i] = raw[i];
    }
}

void vga_update() {
    print_raw(tty_buffer);
    tty_sync();
}
