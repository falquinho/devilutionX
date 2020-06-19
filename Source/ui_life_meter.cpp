#include "all.h"

DEVILUTION_BEGIN_NAMESPACE

BYTE *lifeMeterEmptyGfx;

void LoadLifeMeter()
{
    lifeMeterEmptyGfx = DiabloAllocPtr(88 * 88);
    BYTE *emptyFlasksCel = LoadFileInMem("CtrlPan\\P8Bulbs.CEL", NULL);
    CelBlitWidth(lifeMeterEmptyGfx, 0, 87, 88, emptyFlasksCel, 1, 88);
}

void FreeLifeMeter()
{
    MemFreeDbg(lifeMeterEmptyGfx);
}

void DrawLifeMeter()
{
    int filled = (double)plr[myplr]._pHitPoints / (double)plr[myplr]._pMaxHP * 80.0;
	if (filled > 80)
		filled = 80;
	if (filled < 0)
        filled = 0;
    
    BYTE *src = &lifeMeterEmptyGfx[0];
    BYTE *dst = &gpBuffer[SCREENXY(PANEL_LEFT + 96, PANEL_TOP - 16)];
    for (int i = 0; i < 82 - filled; i++, dst += BUFFER_WIDTH) {
        for (int j = 0; j < 88; j++, src++) {
            if(*src)
                dst[j] = *src;
        }
    }
}

DEVILUTION_END_NAMESPACE