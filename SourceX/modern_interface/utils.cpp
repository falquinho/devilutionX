#include "utils.h"


DEVILUTION_BEGIN_NAMESPACE

void SetPixel(int sx, int sy, BYTE col)
{
	if (sy < 0 || sy >= SCREEN_HEIGHT + SCREEN_Y || sx < SCREEN_X || sx >= SCREEN_WIDTH + SCREEN_X)
		return;

	BYTE *dst;

	dst = &gpBuffer[sx + BUFFER_WIDTH * sy];

	*dst = col;
}


void DrawRectangle(int left, int bottom, int width, int height, BYTE color, bool dither)
{
	for (int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			if(!dither)
				SetPixel(left + x, bottom - y, color);
			else if(x%2 == y%2)
				SetPixel(left + x, bottom - y, color);
		}
	}
	
}


void DrawString(int x, int y, char* str)
{
	int char_w = 13;
	int line_h = 12;
	int curr_col  = 0;
	for(int i = 0; str[i] != '\0'; i++, curr_col++) {
		if(str[i] == '\n') {
			y += line_h;
			curr_col = -1;
			continue;
		}
		int left = SCREEN_X + x + (curr_col * char_w);
		int bottom = SCREEN_Y + y + line_h;
		int cel_index = fontframe[gbFontTransTbl[str[i]]];
		CelDraw(left, bottom, pPanelText, cel_index, char_w);
	}
}

DEVILUTION_END_NAMESPACE