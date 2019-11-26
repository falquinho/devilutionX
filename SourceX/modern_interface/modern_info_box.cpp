#include "devilution.h"
#include "utils.h"

DEVILUTION_BEGIN_NAMESPACE

int char_width  = 6;

int char_height = 12;

char compare_info[4][128] = {"", "", "", ""};


void DrawMonsterInfo()
{
    int str_box_w = strlen(infostr) * char_width;
    Rect bkg = {(SCREEN_WIDTH - str_box_w)/2, 4, str_box_w, char_height};
    DrawRectangle(bkg, PAL16_GRAY + 15, true);
    DrawString((SCREEN_WIDTH - bkg.w)/2, 4, infostr);

    for(int i = 0; i < pnumlines; i++) {
        bkg.w = strlen(&panelstr[64 * i]) * char_width;
        bkg.y = 4 + char_height + (char_height * i);
        bkg.x = (SCREEN_WIDTH - bkg.w)/2;
        DrawRectangle(bkg, PAL16_GRAY + 15, true);
        DrawString(bkg.x, bkg.y, &panelstr[64 * i]);
    }
}


void DrawCompareEquipInfo()
{
    Rect bkg = {0, 0, 0, 0};
    for(int i = 0; i < 4; i++){
        if(compare_info[i][0] == '\0')
            break;
        bkg.w = strlen(&compare_info[i][0])*char_width > bkg.w? strlen(&compare_info[i][0])*char_width : bkg.w;
        bkg.h = (i + 2) * char_height;
    }
    DrawRectangle(bkg, PAL16_GRAY+15, false);
    for(int i = 0; i < 4; i++) {
        if(compare_info[i][0] == '\0')
            break;
        DrawString(2, 2 + (char_height*i), &compare_info[i][0]);
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

    int offset = (box_rect.w - strlen(infostr) * char_width)/2;
    DrawString(box_rect.x + offset, box_rect.y + 2, infostr);

    for (i = 0; i < pnumlines; i++) {
        offset = (box_rect.w - strlen(&panelstr[64 * i]) * char_width)/2;
        DrawString(box_rect.x + offset, box_rect.y + 2 + ((i + 1) * char_height), &panelstr[64 * i]);
    }

    if(compare_info[0][0] != '\0')
        DrawCompareEquipInfo();
}


void ClearComparisonInfo()
{
    compare_info[0][0] = '\0';
}


void SetCompareEquipmentInfo(ItemStruct item)
{
    ClearComparisonInfo();

    if(item._itype == ITYPE_NONE)
        return;

    ItemStruct target_item;
    if(item._iLoc == ILOC_HELM)
        target_item = plr[myplr].InvBody[INVLOC_HEAD];

    else if(item._iLoc == ILOC_ARMOR)
        target_item = plr[myplr].InvBody[INVLOC_CHEST];

    else if(item._iLoc == ILOC_TWOHAND)
        target_item = plr[myplr].InvBody[INVLOC_HAND_LEFT];

    else if(item._iLoc == ILOC_ONEHAND && item._iClass == ICLASS_WEAPON)
        target_item = plr[myplr].InvBody[INVLOC_HAND_LEFT];

    else if(item._iLoc == ILOC_ONEHAND && item._iClass == ICLASS_ARMOR)
        target_item = plr[myplr].InvBody[INVLOC_HAND_RIGHT];

    else if(item._iLoc == ILOC_AMULET)
        target_item = plr[myplr].InvBody[INVLOC_AMULET];

    else if(item._iLoc == ILOC_RING) {
        target_item = plr[myplr].InvBody[INVLOC_RING_LEFT];
        if(target_item._itype == ITYPE_NONE)
            target_item = plr[myplr].InvBody[INVLOC_RING_RIGHT];
    }
    else
        return;

    if(target_item._itype == ITYPE_NONE)
        return;
    
    strcpy(&compare_info[0][0], target_item._iName);

    if (target_item._iClass == ICLASS_WEAPON) {
		if (target_item._iMaxDur == DUR_INDESTRUCTIBLE)
			sprintf(&compare_info[1][0], "damage: %i-%i  Indestructible", target_item._iMinDam, target_item._iMaxDam);
		else
			sprintf(&compare_info[1][0], "damage: %i-%i  Dur: %i/%i", target_item._iMinDam, target_item._iMaxDam, target_item._iDurability, target_item._iMaxDur);
	}
	else if (target_item._iClass == ICLASS_ARMOR) {
		if (target_item._iMaxDur == DUR_INDESTRUCTIBLE)
			sprintf(&compare_info[1][0], "armor: %i  Indestructible", target_item._iAC);
		else
			sprintf(&compare_info[1][0], "armor: %i  Dur: %i/%i", target_item._iAC, target_item._iDurability, target_item._iMaxDur);
	}
}

DEVILUTION_END_NAMESPACE