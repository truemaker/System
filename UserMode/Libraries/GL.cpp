void draw_triangle(uint16 x, uint16 y, uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint8 color) {
    draw_line(x1, y1, x2, y2, color);
    draw_line(x1, y1, x, y, color);
    draw_line(x, y, x2, y2, color);
}

uint8* create_framebuffer() {
  uint8 framebuffer[GRAPHICS_MAX];
  for (int i = 0; i < GRAPHICS_MAX; i++) {
    framebuffer[i] = BLACK;
  }
  return framebuffer;
}

void set_framebuffer(uint8 *buffer) {
  graphics_buffer = buffer;
}

void reset_framebuffer() {
  graphics_buffer = (uint8*)GRAPHICS_ADDRESS;
}

void draw_framebuffer(uint8 *b) {
  uint8* buffer = b;
  for (int i = 0; i < GRAPHICS_MAX; i++) {
    if (buffer[i] > 0) {
      setpixel(i, buffer[i]);
    }
  }
}