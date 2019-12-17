#include "devilution.h"
#include "utils.h"
#include "../Source/inv.h"

DEVILUTION_BEGIN_NAMESPACE

#define MAX_COMPARE_LINES 7

char compare_info[MAX_COMPARE_LINES][128] = {"", "", "", "", "", "", ""};

char compare_loc = NUM_INVLOC;


void DrawMonsterInfo()
{
    int str_box_w = strlen(infostr) * CHAR_W;
    Rect bkg = {(SCREEN_WIDTH - str_box_w)/2, 4, str_box_w, CHAR_H};
    DrawRectangle(bkg, PAL16_GRAY + 15, true);
    DrawString((SCREEN_WIDTH - bkg.w)/2, 4, infostr);

    for(int i = 0; i < pnumlines; i++) {
        bkg.w = strlen(&panelstr[64 * i]) * CHAR_W;
        bkg.y = 4 + CHAR_H + (CHAR_H * i);
        bkg.x = (SCREEN_WIDTH - bkg.w)/2;
        DrawRectangle(bkg, PAL16_GRAY + 15, true);
        DrawString(bkg.x, bkg.y, &panelstr[64 * i]);
    }
}


void DrawCompareEquipInfo(Rect sister_rect)
{
    Rect bkg = {0, 0, 0, 0};
    for(int i = 0; i < MAX_COMPARE_LINES; i++){
        if(compare_info[i][0] == '\0')
            break;
        int curr_w = strlen(&compare_info[i][0])*CHAR_W + 4;
        bkg.w = curr_w > bkg.w? curr_w : bkg.w;
        bkg.h = ((i + 2) * CHAR_H) + 4;
    }

    bkg.x = sister_rect.x - bkg.w - 4;
    bkg.y = sister_rect.y;

    DrawRectangle(bkg, PAL16_GRAY+15, false);

    int offset = (bkg.w - (9*CHAR_W))/2;
    DrawString(bkg.x + offset, bkg.y, "EQUIPPED:");
    for(int i = 0; i < MAX_COMPARE_LINES; i++) {
        if(compare_info[i][0] == '\0')
            break;
        offset = (bkg.w - (strlen(&compare_info[i][0]) * CHAR_W))/2;
        DrawString(bkg.x + offset, bkg.y + (CHAR_H * (i + 1)), &compare_info[i][0]);
    }
}


void DrawModernInfoBox()
{
    if(!infostr[0])
        return;
    
    if(pcursmonst >= 0 &&  leveltype != DTYPE_TOWN)
        return DrawMonsterInfo();

    Rect box_rect;
    
    box_rect.h = ((1 + pnumlines) * CHAR_H) + 4;
    box_rect.w = strlen(infostr) * CHAR_W;

    int i;
    for (i = 0; i < pnumlines; i++) {
        int curr_line_width = strlen(&panelstr[64 * i]) * CHAR_W;
        box_rect.w = curr_line_width > box_rect.w? curr_line_width : box_rect.w;
    }
    box_rect.w += 4;

    box_rect.x = MouseX;
    box_rect.y = MouseY - box_rect.h;
    PositionRectInScreen(&box_rect);

    DrawRectangle(box_rect, PAL16_GRAY + 15, false);

    int offset = (box_rect.w - strlen(infostr) * CHAR_W)/2;
    DrawString(box_rect.x + offset, box_rect.y + 2, infostr);

    for (i = 0; i < pnumlines; i++) {
        offset = (box_rect.w - strlen(&panelstr[64 * i]) * CHAR_W)/2;
        DrawString(box_rect.x + offset, box_rect.y + 2 + ((i + 1) * CHAR_H), &panelstr[64 * i]);
    }

    if(compare_info[0][0] != '\0' && pcurs == CURSOR_HAND)
        DrawCompareEquipInfo(box_rect);
}


void ClearComparisonInfo()
{
    for(int i = 0; i < MAX_COMPARE_LINES; i++) {
        compare_info[i][0] = '\0';
    }
    compare_loc = NUM_INVLOC;
}


void SetCompareEquipmentInfo(ItemStruct item)
{
    ClearComparisonInfo();

    if(item._itype == ITYPE_NONE)
        return;

    char inv_loc;
    if(item._iLoc == ILOC_HELM)
        inv_loc = INVLOC_HEAD;

    else if(item._iLoc == ILOC_ARMOR)
        inv_loc = INVLOC_CHEST;

    else if(item._iLoc == ILOC_TWOHAND)
        inv_loc = INVLOC_HAND_LEFT;

    else if(item._iLoc == ILOC_ONEHAND && item._iClass == ICLASS_WEAPON)
        inv_loc = INVLOC_HAND_LEFT;

    else if(item._iLoc == ILOC_ONEHAND && item._iClass == ICLASS_ARMOR)
        inv_loc = INVLOC_HAND_RIGHT;

    else if(item._iLoc == ILOC_AMULET)
        inv_loc = INVLOC_AMULET;

    else if(item._iLoc == ILOC_RING) {
        inv_loc = INVLOC_RING_LEFT;
        ItemStruct item = plr[myplr].InvBody[inv_loc];
        if(item._itype == ITYPE_NONE)
            inv_loc = INVLOC_RING_RIGHT;
    }
    else
        return;

    ItemStruct target_item = plr[myplr].InvBody[inv_loc];

    if(target_item._itype == ITYPE_NONE)
        return;
    
    compare_loc = inv_loc;

    strcpy(&compare_info[0][0], target_item._iIName);

    int curr_line = 1;
    if (target_item._iClass == ICLASS_WEAPON) {
		if (target_item._iMaxDur == DUR_INDESTRUCTIBLE)
			sprintf(&compare_info[curr_line++][0], "damage: %i-%i  Indestructible", target_item._iMinDam, target_item._iMaxDam);
		else
			sprintf(&compare_info[curr_line++][0], "damage: %i-%i  Dur: %i/%i", target_item._iMinDam, target_item._iMaxDam, target_item._iDurability, target_item._iMaxDur);
	}
	else if (target_item._iClass == ICLASS_ARMOR) {
		if (target_item._iMaxDur == DUR_INDESTRUCTIBLE)
			sprintf(&compare_info[curr_line++][0], "armor: %i  Indestructible", target_item._iAC);
		else
			sprintf(&compare_info[curr_line++][0], "armor: %i  Dur: %i/%i", target_item._iAC, target_item._iDurability, target_item._iMaxDur);
	}

    if(target_item._iPrePower != -1) {
        PrintItemPower(target_item._iPrePower, &target_item);
        sprintf(&compare_info[curr_line++][0], "%s", tempstr);
    }

    if(target_item._iSufPower != -1) {
        PrintItemPower(target_item._iSufPower, &target_item);
        sprintf(&compare_info[curr_line++][0], "%s", tempstr);
    }

    if (target_item._iMagical == ITEM_QUALITY_UNIQUE)
		sprintf(&compare_info[curr_line++][0], "Unique item.");
	
    if (target_item._iMinMag + target_item._iMinDex + target_item._iMinStr) {
		strcpy(tempstr, "Required:");
		if (target_item._iMinStr)
			sprintf(tempstr, "%s %i Str", tempstr, target_item._iMinStr);
		if (target_item._iMinMag)
			sprintf(tempstr, "%s %i Mag", tempstr, target_item._iMinMag);
		if (target_item._iMinDex)
			sprintf(tempstr, "%s %i Dex", tempstr, target_item._iMinDex);
		sprintf(&compare_info[curr_line][0], tempstr);
	}
}

DEVILUTION_END_NAMESPACE