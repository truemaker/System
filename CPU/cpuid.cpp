void cpuid(uint32 value, uint32 *eax, uint32 *ebx, unsigned int *ecx, uint32 *edx)
{
  uint32 eaxres, ebxres, ecxres, edxres;
  asm("xorl\t%eax, %eax");
  asm("xorl\t%ebx, %ebx");
  asm("xorl\t%ecx, %ecx");
  asm("xorl\t%edx, %edx");
  asm("movl\t%0, %%eax":"=m"(value));
  asm("cpuid");
  asm("movl\t%%eax, %0" : "=m" (eaxres));
  asm("movl\t%%ebx, %0" : "=m" (ebxres));
  asm("movl\t%%ecx, %0" : "=m" (ecxres));
  asm("movl\t%%edx, %0" : "=m" (edxres));
  *eax = eaxres;
  *ebx = ebxres;
  *ecx = ecxres;
  *edx = edxres;    
}