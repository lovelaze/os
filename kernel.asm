;; kernel.asm
bits 32 						; nasm directive - 32 bit
section .text				; here begins the text section
	; multiboot spec
	align 4					; 4 byte aligned
	dd 0x1BADB002  			; magic field - identifies the multiboot header
	dd 0x00 				; flags
	dd - (0x1BADB002 + 0x00); checksum. magic + flags + checksum should be zero


global start				; nasm directive to set symbols as global - used by linker
extern kmain				; this function is declared elsewhere

start:
	cli
	call kmain
	hlt;
	
