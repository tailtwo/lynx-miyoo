#ifndef __FONT_H__
#define __FONT_H__

/* screen and font sizes */
#define	SCREEN_W	640
#define	SCREEN_H	480
#define	X_SIZE		8
#define	Y_SIZE		14
#define	X_STEP		8
#define	Y_STEP		15
#define X_MARGIN	((SCREEN_W-((int)(SCREEN_W/X_STEP))*X_STEP)/2)
#define	Y_MARGIN	((SCREEN_H-((int)(SCREEN_H/Y_STEP))*Y_STEP)/2)
typedef	uint8_t		font_uint_t;
typedef	int8_t		font_int_t;

void draw_char(SDL_Surface* surface, unsigned char symbol, int x, int y, unsigned short color);
void draw_string(SDL_Surface* surface, const char* text, int x, int y, unsigned short color);

#endif
