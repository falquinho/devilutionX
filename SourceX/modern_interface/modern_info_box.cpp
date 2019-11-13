#include "devilution.h"
#include "utils.h"

DEVILUTION_BEGIN_NAMESPACE

int char_width  = 6;
int char_height = 12;
void DrawModernInfoBox()
{
    if(!infostr[0])
        return;

    int box_h = ((1 + pnumlines) * char_height) + 4;
    int box_w = strlen(infostr) * char_width;

    int i;
    for (i = 0; i < pnumlines; i++) {
        box_w = strlen(&panelstr[64 * i]) * char_width > box_w? strlen(&panelstr[64 * i]) * char_width: box_w;
    }
    box_w += 4;

    int box_rect[4] = {MouseX, MouseY - box_h, box_w, box_h};
    PositionRectInScreen(box_rect);

    DrawRectangle(box_rect, PAL16_GRAY + 15, true);

    DrawString(box_rect[0] + 2, box_rect[1] + 2, infostr);

    for (i = 0; i < pnumlines; i++) {
        DrawString(box_rect[0] + 2, box_rect[1] + 2 + ((i + 1) * char_height), &panelstr[64 * i]);
    }
}

DEVILUTION_END_NAMESPACE