#ifndef __UTILS_H__
#define __UTILS_H__

#include "devilution.h"
#include "modern_control_panel.h"

DEVILUTION_BEGIN_NAMESPACE

void SetPixel(int x, int y, BYTE color);
void DrawRectangle(int rect[4], BYTE color, bool dither);
void DrawChar(int x, int y, char c);
void DrawString(int x, int y, char* str);
bool IsCoordInsideRect(int x, int y, int* rect);

DEVILUTION_END_NAMESPACE

#endif // __UTILS_H__