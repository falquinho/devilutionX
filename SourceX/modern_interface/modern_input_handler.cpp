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

int panel_elements_rects[][4] = {
    {panel_x +   9, panel_y + 14, 16, 16}, // character button
    {panel_x +   9, panel_y + 31, 16, 16}, // quest button 
    {panel_x +   9, panel_y + 48, 16, 16}, // map button
    {panel_x + 361, panel_y + 14, 16, 16}, // inventory button
    {panel_x + 361, panel_y + 31, 16, 16}, // spellbook button
    {panel_x + 361, panel_y + 48, 16, 16}, // menu button
    {panel_x +  34, panel_y + 14, 23, 51}, // life meter  
    {panel_x + 329, panel_y + 14, 23, 51}, // mana meter
    {panel_x + 78 + (28*0), panel_y + 3, 28, 26}, // belt item 1
    {panel_x + 78 + (28*1), panel_y + 3, 28, 26}, // belt item 2 
    {panel_x + 78 + (28*2), panel_y + 3, 28, 26}, // belt item 3 
    {panel_x + 78 + (28*3), panel_y + 3, 28, 26}, // belt item 4 
    {panel_x + 78 + (28*4), panel_y + 3, 28, 26}, // belt item 5 
    {panel_x + 78 + (28*5), panel_y + 3, 28, 26}, // belt item 6 
    {panel_x + 78 + (28*6), panel_y + 3, 28, 26}, // belt item 7 
    {panel_x + 78 + (28*7), panel_y + 3, 28, 26}, // belt item 8
    {panel_x + 71 + (42 * 0), panel_y + 35, 34, 34}, // spell 1
    {panel_x + 71 + (42 * 1), panel_y + 35, 34, 34}, // spell 2
    {panel_x + 71 + (42 * 2), panel_y + 35, 34, 34}, // spell 3
    {panel_x + 71 + (42 * 3), panel_y + 35, 34, 34}, // spell 4
    {panel_x + 71 + (42 * 4), panel_y + 35, 34, 34}, // spell 5
    {panel_x + 71 + (42 * 5), panel_y + 35, 34, 34}, // spell 6
};

int hovered_element = PANEL_ELEMENT_NONE;
int pressed_element = PANEL_ELEMENT_NONE;

void set_hovered_element()
{
    int i;
    for(i = PANEL_ELEMENT_BTN_CHR; i < PANEL_ELEMENT_NONE; i++) {
        if(CoordInsideRect(MouseX, MouseY, panel_elements_rects[i])) 
            break;
    }
    hovered_element = i;
    if(pressed_element != hovered_element)
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