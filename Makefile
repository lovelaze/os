
# i586-elf-as boot.s -o boot.o
# i586-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
# i586-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

AS = $(HOME)/cross/bin/i586-elf-as
ASTARGET = src/boot.s
ASOBJ = bin/boot.o

CC = $(HOME)/cross/bin/i586-elf-gcc
CCTARGET = src/kernel.c
CCOBJ = bin/kernel.o
CCFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra

LINKTARGET = linker.ld
LINKOBJ = bin/myos.bin
LINKFLAGS = -ffreestanding -O2 -nostdlib -lgcc

GRUBFILE = isodir/boot/grub/grub.cfg

all: buildAS buildC link buildiso

buildAS: $(ASTARGET)
	$(AS) $(ASTARGET) -o $(ASOBJ)

buildC: $(CCTARGET)
	$(CC) -c $(CCTARGET) -o $(CCOBJ) $(CCFLAGS)

link: $(LINKTARGET) $(ASOBJ) $(CCOBJ)
	$(CC) -T $(LINKTARGET) $(ASOBJ) $(CCOBJ) -o $(LINKOBJ) $(LINKFLAGS)

buildiso: $(LINKOBJ) $(GRUBFILE)
	cp $(LINKOBJ) isodir/boot/myos.bin
	grub-mkrescue -o myiso.iso isodir

clean:
	rm bin/*.*

