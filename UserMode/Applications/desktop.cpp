void start_desktop() {
    tty_out("Initializing Graphics Library");
    init_graphics();
    fill_rect(0,0,100,100, BLUE);
    draw_rect(0,0,100,100, RED);
    draw_rect(1,1,98,98, YELLOW);
    gSwap();
}