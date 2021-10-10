#pragma once
uint8 fg_color;
uint8 bg_color;
void print_char(uint8 c);
void print_str(char* str);
void clear();
void set_cursor_pos(int pos);
void next_line();
