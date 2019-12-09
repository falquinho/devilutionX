#ifndef __MODERNSPELLBAR_H__
#define __MODERNSPELLBAR_H__

#include "devilution.h"

DEVILUTION_BEGIN_NAMESPACE

bool CheckCursorOverModernSpellbar();

void OnCursorOverModernSpellbar();

void OnClickModernSpellbar();

void DrawModernSpellbar();

void SetSpell(int slot, int spell_id, char type);

void CastSpell(int slot);

DEVILUTION_END_NAMESPACE

#endif