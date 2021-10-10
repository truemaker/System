int strlen(char* str) {
    int len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}

char* num_to_char(uint8 num) {
  char* c = 0;
  itoa(num, c);
  return c;
}
