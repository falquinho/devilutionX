#include "modern_spellbar.h"
#include "modern_control_panel.h"
#include "modern_spell_setter.h"
#include "utils.h"
#include "../Source/diablo.h"
#include "../Source/control.h"
#include "../Source/player.h"
#include "../Source/inv.h"

DEVILUTION_BEGIN_NAMESPACE

Rect spellbar_rect = {
    panel_rect.x + 71, panel_rect.y + 35, 244, 34
};

int quick_spells[6] = {
    (int)SPL_INVALID,
    (int)SPL_INVALID,
    (int)SPL_INVALID,
    (int)SPL_INVALID,
    (int)SPL_INVALID,
    (int)SPL_INVALID
};

char spells_type[6]  = {0, 0, 0, 0, 0, 0};


bool CheckCursorOverModernSpellbar()
{
    if(!CoordInsideRect(MouseX, MouseY, spellbar_rect))
        return false;

    int offset = MouseX - spellbar_rect.x;

    if(offset%42 > 34)
        return false;

    return true;
}

int  GetSpellInSlot(int slot)
{
    if(slot < 0 || slot > 5)
        return (int)SPL_INVALID;
    return (int)quick_spells[slot];
}

void OnCursorOverModernSpellbar()
{
    int slot = (MouseX - spellbar_rect.x)/42;

    if(quick_spells[slot] == SPL_INVALID) {
        sprintf(infostr, "Spell slot #%d", slot + 1);
        sprintf(panelstr, "Click to set spell");
        pnumlines = 1;
    } else {
        pnumlines = 0;
        SetSpellInfo(quick_spells[slot], spells_type[slot]);
    }
}

void OnClickModernSpellbar()
{
    int index = (MouseX - spellbar_rect.x) / 42;
    OpenModernSpellSetter(index);
}

void DrawModernSpellbar()
{
    static int frame_size = 34;

    static char hotkeys[6][4] = {"Q", "W", "E", "R", "T", "RMB"};

    int x = spellbar_rect.x;
	int y = panel_rect.y + panel_rect.h - 2;
	for(int i = 0; i < 6; i++, x += 42) {
        if(spells_type[i] == RSPLTYPE_SCROLL && !GetNumOfSpellScrolls(quick_spells[i]))
            quick_spells[i] = SPL_INVALID;
        else if(spells_type[i] == RSPLTYPE_CHARGES && !GetNumChargesEquippedStaff(quick_spells[i]))
            quick_spells[i] = SPL_INVALID;
        
        if(quick_spells[i] != SPL_INVALID)
            CelDraw(SCREEN_X + x, SCREEN_Y + y, spellicons_sm_cel, SpellITbl[quick_spells[i]], frame_size);
		DrawString(x + 13, y - CHAR_H/2, hotkeys[i]);
	}
}

void SpellbarSetSpell(int slot, int spell_id, char type)
{
    quick_spells[slot] = spell_id;
    spells_type[slot] = type;
}

void SpellbarCastSpell(int slot)
{
    plr[myplr]._pRSpell   = quick_spells[slot];
    plr[myplr]._pRSplType = spells_type[slot];

    CheckPlrSpell();
}

DEVILUTION_END_NAMESPACE