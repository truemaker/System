export PATH=$PATH:/usr/local/i386elfgcc/bin

nasm "boot.asm" -f bin -o "Binaries/boot.bin"
nasm "kernel_entry.asm" -f elf -o "Binaries/kernel_entry.o"
i386-elf-gcc -ffreestanding -m32 -g -c "kernel.cpp" -o "Binaries/kernel.o"
nasm "zeroes.asm" -f bin -o "Binaries/zeroes.bin"

i386-elf-ld -m elf_i386 -o "Binaries/full_kernel.bin" -Ttext 0x7ef0 "Binaries/kernel_entry.o" "Binaries/kernel.o" --oformat binary
cat "Binaries/boot.bin" "Binaries/full_kernel.bin" "Binaries/zeroes.bin"  > "Binaries/OS.bin"

qemu-system-x86_64 -drive format=raw,file="Binaries/OS.bin",index=0,if=floppy, -m 512M
