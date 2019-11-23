#ifndef __MODERNCONTROLPANEL_H__
#define __MODERNCONTROLPANEL_H__

#include "../../SourceS/devilution.h"
#include "utils.h"

DEVILUTION_BEGIN_NAMESPACE

#define PANEL_ELEMENT_BTN_CHR 0
#define PANEL_ELEMENT_BTN_QST 1
#define PANEL_ELEMENT_BTN_MAP 2
#define PANEL_ELEMENT_BTN_INV 3
#define PANEL_ELEMENT_BTN_SBK 4
#define PANEL_ELEMENT_BTN_MNU 5
#define PANEL_ELEMENT_LIFEBAR 6
#define PANEL_ELEMENT_MANABAR 7
#define PANEL_ELEMENT_NONE    8
#define PANEL_ELEMENTS_NUM    9

extern BYTE* ctrl_panel_cel;
extern BYTE* ascii_charmap_cel;
extern BYTE* spellicons_sm_cel;

extern Rect panel_rect;

extern Rect panel_elements_rects[PANEL_ELEMENTS_NUM];

extern int quickspells[4];

void LoadModernPanel();

void DrawModernPanel();

void ModernPanelOnCursorIn();

bool ModernPanelContainCurs();

void ModernPanelOnCharPress(char c);

void ModerPanelOnMouseBtnDown(char c);

DEVILUTION_END_NAMESPACE
#endif //__MODERNCONTROLPANEL_H__s