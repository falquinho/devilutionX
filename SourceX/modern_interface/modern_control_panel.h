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
#define PANEL_ELEMENT_BELT_1  8
#define PANEL_ELEMENT_BELT_2  9
#define PANEL_ELEMENT_BELT_3  10
#define PANEL_ELEMENT_BELT_4  11
#define PANEL_ELEMENT_BELT_5  12
#define PANEL_ELEMENT_BELT_6  13
#define PANEL_ELEMENT_BELT_7  14
#define PANEL_ELEMENT_BELT_8  15
#define PANEL_ELEMENT_SPELL_1 16
#define PANEL_ELEMENT_SPELL_2 17
#define PANEL_ELEMENT_SPELL_3 18
#define PANEL_ELEMENT_SPELL_4 19
#define PANEL_ELEMENT_SPELL_5 20
#define PANEL_ELEMENT_SPELL_6 21
#define PANEL_ELEMENT_NONE    22
#define PANEL_ELEMENTS_NUM    23

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

DEVILUTION_END_NAMESPACE
#endif //__MODERNCONTROLPANEL_H__s