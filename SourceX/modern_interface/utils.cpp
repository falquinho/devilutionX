#include "utils.h"


DEVILUTION_BEGIN_NAMESPACE

int char_w = 13;
int line_h = 12;


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


void DrawChar(int x, int y, char c)
{
	int cel_index = fontframe[gbFontTransTbl[c]];
	CelDraw(SCREEN_X + x, SCREEN_Y + y + line_h, pPanelText, cel_index, char_w);
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


void DrawTooltip(int x, int y, char* str)
{
	int height = line_h;
	int width  = 0;
	int curr_width = 0;
	for(int i = 0; str[i] != '\0'; i++) {
		curr_width += char_w;
		if(str[i] == '\n') {
			height += line_h;
			width = width > curr_width? width : curr_width;
			curr_width = 0;
		}
	}
	width = width > curr_width? width : curr_width;

	DrawRectangle(SCREEN_X + x, SCREEN_Y + y + height + 2, width + 4, height + 4, PAL16_GRAY + 15, true);
	DrawString(x + 2, y, str);
}


bool CoordInsideRect(int x, int y, int* rect)
{
	if(x < rect[0] || x > rect[0] + rect[2])
		return false;
	if(y < rect[1] || y > rect[1] + rect[3])
		return false;
	return true;
}

DEVILUTION_END_NAMESPACE