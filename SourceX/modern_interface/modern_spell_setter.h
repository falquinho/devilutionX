#ifndef __MODERNSPELLSETTER_H__
#define __MODERNSPELLSETTER_H__

#include "devilution.h"

DEVILUTION_BEGIN_NAMESPACE

void OpenModernSpellSetter(int spell_index);

void CloseModernSpellSetter();

bool CheckCursorOverSpellSetter();

bool IsSpellSetterOpen();

void DrawModernSpellSetter();

void OnCursorOverSpellSetter();

void OnClickSpellSetter();

DEVILUTION_END_NAMESPACE

#endif