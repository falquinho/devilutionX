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
    {panel_x + 361, panel_y + 48, 16, 16}
};

int meters_rects[][4] = {
    {panel_x +  34, panel_y + 14, 23, 51},
    {panel_x + 329, panel_y + 14, 23, 51}
};

int base_belt_rect[4] = {panel_x + 78, panel_y + 3, 28, 26};

int hovered_element = PANEL_ELEMENT_NONE;
int pressed_element = PANEL_ELEMENT_NONE;

void set_hovered_element()
{
    int i;

    for(i = 0; i < 6; i++) {
        if(CoordInsideRect(MouseX, MouseY, btns_rects[i])) break;
    }
    if(i < 6) {
        hovered_element = i;
        if(pressed_element != hovered_element) pressed_element = PANEL_ELEMENT_NONE;
        return;
    }
    
    for(i = 0; i < 2; i++) {
        if(CoordInsideRect(MouseX, MouseY, meters_rects[i])) break;
    }
    if(i < 2) {
        hovered_element = 6 + i;
        pressed_element = PANEL_ELEMENT_NONE;
        return;
    }

    for(i = 0; i < 8; i++) {
        int curr_belt_slot[4] = {base_belt_rect[0] + (base_belt_rect[2] * i), base_belt_rect[1], base_belt_rect[2], base_belt_rect[3]};
        if(CoordInsideRect(MouseX, MouseY, curr_belt_slot)) {
            hovered_element = 8 + i;
            if(pressed_element != hovered_element) pressed_element = PANEL_ELEMENT_NONE;
            return;
        }
    }

    hovered_element = PANEL_ELEMENT_NONE;
    pressed_element = PANEL_ELEMENT_NONE;
}


void on_mouse_lbtn_up()
{
    if(pressed_element == PANEL_ELEMENT_NONE)
        return;

    if(pressed_element == PANEL_ELEMENT_BTN_INV) {
        invflag = invflag? 0 : 1;
        sbookflag = 0;
    } else if(pressed_element == PANEL_ELEMENT_BTN_SBK) {
        sbookflag = sbookflag? 0 : 1;
        invflag = 0;
    } else if(pressed_element == PANEL_ELEMENT_BTN_CHR) {
        chrflag = chrflag? 0 : 1;
        questlog = 0;
    } else if(pressed_element == PANEL_ELEMENT_BTN_QST) {
        questlog = questlog? 0 : 1;
        chrflag = 0;
    } else if(pressed_element == PANEL_ELEMENT_BTN_MAP)
        automapflag = automapflag? 0 : 1;

    pressed_element = PANEL_ELEMENT_NONE;
}

void modern_input_handler(int event)
{
    printf("MODERN INPUT HANDLER\n");

    set_hovered_element();

    if(event == DVL_WM_LBUTTONDOWN)
        pressed_element = hovered_element;

    else if(event == DVL_WM_LBUTTONUP)
        on_mouse_lbtn_up();
}

DEVILUTION_END_NAMESPACE