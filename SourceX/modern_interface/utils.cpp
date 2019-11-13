#include "utils.h"


DEVILUTION_BEGIN_NAMESPACE

int char_w = 6;
int line_h = 12;


void SetPixel(int sx, int sy, BYTE col)
{
	if (sy < 0 || sy >= SCREEN_HEIGHT + SCREEN_Y || sx < SCREEN_X || sx >= SCREEN_WIDTH + SCREEN_X)
		return;

	BYTE *dst;

	dst = &gpBuffer[sx + BUFFER_WIDTH * sy];

	*dst = col;
}


void DrawRectangle(int rect[4], BYTE color, bool dither)
{
	for (int y = 0; y < rect[3]; y++) {
		for(int x = 0; x < rect[2]; x++) {
			if(dither && x%2 != y%2)
				continue;
			SetPixel(SCREEN_X + rect[0] + x, SCREEN_Y + rect[1] + y, color);
		}
	}
}


void DrawChar(int x, int y, char c)
{
	int frame = (c - 31) < 1? 1 : (c - 31);
	CelDraw(SCREEN_X + x, SCREEN_Y + y + line_h, ascii_charmap_cel, frame, char_w);
}


void DrawString(int x, int y, char* str)
{
	int curr_col  = 0;
	for(int i = 0; str[i] != '\0'; i++, curr_col++) {
		if(str[i] == '\n') {
			y += line_h;
			curr_col = -1;
			continue;
		}
		int curr_x = x + (curr_col * char_w);
		DrawChar(curr_x, y, str[i]);
	}
}


bool IsCoordInsideRect(int x, int y, int* rect)
{
	if(x < rect[0] || x > rect[0] + rect[2])
		return false;
	if(y < rect[1] || y > rect[1] + rect[3])
		return false;
	return true;
}

DEVILUTION_END_NAMESPACE