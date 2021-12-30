void start_desktop() {
    tty_out("Initializing Graphics Library");
    init_graphics();
    wSetup();
    window* w = (window*)kmalloc(sizeof(struct window));
    panel* p = (panel*)kmalloc(sizeof(panel));
    gContext* c = wCreateContext(99, 91);

    wFillRect(c, 0, 0, 50, 50, BLUE);
    wDrawRect(c, 1, 1, 48, 48, RED);

    p->context = c;
    w->panel = p;
    w->width = 100;
    w->height = 100;
    w->x = GRAPHICS_MAX_WIDTH / 2 - 50;
    w->y = GRAPHICS_MAX_HEIGHT / 2 - 50;
    for (int i = 0; i < 100; i++) {
        w->y = i;
        w->x = i;
        wSetup();
        wDraw(w);
        sleep(1);
    }
    
}