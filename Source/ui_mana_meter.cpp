#include "all.h"

DEVILUTION_BEGIN_NAMESPACE

BYTE *manaMeterEmptyGfx;

void LoadManaMeter()
{
    manaMeterEmptyGfx = DiabloAllocPtr(88 * 88);
    memset(manaMeterEmptyGfx, 0, 88 * 88);

    BYTE *emptyFlasksCel = LoadFileInMem("CtrlPan\\P8Bulbs.CEL", NULL);
	CelBlitWidth(manaMeterEmptyGfx, 0, 87, 88, emptyFlasksCel, 2, 88);
}

void FreeManaMeter()
{
    MemFreeDbg(manaMeterEmptyGfx);
}

void DrawManaMeter()
{
    int filled = plr[myplr]._pManaPer;
	if (filled > 80)
		filled = 80;
	if (filled < 0)
        filled = 0;
    BYTE *src = &manaMeterEmptyGfx[0];
    BYTE *dst = &gpBuffer[SCREENXY(PANEL_LEFT + 368, PANEL_TOP - 16)];
    for (int i = 0; i < 82 - filled; i++, dst += BUFFER_WIDTH) {
        for (int j = 0; j < 88; j++, src++) {
            if(*src)
                dst[j] = *src;
        }
    }
}

DEVILUTION_END_NAMESPACE