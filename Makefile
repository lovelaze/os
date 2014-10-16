AS = i686-elf-as
CC = i686-elf-gcc
CXX = i686-elf-g++

all: os.bin

boot.o: src/boot.s
	$(AS) src/boot.s -o bin/boot.o

kernel.o: src/kernel.c
	$(CXX) -c src/kernel.cpp -o bin/kernel.o -ffreestanding -O2 -Wall -Wextra

os.bin: linker.ld kernel.o boot.o
	$(CC) -T linker.ld -o os.bin -ffreestanding -O2 -nostdlib bin/boot.o bin/kernel.o -lgcc

iso: isodir/boot/grub/grub.cfg os.bin
	cp os.bin isodir/boot/os.bin
	grub-mkrescue -o os.iso isodir

run:
	qemu-system-i386 -kernel os.bin

run-iso:
	qemu-system-i386 -cdrom os.iso

.PHONY: clean

clean:
	rm -rf *.o *.bin *.iso
	rm -rf bin/*.o