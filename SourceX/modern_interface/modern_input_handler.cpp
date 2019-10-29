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

void modern_input_handler()
{
    printf("MODERN INPUT HANDLER\n");
    check_mouse_over();
}

DEVILUTION_END_NAMESPACE