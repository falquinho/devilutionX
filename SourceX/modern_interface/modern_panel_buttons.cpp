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

DEVILUTION_END_NAMESPACE 