void outb(uint16 port, uint8 data){
	asm volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}

uint8 inb(uint16 port){
	uint8 res;
	asm volatile("inb %1, %0" : "=a"(res) : "Nd"(port));
	return res;
}
