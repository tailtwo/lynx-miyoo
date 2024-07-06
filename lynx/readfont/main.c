#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

//#define	DISPLAY_FONT
#ifdef	DISPLAY_FONT
#include "gfx.h"
#endif

//
//	readfont Main
//
int main(int argc, char* argv[]) {
	TTF_Font*	font;
	SDL_Color	color={255,255,255,0};
	SDL_Surface	*image, *image_tmp, *screen;
	int		w, h, i, j;
	char		str[17];
	char		c;
	uint32_t	*p;
	char		filename[256] = "VCR_OSD_MONO_1.001.ttf";
	int		ptsize = 20;

	if (argc > 1) strcpy(filename, argv[1]);
	if (argc > 2) ptsize = atoi(argv[2]);
	SDL_Init(SDL_INIT_VIDEO);
#ifdef	DISPLAY_FONT
	screen = GFX_CreateRGBSurface(0, 640, 480, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	GFX_Init();
#else
	screen = SDL_CreateRGBSurface(0, 640, 480, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
#endif
	TTF_Init();

	font = TTF_OpenFont(filename, ptsize);
	if (!font) { printf("usage: readfont [filename.ttf] [pointsize]\n"); return 1; }
	TTF_SetFontHinting(font, TTF_HINTING_NONE);
	TTF_SizeText(font, "W", &w, &h);
	printf("FixedWidth:%d Height:%d w:%d h:%d\n", TTF_FontFaceIsFixedWidth(font), TTF_FontHeight(font), w, h);

#ifdef	DISPLAY_FONT
	c = 0x20;
	SDL_Rect rect = { 0, 0, 640, h };
	for (i=0; i<6; i++) {
		for (j=0; j<16; j++) { str[j] = c++; }
		str[16] = 0;
		image = TTF_RenderText_Solid(font, str, color);
		SDL_BlitSurface(image, NULL, screen, &rect);
		SDL_FreeSurface(image);
		rect.y += h;
	}
	// Draw 3 screens
	GFX_Flip(screen);
	GFX_Flip(screen);
	GFX_FlipForce(screen);
	sleep(2);
#endif
	str[1] = 0;
	printf("//\n//\tbased on %s %dpx\n//\nstatic const uint%d_t embedded_font[] = {\n", filename, ptsize, ((w>32)?64:(w>16)?32:(w>8)?16:8));
	for (c=0x20; c<0x80; c++) {
		str[0] = c;
		image = TTF_RenderText_Solid(font, str, color);
		image_tmp = SDL_ConvertSurface(image, screen->format, 0);
		SDL_FreeSurface(image);
		p = image_tmp->pixels; w = image_tmp->w; h = image_tmp->h;
		printf("// chr[%c] code:%d w:%d h:%d\n", c, c, w, h);
		for (i=0; i<h; i++) {
			printf("\t0b");
			for (j=0; j<w; j++) {
				if (*p++ & 0x00FFFFFF) printf("1"); else printf("0");
			}
			for (j=w; j<((w>32)?64:(w>16)?32:(w>8)?16:8); j++) {
				printf("0");
			}
			printf(",\n");
		}
		SDL_FreeSurface(image_tmp);
		if (c<0x7f) printf("\n");
	}
	printf("};\n");

	// Quit
	TTF_CloseFont(font);
	TTF_Quit();
#ifdef	DISPLAY_FONT
	GFX_WaitAllDone();
	GFX_FreeSurface(screen);
	GFX_Quit();
#else
	SDL_FreeSurface(screen);
#endif
	SDL_Quit();
	return 0;
}
