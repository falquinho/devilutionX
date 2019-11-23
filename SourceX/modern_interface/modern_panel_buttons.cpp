#include "devilution.h"
#include "modern_panel_buttons.h"
#include "modern_control_panel.h"
#include "utils.h"

DEVILUTION_BEGIN_NAMESPACE

Rect left_btns_rect = {
    panel_rect.x +   9, panel_rect.y + 16, 16, 51
};
Rect right_btns_rect = {
    panel_rect.x + 361, panel_rect.y + 16, 16, 51
};

bool CheckCursorOverButtons()
{
    return CoordInsideRect(MouseX, MouseY, left_btns_rect) || CoordInsideRect(MouseX, MouseY, right_btns_rect);
}

void OnCursorOverButtons()
{
    static char labels[][64] = {
        "Character(C)",
        "Quest(Q)",
        "Map(M)",
        "Inventory(I)",
        "Spellbook(B)",
        "Menu(Esc)",
    };

    int col = CoordInsideRect(MouseX, MouseY, left_btns_rect)? 0 : 1;
    int row = (MouseY - left_btns_rect.y)/17;

    pnumlines = 0;
    strcpy(infostr, labels[col * 3 + row]);
}


void OnLeftMouseClickPanelButtons()
{
    int col = CoordInsideRect(MouseX, MouseY, left_btns_rect)? 0 : 1;
    int row = (MouseY - left_btns_rect.y)/17;
    int btn_id = col*3 + row;

    if(btn_id == 0) {
        questlog = 0;
        chrflag  = chrflag? 0 : 1;
    }
    else if(btn_id == 1) {
        chrflag  = 0;
        questlog = questlog? 0 : 1;
    }
    else if(btn_id == 2) 
        automapflag = automapflag? 0 : 1;
    else if(btn_id == 3) {
        sbookflag = 0;
        invflag   = invflag? 0 : 1;
    }
    else if(btn_id == 4) {
        invflag   = 0;
        sbookflag = sbookflag? 0 : 1;
    }
}

DEVILUTION_END_NAMESPACE 