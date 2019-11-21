#include "modern_meters.h"
#include "modern_control_panel.h"
#include "utils.h"

DEVILUTION_BEGIN_NAMESPACE


Rect mana_meter_rect = {
    panel_rect.x + 329, panel_rect.y + 14, 23, 51
};
Rect life_meter_rect = {
    panel_rect.x +  34, panel_rect.y + 14, 23, 51
};

bool CheckCursorOverModernMeters()
{
    return CoordInsideRect(MouseX, MouseY, life_meter_rect) || CoordInsideRect(MouseX, MouseY, mana_meter_rect);
}

void OnCursorOverModernMeters()
{
    pnumlines = 0;

    if(CoordInsideRect(MouseX, MouseY, life_meter_rect)) 
		sprintf(infostr, "%d/%d", plr[myplr]._pHitPoints >> 6, plr[myplr]._pMaxHP >> 6);
	else
		sprintf(infostr, "%d/%d", plr[myplr]._pMana >> 6, plr[myplr]._pMaxMana >> 6);  
}

void DrawModernMeters()
{
	int curr_h = ((double)plr[myplr]._pHitPoints / (double)plr[myplr]._pMaxHP) * life_meter_rect.h;
	Rect rect = {life_meter_rect.x, life_meter_rect.y + life_meter_rect.h - curr_h, life_meter_rect.w, curr_h};
	DrawRectangle(rect, PAL8_RED + 6, false);

	curr_h = ((double)plr[myplr]._pMana / (double)plr[myplr]._pMaxMana) * mana_meter_rect.h;
	rect = {mana_meter_rect.x, mana_meter_rect.y + mana_meter_rect.h - curr_h, mana_meter_rect.w, curr_h};
	DrawRectangle(rect, PAL8_BLUE + 6, false);
}

DEVILUTION_END_NAMESPACE