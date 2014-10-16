AS = i686-elf-as
CC = i686-elf-gcc
CXX = i686-elf-g++

all: os.bin

boot.o: src/boot.s
	$(AS) src/boot.s -o bin/boot.o

kernel.o: src/kernel.c
	$(CC) -c src/kernel.c -o bin/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

os.bin: linker.ld kernel.o boot.o
	$(CC) -T linker.ld -o os.bin -ffreestanding -O2 -nostdlib bin/boot.o bin/kernel.o -lgcc

iso: isodir/boot/grub/grub.cfg os.bin
	cp os.bin isodir/boot/os.bin
	grub-mkrescue -o os.iso isodir

run:
	qemu-system-i386 -kernel os.bin

.PHONY: clean

clean:
	rm -rf *.o *.bin *.iso
	rm -rf bin/*.o


#gcc -m32 -c kernel.c -o kc.o -nostdinc -std=c99
#ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o
#qemu-system-i386 -kernel kernel