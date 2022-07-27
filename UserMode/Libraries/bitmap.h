#ifndef BITMAP_H
#define BITMAP_H

#define BITMAP_SIZE 8

void draw_bm_char(uint16 x, uint16 y, uint8 color, char ch);
void draw_bm_string(uint16 x, uint16 y, uint8 color, char *str);

#endif