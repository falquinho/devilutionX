#include "devilution.h"
#include "utils.h"

DEVILUTION_BEGIN_NAMESPACE

void DrawModernInfoBox()
{
    DrawString(MouseX, MouseY, infostr);
}

DEVILUTION_END_NAMESPACE