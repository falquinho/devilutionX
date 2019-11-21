#include "modern_spellbar.h"
#include "modern_control_panel.h"
#include "utils.h"

DEVILUTION_BEGIN_NAMESPACE

Rect spellbar_rect = {
    panel_rect.x + 71, panel_rect.y + 35, 244, 34
};

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

    sprintf(infostr, "Spell slot #%d", slot + 1);
    sprintf(panelstr, "Click to set spell");

    pnumlines = 1;
}

void DrawModernSpellbar()
{
    static char hotkeys[6][4] = {"Q", "W", "E", "R", "T", "RMB"};

    int x = spellbar_rect.x + 13;
	int y = panel_rect.y + panel_rect.h - 8;
	for(int i = 0; i < 6; i++, x += 42) {
		DrawString(x - (i >= 5? 6: 0), y, hotkeys[i]);
	}
}

DEVILUTION_END_NAMESPACE