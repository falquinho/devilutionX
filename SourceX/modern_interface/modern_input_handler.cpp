#include "../../SourceS/devilution.h"
#include "modern_input_handler.h"
#include "modern_control_panel.h"
#include "utils.h"

DEVILUTION_BEGIN_NAMESPACE

int panel_x = (SCREEN_WIDTH - panel_width)/2;
int panel_y = SCREEN_HEIGHT - 72 - 8;

char* btns_tips[] = {
    "CHARACTER(A)",
    "QUESTS(S)",
    "MAP(D)",
    "INVENTORY(Z)",
    "SPELLBOOK(X)",
    "MENU(C)"
};

int btns_rects[][4] = {
    {panel_x +   9, panel_y + 14, 16, 16},
    {panel_x +   9, panel_y + 31, 16, 16},
    {panel_x +   9, panel_y + 48, 16, 16},
    {panel_x + 361, panel_y + 14, 16, 16},
    {panel_x + 361, panel_y + 31, 16, 16},
    {panel_x + 361, panel_y + 48, 16, 16},
};

int btn_hovered = 6;
int btn_pressed = 6;

void check_mouse_over()
{
    int i;
    for(i = 0; i < 6; i++) {
        if(CoordInsideRect(MouseX, MouseY, btns_rects[i]))
            break;
    }
    if(btn_hovered != i)
        btn_pressed = 6;

    btn_hovered = i;
}


void on_mouse_lbtn_up()
{
    if(btn_pressed == 3) {
        invflag = invflag? 0 : 1;
    } else if(btn_pressed == 4) {
        sbookflag = sbookflag? 0 : 1;
    }

    btn_pressed = 6;
}

void modern_input_handler(int event)
{
    printf("MODERN INPUT HANDLER\n");

    check_mouse_over();

    if(event == DVL_WM_LBUTTONDOWN)
        btn_pressed = btn_hovered;

    else if(event == DVL_WM_LBUTTONUP)
        on_mouse_lbtn_up();
}

DEVILUTION_END_NAMESPACE