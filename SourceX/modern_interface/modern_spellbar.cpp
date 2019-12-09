#include "modern_spellbar.h"
#include "modern_control_panel.h"
#include "modern_spell_setter.h"
#include "utils.h"
#include "../Source/control.h"
#include "../Source/player.h"

DEVILUTION_BEGIN_NAMESPACE

Rect spellbar_rect = {
    panel_rect.x + 71, panel_rect.y + 35, 244, 34
};

int quick_spells[5] = {0, 0, 0, 0, 0};

char spells_type[5]  = {};


bool CheckCursorOverModernSpellbar()
{
    if(!CoordInsideRect(MouseX, MouseY, spellbar_rect))
        return false;

    int offset = MouseX - spellbar_rect.x;

    if(offset%42 > 34)
        return false;

    return true;
}

void OnCursorOverModernSpellbar()
{
    int slot = (MouseX - spellbar_rect.x)/42;

    if(slot >= 5 && plr[myplr]._pRSpell) {
        pnumlines = 0;
        SetSpellInfo(plr[myplr]._pRSpell, plr[myplr]._pRSplType);
    } else if(!quick_spells[slot]) {
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
	for(int i = 0; i < 5; i++, x += 42) {
        if(quick_spells[i])
            CelDraw(SCREEN_X + x, SCREEN_Y + y, spellicons_sm_cel, SpellITbl[quick_spells[i]], frame_size);
		DrawString(x + 13, y - CHAR_H/2, hotkeys[i]);
	}
    if(plr[myplr]._pRSpell)
        CelDraw(SCREEN_X + x, SCREEN_Y + y, spellicons_sm_cel, SpellITbl[plr[myplr]._pRSpell], frame_size);
    DrawString(x + 7, y - CHAR_H/2, hotkeys[5]);
}

void SetSpell(int slot, int spell_id, char type)
{
    if(slot < 5) {
        quick_spells[slot] = spell_id;
        spells_type[slot]  = type;
    } else if(slot == 5) {
        plr[myplr]._pRSpell = spell_id;
        plr[myplr]._pRSplType = type;
    }

}

void CastSpell(int slot)
{
    // if (!quick_spells[slot])
    //     return;

    int curr_spell = plr[myplr]._pRSpell;
    char curr_type = plr[myplr]._pRSplType;
    plr[myplr]._pRSpell = quick_spells[slot];
    plr[myplr]._pRSplType = spells_type[slot];
    CheckPlrSpell();
    plr[myplr]._pRSpell = curr_spell;
    plr[myplr]._pRSplType = curr_type;
}

DEVILUTION_END_NAMESPACE