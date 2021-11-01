int strlen(char* str) {
    int len = 0;
    while (str[len] != 0) {
        len++;
    }
    return len;
}

uint8 strcompare(char* str1, char* str2) {
    uint8 res = 0;
    if (strlen(str1) == strlen(str2)) {
      for (uint8 i = 0; i < strlen(str1); i++) {
        if (str1[i] == str2[i]) {
          res = 1;
        } else {
          res = 0;
          return res;
        }
      }
    }
    return res;
}

char* num_to_char(uint8 num) {
  char* c = 0;
  itoa(num, c);
  return c;
}
