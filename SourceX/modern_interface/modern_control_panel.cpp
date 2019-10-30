#include "modern_control_panel.h"
#include "utils.h"
#include "modern_input_handler.h"

DEVILUTION_BEGIN_NAMESPACE

BYTE* ctrl_panel_cel;

int panel_width  = 386;
int panel_left   = SCREEN_X + (SCREEN_WIDTH - panel_width)/2;
int panel_bottom = SCREEN_Y + SCREEN_HEIGHT - 8;

// Sizes of the life and mana meters:
int meter_h = 51;
int meter_w = 23;

void load_modern_control_panel()
{
	ctrl_panel_cel = LoadFileInMem("assets\\modern_panel.cel", NULL);
}

void update_life()
{
	int curr_h = ((double)plr[myplr]._pHitPoints / (double)plr[myplr]._pMaxHP) * meter_h;
	int left   = panel_left   + 34;
	int bottom = panel_bottom - 6;
	DrawRectangle(left, bottom, meter_w, curr_h, PAL8_RED + 6, false);
}

void update_mana()
{
	int curr_h = ((double)plr[myplr]._pMana / (double)plr[myplr]._pMaxMana) * meter_h;
	int left   = panel_left   + 329;
	int bottom = panel_bottom - 6;
	DrawRectangle(left, bottom, meter_w, curr_h, PAL8_BLUE + 6, false);
}

void draw_item_belt()
{
	int frame;
	int left   = panel_left + 77;
	int bottom = panel_bottom - 42;
	int frame_width = 28;
	int hor_space   = 29;
	
	for (int i = 0; i < MAXBELTITEMS; i++) {
		if (plr[myplr].SpdList[i]._itype == ITYPE_NONE) {
			continue;
		}

		int frame = plr[myplr].SpdList[i]._iCurs + CURSOR_FIRSTITEM;

		if (plr[myplr].SpdList[i]._iStatFlag)
			CelClippedDraw(left + (hor_space * i), bottom, pCursCels, frame, frame_width);
		else
			CelDrawLightRed(left + (hor_space * i), bottom, pCursCels, frame, frame_width, 0, 8, 1);
		
		DrawChar(left - SCREEN_X + 20 + (i*hor_space), bottom - SCREEN_Y - 12, i + 49);
	}		
}

char hotkeys[6][4] = {
	"Q", "W", "E", "R", "LMB", "RMB"
};
void draw_spellbar()
{
	int x = panel_left + 84 - SCREEN_X;
	int y = panel_bottom - 8 - SCREEN_Y;
	for(int i = 0; i < 6; i++, x += 42) {
		DrawString(x - (i >= 4? 12: 0), y, hotkeys[i]);
	}
}

void draw_tooltip_if_needed()
{
	if(btn_hovered < 6)
		DrawTooltip(btns_rects[btn_hovered], btns_tips[btn_hovered]);
}

void draw_modern_control_panel()
{
	CelDraw( panel_left, panel_bottom, ctrl_panel_cel, 1, panel_width);
	update_life();
	update_mana();
	draw_item_belt();
	draw_spellbar();
	draw_tooltip_if_needed();
}

void unload_modern_control_panel()
{

}

DEVILUTION_END_NAMESPACE