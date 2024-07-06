#include <SDL/SDL.h>
#include "font.h"
#include "font8x14.h"

void draw_char(SDL_Surface* surface, unsigned char symbol, int x, int y, unsigned short color) {
	const font_uint_t	*ptr;
	uint16_t		*d;
	font_int_t		p;
	uint32_t		px, py;
	int			padd;

	d = (uint16_t*)surface->pixels + x + (y * surface->w);
	if (symbol < 128) padd = +1;
	else {	// flip symbols over 128
		symbol -= 128;
		padd = -1;
	}
	ptr = embedded_font + ((symbol>32)?symbol-32:0) * Y_STEP + ((padd<0)?Y_SIZE-1:0);

	for (py = 0; py < Y_SIZE; py++, d += surface->w) {
		p = (font_int_t)*ptr;
		ptr += padd;
		for (px = 0; px < X_SIZE; px++, p <<= 1) {
			if (p < 0) d[px] = color;
		}
	}
}

void draw_string(SDL_Surface* surface, const char* text, int orig_x, int orig_y, unsigned short color) {
	int x = orig_x, y = orig_y;
	while(*text) {
		if(*text == '\n') {
			x = orig_x;
			y += Y_STEP;
		} else {
			draw_char(surface, *text, x, y, color);
			x += X_STEP;
		}
		text++;
	}
}
