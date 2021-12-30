int timer_ticks = 0;
int seconds = 0;

void kernel_loop();
void vga_update();

void timer_phase(int hz)
{
	int divisor = 1193180 / hz;	   /* Calculate our divisor */
	outb(0x43, 0x36);			 /* Set our command byte 0x36 */
	outb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
	outb(0x40, divisor >> 8);	 /* Set high byte of divisor */
}

void timer_handler(struct regs *r)
{
    /* Increment our 'tick count' */
    timer_ticks++;
    kernel_loop();
    vga_update();
    if (gInitialized == 1) {
        gSwap();
    }

    if (timer_ticks % 18 == 0)
    {
    	seconds++;
	    /*print_str(num_to_char(seconds));
        print_str(" Seconds");
        set_cursor_pos(cursor_pos - (strlen(num_to_char(seconds)) + 8));*/
    }
}

void sleep(int time_to_wait_seconds) {
    int start = seconds;
    while (seconds < time_to_wait_seconds + start) {
        
    }
}

void timer_install()
{
    irq_install_handler(0, timer_handler);
}
