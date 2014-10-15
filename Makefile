all: kernel

kasm.o: kernel.asm
	nasm -f elf32 kernel.asm -o kasm.o

kc.o: kernel.c
	gcc -m32 -c kernel.c -o kc.o -nostdinc -std=c99

kernel: kasm.o kc.o link.ld
	ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o

run: kernel
	qemu-system-i386 -kernel kernel

.PHONY: clean

clean:
	rm -rf *.o


#gcc -m32 -c kernel.c -o kc.o -nostdinc -std=c99
#ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o
#qemu-system-i386 -kernel kernel