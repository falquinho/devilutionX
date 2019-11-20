#ifndef __MODERNBELT_H__
#define __MODERNBELT_H__

#include "devilution.h"
#include "utils.h"

DEVILUTION_BEGIN_NAMESPACE

extern Rect belt_rect;

void DrawModernBelt();

bool CheckCursorOverModernBelt();

void OnCursorOverModernBelt();

DEVILUTION_END_NAMESPACE

#endif