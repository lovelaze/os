/*
* kernel.c
*/

/* Hardware text mode color constants. */
enum vga_color
{
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};

unsigned int make_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

unsigned int make_vgaentry(char c, unsigned int color)
{
	unsigned int c16 = c;
	unsigned int color16 = color;
	return c16 | color16 << 8;
}

unsigned int strlen(const char * str)
{
	unsigned int ret = 0;
	while (str[ret] != '\0')
	{
		ret++;
	}
	return ret;
}

static const unsigned int VGA_WIDTH = 80;
static const unsigned int VGA_HEIGHT = 24;

unsigned int terminal_row;
unsigned int terminal_column;
unsigned int terminal_color;
unsigned int * terminal_buffer;



void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (unsigned int  *) 0xB8000;
	for ( unsigned int y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( unsigned int x = 0; x < VGA_WIDTH; x++ )
		{
			const unsigned int index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}

}


void terminal_putentryat(char c, unsigned int color, unsigned int x, unsigned int y)
{
	const unsigned int index =  y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_putchar(char c)
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);

	if (++terminal_column+1 == VGA_WIDTH)
	{
		terminal_column = 0;
		
		if (++terminal_row+1 == VGA_HEIGHT )
		{
			terminal_row = 0;

		}
	}

	
	

}

void terminal_writestring(const char * string)
{
	unsigned int len = strlen(string);
	for (unsigned int i = 0; i < len; ++i) {
		terminal_putchar(string[i]);
	}
}


void kmain(void)
{
	terminal_initialize();

	terminal_writestring("bajs");	

	
	return;
}