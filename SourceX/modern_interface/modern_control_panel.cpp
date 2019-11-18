#include "modern_control_panel.h"
#include "utils.h"

DEVILUTION_BEGIN_NAMESPACE

BYTE* ctrl_panel_cel;
BYTE* ascii_charmap_cel;
BYTE* spellicons_sm_cel;

Rect panel_rect = {(SCREEN_WIDTH - 386)/2, SCREEN_HEIGHT - 71 - 8, 386, 71};

int panel_left   = SCREEN_X + panel_rect.x;
int panel_bottom = SCREEN_Y + panel_rect.y + panel_rect.h;

Rect panel_elements_rects[PANEL_ELEMENTS_NUM] = {
    {panel_rect.x +   9, panel_rect.y + 14, 16, 16}, // character button
    {panel_rect.x +   9, panel_rect.y + 31, 16, 16}, // quest button 
    {panel_rect.x +   9, panel_rect.y + 48, 16, 16}, // map button
    {panel_rect.x + 361, panel_rect.y + 14, 16, 16}, // inventory button
    {panel_rect.x + 361, panel_rect.y + 31, 16, 16}, // spellbook button
    {panel_rect.x + 361, panel_rect.y + 48, 16, 16}, // menu button
    {panel_rect.x +  34, panel_rect.y + 14, 23, 51}, // life meter  
    {panel_rect.x + 329, panel_rect.y + 14, 23, 51}, // mana meter
    {panel_rect.x + 78 + (28*0), panel_rect.y + 3, 28, 26}, // belt item 1
    {panel_rect.x + 78 + (28*1), panel_rect.y + 3, 28, 26}, // belt item 2 
    {panel_rect.x + 78 + (28*2), panel_rect.y + 3, 28, 26}, // belt item 3 
    {panel_rect.x + 78 + (28*3), panel_rect.y + 3, 28, 26}, // belt item 4 
    {panel_rect.x + 78 + (28*4), panel_rect.y + 3, 28, 26}, // belt item 5 
    {panel_rect.x + 78 + (28*5), panel_rect.y + 3, 28, 26}, // belt item 6 
    {panel_rect.x + 78 + (28*6), panel_rect.y + 3, 28, 26}, // belt item 7 
    {panel_rect.x + 78 + (28*7), panel_rect.y + 3, 28, 26}, // belt item 8
    {panel_rect.x + 71 + (42 * 0), panel_rect.y + 35, 34, 34}, // spell 1
    {panel_rect.x + 71 + (42 * 1), panel_rect.y + 35, 34, 34}, // spell 2
    {panel_rect.x + 71 + (42 * 2), panel_rect.y + 35, 34, 34}, // spell 3
    {panel_rect.x + 71 + (42 * 3), panel_rect.y + 35, 34, 34}, // spell 4
    {panel_rect.x + 71 + (42 * 4), panel_rect.y + 35, 34, 34}, // spell 5
    {panel_rect.x + 71 + (42 * 5), panel_rect.y + 35, 34, 34}, // spell 6
};


int quickspells[4] = {
	SPL_NULL, SPL_NULL, SPL_NULL, SPL_NULL
};


void LoadModernPanel()
{
	ctrl_panel_cel    = LoadFileInMem("assets\\modern_panel.cel", NULL);
	ascii_charmap_cel = LoadFileInMem("assets\\asciicharmap.cel", NULL);
	spellicons_sm_cel = LoadFileInMem("assets\\spellicons_sm.cel", NULL);
}


// Sizes of the life and mana meters:
int meter_h = 51;
int meter_w = 23;

void DrawLifeMeter()
{
	int curr_h = ((double)plr[myplr]._pHitPoints / (double)plr[myplr]._pMaxHP) * meter_h;
	Rect rect = {panel_rect.x + 34, panel_rect.y + 14 + meter_h - curr_h, meter_w, curr_h};
	DrawRectangle(rect, PAL8_RED + 6, false);
}

void DrawManaMeter()
{
	int curr_h = ((double)plr[myplr]._pMana / (double)plr[myplr]._pMaxMana) * meter_h;
	Rect rect = {panel_rect.x + 329, panel_rect.y + 14 + meter_h - curr_h, meter_w, curr_h};
	DrawRectangle(rect, PAL8_BLUE + 6, false);
}


void DrawItemBelt()
{
	int left   = panel_left + 77;
	int bottom = panel_bottom - 42;
	int frame_width = 28;
	int hor_space   = 29;
	
	for (int i = 0; i < MAXBELTITEMS; i++) {
		if (plr[myplr].SpdList[i]._itype == ITYPE_NONE)
			continue;

		int frame = plr[myplr].SpdList[i]._iCurs + CURSOR_FIRSTITEM;

		if (plr[myplr].SpdList[i]._iStatFlag)
			CelClippedDraw(left + (hor_space * i), bottom, pCursCels, frame, frame_width);
		else
			CelDrawLightRed(left + (hor_space * i), bottom, pCursCels, frame, frame_width, 0, 8, 1);
		
		DrawChar(left - SCREEN_X + 20 + (i*hor_space), bottom - SCREEN_Y - 12, i + 49);
	}
}


// labels to draw on spellbar
char hotkeys[6][4] = {
	"Q", "W", "E", "R", "T", "RMB"
};
void DrawSpellBar()
{
	int x = panel_left + 84 - SCREEN_X;
	int y = panel_bottom - 8 - SCREEN_Y;
	for(int i = 0; i < 6; i++, x += 42) {
		DrawString(x - (i >= 5? 6: 0), y, hotkeys[i]);
	}
}


void DrawModernPanel()
{
	CelDraw( panel_left, panel_bottom, ctrl_panel_cel, 1, panel_rect.w);
	DrawLifeMeter();
	DrawManaMeter();
	DrawSpellBar();
	DrawItemBelt();
}


char btns_labels[][64] = {
	"Character(C)",
	"Quest(Q)",
	"Map(M)",
	"Inventory(I)",
	"Spellbook(B)",
	"Menu(Esc)",
};
void OnPanelButtonHovered(int btn)
{
	strcpy(infostr, btns_labels[btn]);
	pnumlines = 0;
}


void OnItemBeltHovered(int index)
{
	ItemStruct item = plr[myplr].SpdList[index];
	if(item._itype == ITYPE_NONE) {
		infostr[0] = '\0';
		panelflag = false;
		return;
	}
	strcpy(infostr, item._iName);
		if (item._iIdentified) {
			strcpy(infostr, item._iIName);
			PrintItemDetails(&item);
		} else {
			PrintItemDur(&item);
		}
}


void OnLifeOrManaBarHovered(int meter) {
	if(meter == PANEL_ELEMENT_LIFEBAR) 
		sprintf(infostr, "%d/%d", plr[myplr]._pHitPoints >> 6, plr[myplr]._pMaxHP >> 6);
	else
		sprintf(infostr, "%d/%d", plr[myplr]._pMana >> 6, plr[myplr]._pMaxMana >> 6);
}


void OnSpellSlotHovered(int slot) {
	sprintf(infostr, "Speel #%d hovered", slot);
}


void ModernPanelOnCursorIn()
{
	int i = 0;
	for(; i < PANEL_ELEMENTS_NUM; i++) {
		if(CoordInsideRect(MouseX, MouseY, panel_elements_rects[i]))
			break;
	}
	if(i == PANEL_ELEMENT_NONE) {
		panelflag = false;
		infostr[0] = '\0';
		return;
	}
	
	panelflag = true;
	if(i <= PANEL_ELEMENT_BTN_MNU) 
		return OnPanelButtonHovered(i);
	else if(i >= PANEL_ELEMENT_BELT_1 && i <= PANEL_ELEMENT_BELT_8)
		return OnItemBeltHovered(i - 8);
	else if(i == PANEL_ELEMENT_MANABAR || i == PANEL_ELEMENT_LIFEBAR)
		return OnLifeOrManaBarHovered(i);
	else if(i >= PANEL_ELEMENT_SPELL_1 && i <= PANEL_ELEMENT_SPELL_6)
		return OnSpellSlotHovered(i - PANEL_ELEMENT_SPELL_1);
}


bool ModernPanelContainCurs()
{
	return CoordInsideRect(MouseX, MouseY, panel_rect);
}


DEVILUTION_END_NAMESPACE