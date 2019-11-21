#include "modern_belt.h"
#include "modern_control_panel.h"

DEVILUTION_BEGIN_NAMESPACE

Rect belt_rect = {
    panel_rect.x + 78, panel_rect.y + 3, 229, 28
};

void DrawModernBelt()
{
    static const int left   = belt_rect.x + SCREEN_X;
	static const int bottom = belt_rect.y + belt_rect.h + SCREEN_Y;
	static const int frame_width = 28;
	static const int hor_space   = 29;
	
    bool first_heal_drawn = false;
    bool first_mana_drawn = false;
	for (int i = 0; i < MAXBELTITEMS; i++) {
        ItemStruct item = plr[myplr].SpdList[i];
		if (item._itype == ITYPE_NONE)
			continue;

		int frame = plr[myplr].SpdList[i]._iCurs + CURSOR_FIRSTITEM;

		if (plr[myplr].SpdList[i]._iStatFlag)
			CelClippedDraw(left + (hor_space * i), bottom, pCursCels, frame, frame_width);
		else
			CelDrawLightRed(left + (hor_space * i), bottom, pCursCels, frame, frame_width, 0, 8, 1);
		
        char char_to_draw = i + 49;
        if((item._iMiscId == IMISC_FULLHEAL || item._iMiscId == IMISC_HEAL) && !first_heal_drawn) {
            first_heal_drawn = true;
            char_to_draw = 'F';
        }
        else if((item._iMiscId == IMISC_MANA || item._iMiscId == IMISC_FULLMANA) && !first_mana_drawn) {
            first_mana_drawn = true;
            char_to_draw = 'G';
        }
		DrawChar(left - SCREEN_X + 20 + (i*hor_space), bottom - SCREEN_Y - 12, char_to_draw);
	}
}


bool CheckCursorOverModernBelt()
{
    return CoordInsideRect(MouseX, MouseY, belt_rect);
}


void OnCursorOverModernBelt()
{
    static const int slot_width = 29;
    int index = (MouseX - belt_rect.x)/slot_width;

    ItemStruct item = plr[myplr].SpdList[index];

	if(item._itype == ITYPE_NONE) {
		infostr[0] = '\0';
		panelflag = false;
		return;
	}

	strcpy(infostr, item._iName);
    pnumlines = 0;

    PrintItemMisc(&item);
}


void UseFirstPotion(bool life_pot)
{
    int id_potion = life_pot? IMISC_FULLHEAL : IMISC_MANA;
    int i;
    for(i = 0; i < MAXBELTITEMS; i++) {
        ItemStruct item = plr[myplr].SpdList[i];
        if(item._itype != ITYPE_NONE && (item._iMiscId == id_potion || item._iMiscId == (id_potion + 1)))
            break;
    }
    if(i >= MAXBELTITEMS)
        return;

    UseInvItem(myplr, 47 + i);
}

DEVILUTION_END_NAMESPACE