char updated = 1;
gContext* c;
int pads_y = 160;
void move_pads() {
    if (kpressed[72]==1) { pads_y = pads_y - 5; updated = 1; }
    if (kpressed[80]==1) { pads_y = pads_y + 5; updated = 1; }
}

void draw_pads() {
    wFillRect(c, 10, 10+pads_y, 20, 10-pads_y, WHITE);
    wFillRect(c, 179, 10+pads_y, 189, 10-pads_y, WHITE);
}

void start_desktop() {
    char running = 1;
    tty_out("Initializing Graphics Library");
    init_graphics();


    wSetup();
    window* w = (window*)kmalloc(sizeof(struct window));
    panel* p = (panel*)kmalloc(sizeof(panel));
    c = wCreateContext(319, 199);

    /*wFillRect(c, 25, 25, 50, 50, BLUE);
    wDrawRect(c, 25, 25, 50, 50, RED);*/

    p->context = c;
    w->panel = p;
    w->width = 320;
    w->height = 200;
    w->x = 0;
    w->y = 0;
    
    while (running) {
        move_pads();
        draw_pads();
        if (updated) {
            wDraw(w);
            draw = 1;
            updated = 0;
        }
        gSwap();
    }
}
