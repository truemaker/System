bool input_enabled = true;
unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

bool shift_pressed = false;
bool caps_lock = false;

void disable_input() {
  input_enabled = false;;
}

void enable_input() {
  input_enabled = true;
}

void keyboard_handler(struct regs *r)
{
    if (!input_enabled) return;
    unsigned char scancode;

    scancode = inb(0x60);

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */

    	//print(toString((int)scancode, 16));		// for testing


    	switch(scancode){
    		case 0xaa: shift_pressed = false; break;

    	}

    }
    else
    {
    	switch(scancode){
    		case 0x4b: set_cursor_pos(cursor_pos - 1); break;
    		case 0x4d: set_cursor_pos(cursor_pos + 1); break;
    		case 0x48: set_cursor_pos(cursor_pos - 80); break;
    		case 0x50: set_cursor_pos(cursor_pos +80); break;
    		case 0x2a: shift_pressed = true; break;
    		case 0x3a: caps_lock = !caps_lock; break;
    		default: if (kbdus[scancode] != 0) input_char(kbdus[scancode], shift_pressed | caps_lock);
    	}
    }
}
