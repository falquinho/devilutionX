#include "modern_control_panel.h"
#include "utils.h"
#include "modern_belt.h"
#include "modern_spellbar.h"
#include "modern_meters.h"

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

void DrawModernPanel()
{
	CelDraw( panel_left, panel_bottom, ctrl_panel_cel, 1, panel_rect.w);
	DrawModernMeters();
	DrawModernSpellbar();
	DrawModernBelt();
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


void ModernPanelOnCursorIn()
{
	panelflag = true;

	// if(i <= PANEL_ELEMENT_BTN_MNU) 
	// 	return OnPanelButtonHovered(i);

	if(CheckCursorOverModernBelt())
		return OnCursorOverModernBelt();

	else if(CheckCursorOverModernSpellbar())
		return OnCursorOverModernSpellbar();
	
	else if(CheckCursorOverModernMeters())
		return OnCursorOverModernMeters();
	
	infostr[0] = '\0';
	pnumlines  = 0;
	panelflag  = false;

}


bool ModernPanelContainCurs()
{
	return CoordInsideRect(MouseX, MouseY, panel_rect);
}


void ModernPanelOnCharPress(char c)
{
	switch(c) {
		case 'f':
		case 'F':
			UseFirstPotion(true);
			break;
		case 'g':
		case 'G':
			UseFirstPotion(false);
			break;
	}
}

DEVILUTION_END_NAMESPACE