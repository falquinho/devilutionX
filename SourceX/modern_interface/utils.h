#ifndef __UTILS_H__
#define __UTILS_H__

#include "devilution.h"

DEVILUTION_BEGIN_NAMESPACE

void SetPixel(int x, int y, BYTE color);
void DrawRectangle(int left, int bottom, int width, int height, BYTE color, bool dither);
void DrawChar(int x, int y, char c);
void DrawString(int x, int y, char* str);
void DrawTooltip(int* el_rect, char* str);
void DrawTooltipAvoidRect(int* rect, char* str);
bool CoordInsideRect(int x, int y, int* rect);

DEVILUTION_END_NAMESPACE

#endif // __UTILS_H__