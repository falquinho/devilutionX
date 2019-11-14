#include "devilution.h"
#include "utils.h"

DEVILUTION_BEGIN_NAMESPACE

int char_width  = 6;

int char_height = 12;


void DrawMonsterInfo()
{
    int str_box_w = strlen(infostr) * char_width;
    Rect bkg = {(SCREEN_WIDTH - str_box_w)/2, 4, str_box_w, char_height};
    DrawRectangle(bkg, PAL16_GRAY + 15, true);
    DrawString((SCREEN_WIDTH - str_box_w)/2, 4, infostr);

    for(int i = 0; i < pnumlines; i++) {
        bkg.w = strlen(&panelstr[64 * i]) * char_width;
        bkg.y = 4 + char_height + (char_height * i);
        bkg.x = (SCREEN_WIDTH - str_box_w)/2;
        DrawRectangle(bkg, PAL16_GRAY + 15, true);
        DrawString(bkg.x, bkg.y, &panelstr[64 * i]);
    }
}


void DrawModernInfoBox()
{
    if(!infostr[0])
        return;
    
    if(pcursmonst >= 0 &&  leveltype != DTYPE_TOWN)
        return DrawMonsterInfo();

    Rect box_rect;
    
    box_rect.h = ((1 + pnumlines) * char_height) + 4;
    box_rect.w = strlen(infostr) * char_width;

    int i;
    for (i = 0; i < pnumlines; i++) {
        int curr_line_width = strlen(&panelstr[64 * i]) * char_width;
        box_rect.w = curr_line_width > box_rect.w? curr_line_width : box_rect.w;
    }
    box_rect.w += 4;

    box_rect.x = MouseX;
    box_rect.y = MouseY - box_rect.h;
    PositionRectInScreen(&box_rect);

    DrawRectangle(box_rect, PAL16_GRAY + 15, true);

    DrawString(box_rect.x + 2, box_rect.y + 2, infostr);

    for (i = 0; i < pnumlines; i++) {
        DrawString(box_rect.x + 2, box_rect.y + 2 + ((i + 1) * char_height), &panelstr[64 * i]);
    }
}

DEVILUTION_END_NAMESPACE