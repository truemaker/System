uint32 digit_count(int num)
{
  uint32 count = 0;
  if(num == 0)
    return 1;
  while(num > 0){
    count++;
    num = num/10;
  }
  return count;
}

uint32 list_length(uint16* list) {
  uint32 len = 0;
  while(list[len]) {
    len++;
  }
  return len;
}
