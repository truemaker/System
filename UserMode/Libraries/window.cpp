typedef struct gContext {
    uint16 width, height;
    uint8* pixels;
} gContext;

typedef struct panel {
    gContext* context;
} panel;

typedef struct window {
    int x, y, width, height;
    panel* panel;
} window;

void wSetup() {
    fill_rect(0,0,GRAPHICS_MAX_WIDTH, GRAPHICS_MAX_HEIGHT, CYAN);
}

gContext* wCreateContext(uint16 width, uint16 height) {
    gContext* context = (gContext*)kmalloc(sizeof(gContext));
    context->width = width;
    context->height = height;
    context->pixels = (uint8*)kmalloc(width*height);
    for(uint16 index = 0; index < width*height; index++) {
        context->pixels[index] = BLACK;
    }
    return context;
}

void wPutPixel(gContext* context, uint16 x, uint16 y, uint8 color) {
    context->pixels[x+y*context->width] = color;
}

void wDrawLine(gContext* context, uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint8 color) {
    if (x1 == x2) {
        for (uint16 i = y1; i <= y2; i++) {
            wPutPixel(context, x1, i, color);
        }
    } else if (y1 == y2) {
        for (uint16 i = x1; i <= x2; i++) {
            wPutPixel(context, i, y1, color);
        }
    }
}

void wDrawRect(gContext* context, uint16 x, uint16 y, uint16 width, uint16 height, uint8 color) {
    wDrawLine(context, x, y, x, y+height, color);
    wDrawLine(context, x, y, x+width, y, color);
    wDrawLine(context, x + width, y, x + width, y+height, color);
    wDrawLine(context, x, y + height, x+width, y + height, color);
}

void wFillRect(gContext* context, uint16 x, uint16 y, uint16 width, uint16 height, uint8 color) {
    for (uint16 dx = x; dx < x+width; dx++) {
        for (uint16 dy = y; dy < y+height; dy++) {
            wPutPixel(context, dx, dy, color);
        }
    }
}

void wDrawContext(gContext* context, window* window) {
    uint16 x = 0, y = 0;
    for (uint16 index = 0; index < context->width*context->height; index++) {
        x = index;
        y = 0;
        while (x >= context->width) {
            x -= context->width;
            y++;
        }
        x += window->x + 1;
        y += window->y + 9;
        putpixel(x,y,context->pixels[index]);
    }
}

void wDrawPanel(panel* panel, window* window) {
    fill_rect(window->x + 1, window->y + 9, window->width - 2, window->height - 10, GREY);
    wDrawContext(panel->context, window);
}

void wDraw(window* window) {
    fill_rect(window->x + 2, window->y + 2, window->width, window->height, BLACK);
    fill_rect(window->x, window->y, window->width, window->height, BRIGHT_BLUE);
    draw_rect(window->x, window->y, window->width, window->height, BLUE);
    draw_line(window->x, window->y, window->x, window->height + window->y, BRIGHT_MAGENTA);
    draw_line(window->x, window->y, window->x + window->width, window->y, BRIGHT_MAGENTA);
    wDrawPanel(window->panel, window);
}

