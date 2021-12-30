#ifndef GRAPHICS_H
#define GRAPHICS_H

#define GRAPHICS_ADDRESS 0xA0000
#define GRAPHICS_MAX 0xF9FF
#define GRAPHICS_MAX_WIDTH 320
#define GRAPHICS_MAX_HEIGHT 200

uint8* graphics_buffer;
uint8 gInitialized = 0;

enum graphics_color {
  BLACK,
  BLUE,
  GREEN,
  CYAN,
  RED,
  MAGENTA,
  BROWN,
  GREY,
  DARK_GREY,
  BRIGHT_BLUE,
  BRIGHT_GREEN,
  BRIGHT_CYAN,
  BRIGHT_RED,
  BRIGHT_MAGENTA,
  YELLOW,
  WHITE = 0x1F,
};

/* Attribute Controller Registers */
#define	GRAPHICS_AC_INDEX 0x3C0
#define	GRAPHICS_AC_READ 0x3C1
#define	GRAPHICS_AC_WRITE 0x3C0

/*
Miscellaneous Output
*/
#define	GRAPHICS_MISC_READ 0x3CC
#define	GRAPHICS_MISC_WRITE 0x3C2

/* Sequencer Registers */
#define GRAPHICS_SEQ_INDEX 0x3C4
#define GRAPHICS_SEQ_DATA 0x3C5

/* GRAPHICS Color Palette Registers */
#define	GRAPHICS_DAC_READ_INDEX 0x3C7
#define	GRAPHICS_DAC_WRITE_INDEX 0x3C8
#define	GRAPHICS_DAC_DATA 0x3C9

/* Graphics Controller Registers */
#define GRAPHICS_GC_INDEX 0x3CE
#define GRAPHICS_GC_DATA 0x3CF

/* CRT Controller Registers */
#define GRAPHICS_CRTC_INDEX 0x3D4
#define GRAPHICS_CRTC_DATA 0x3D5

/* General Control and Status Registers */
#define	GRAPHICS_INSTAT_READ 0x3DA

void init_graphics();
void gClear();
void gSwap();
void gClear_color(uint8 color);
void putpixel(uint16 x, uint16 y, uint8 color);
void setpixel(uint16 index, uint8 color);
void draw_line(uint16 x1, uint16 y1, uint16 x2, uint16 y2, uint8 color);
void draw_rect(uint16 x, uint16 y, uint16 width, uint16 height, uint8 color);
void fill_rect(uint16 x, uint16 y, uint16 width, uint16 height, uint8 color);
void draw_circle(uint16 x, uint16 y, uint16 radius, uint8 color);
void draw_diamond(uint16 x, uint16 y, uint16 radius, uint8 color);

#endif
