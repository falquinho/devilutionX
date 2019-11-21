#include "modern_control_panel.h"
#include "utils.h"
#include "modern_belt.h"
#include "modern_spellbar.h"
#include "modern_meters.h"
#include "modern_panel_buttons.h"

DEVILUTION_BEGIN_NAMESPACE

BYTE* ctrl_panel_cel;
BYTE* ascii_charmap_cel;
BYTE* spellicons_sm_cel;

Rect panel_rect = {(SCREEN_WIDTH - 386)/2, SCREEN_HEIGHT - 71 - 8, 386, 71};


void LoadModernPanel()
{
	ctrl_panel_cel    = LoadFileInMem("assets\\modern_panel.cel", NULL);
	ascii_charmap_cel = LoadFileInMem("assets\\asciicharmap.cel", NULL);
	spellicons_sm_cel = LoadFileInMem("assets\\spellicons_sm.cel", NULL);
}


void DrawModernPanel()
{
	static int panel_left = SCREEN_X + panel_rect.x;
	static int panel_bottom = SCREEN_Y + panel_rect.y + panel_rect.h;
	CelDraw( panel_left, panel_bottom, ctrl_panel_cel, 1, panel_rect.w);
	DrawModernMeters();
	DrawModernSpellbar();
	DrawModernBelt();
}


void ModernPanelOnCursorIn()
{
	panelflag = true;

	if(CheckCursorOverModernBelt())
		return OnCursorOverModernBelt();

	else if(CheckCursorOverModernSpellbar())
		return OnCursorOverModernSpellbar();
	
	else if(CheckCursorOverModernMeters())
		return OnCursorOverModernMeters();
	
	else if(CheckCursorOverButtons())
		return OnCursorOverButtons();
	
	infostr[0] = '\0';
	pnumlines  = 0;
	panelflag  = false;

}


bool ModernPanelContainCurs()
{
	return CheckCursorOverButtons()     ||
		CheckCursorOverModernBelt()     ||
		CheckCursorOverModernMeters()   ||
		CheckCursorOverModernSpellbar();
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


void ModerPanelOnMouseBtnDown(char btn)
{
	if( btn == 'l') {
		if(CheckCursorOverButtons())
			return OnLeftMouseClickPanelButtons();
		else if(CheckCursorOverModernBelt())
			return OnLeftClickModernBelt();
	}
}

DEVILUTION_END_NAMESPACE