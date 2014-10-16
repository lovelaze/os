#include <stddef.h>
#include <stdint.h>
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#include "kernel_util.hpp"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize()
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_scroll_down() {
	for (size_t row = 0; row < VGA_HEIGHT; ++row) {
		for (size_t column = 0; column < VGA_WIDTH; ++column) {
			const size_t index = row * VGA_WIDTH + column;
			const size_t next_index = (row + 1)* VGA_WIDTH + column;
			terminal_buffer[index] = terminal_buffer[next_index];
			//terminal_buffer[0] = terminal_buffer[80];
		}
	}
	terminal_column = 0;
}
 
void terminal_putchar(char c)
{	

	if (c == '\n') {
		terminal_column = 0;
		terminal_row += 1;
	} else {

		if (terminal_row+1 == VGA_HEIGHT ) {
				terminal_scroll_down();
				--terminal_row;
		}

		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if ( ++terminal_column == VGA_WIDTH ) {
			terminal_column = 0;
			
			
		}
	}
}
 
void terminal_writestring(const char* data) {
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ ) {
		terminal_putchar(data[i]);
	}
	
}
 
#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kmain()
{
	terminal_initialize();
	terminal_writestring("H\ne\nl\nl\no\nk\nH\ne\nl\nl\no\nk\nH\ne\nl\nl\no\nk\nH\ne\nl\nl\no\nk\nH\ne\nA\np");
	

}