#include "all.h"

DEVILUTION_BEGIN_NAMESPACE

BYTE *panelGfx;

void LoadMainPanel()
{
    panelGfx = LoadFileInMem("CtrlPan\\Panel8.CEL", NULL);
}

void FreeMainPanel()
{
    MemFreeDbg(panelGfx);
}

void DrawMainPanel()
{
    
}

DEVILUTION_END_NAMESPACE