#include "modern_spell_setter.h"
#include "modern_control_panel.h"
#include "utils.h"

DEVILUTION_BEGIN_NAMESPACE

int  target_spell_slot = -1;

const int margin = 6;

const int frame_size = 34;

int learned_spells_id[MAX_SPELLS] = {};
int num_learned_spells = 0;
Rect learned_spells_box = {-1, -1, 0, 0};

Rect scroll_spells_box  = {-1, -1, 0, 0};
Rect charge_spells_box  = {-1, -1, 0, 0};

void SetLearnedSpells()
{
    unsigned long long int mask = plr[myplr]._pMemSpells;
    unsigned long long int ctrl_bit = 1;
    num_learned_spells = 1; // always knows at least the class skill
    int index = -1;
    for(int spell_id = 1; spell_id < 32; spell_id++, ctrl_bit <<= 1) {
        // if(!(ctrl_bit & mask))
        //     continue;
        index++;
        num_learned_spells++;
        learned_spells_id[index] = spell_id;
    }
    learned_spells_box.w = (num_learned_spells > 19? 19 : num_learned_spells) * frame_size;
    learned_spells_box.x = (SCREEN_WIDTH - learned_spells_box.w) / 2;
    learned_spells_box.h = frame_size * (num_learned_spells > 19? 2 : 1);
    learned_spells_box.y = panel_rect.y - margin - learned_spells_box.h;
}

void OpenModernSpellSetter(int spell_index)
{
    target_spell_slot = spell_index;
    SetLearnedSpells();
}

void CloseModernSpellSetter()
{
    target_spell_slot = -1;
}

bool IsSpellSetterOpen()
{
    return target_spell_slot >= 0;
}

bool CheckCursorOverSpellSetter()
{
    if(!IsSpellSetterOpen())
        return false;
    
    if(
        CoordInsideRect(MouseX, MouseY, learned_spells_box) ||
        CoordInsideRect(MouseX, MouseY, scroll_spells_box ) ||
        CoordInsideRect(MouseX, MouseY, charge_spells_box )
    )
        return true;

    return false;
}

void DrawLearnedSpellsRow()
{
    Rect bkg = learned_spells_box;
    bkg.w = bkg.w < 14 * 6? 14 * 6 + 6 : bkg.w + 6;
    bkg.x = ((SCREEN_WIDTH - bkg.w) / 2) + 3;
    bkg.h += 14;
    bkg.y -= 11;
    DrawRectangle(bkg, PAL16_GRAY + 15, true);
    DrawString(bkg.x + 3, bkg.y, "LEARNED SPELLS");

    int left = learned_spells_box.x + SCREEN_X;
    int bottom = learned_spells_box.y + SCREEN_Y + frame_size;
    for(int i = 0; i < num_learned_spells; i++, left += frame_size){
        if(i == 19) {
            left = learned_spells_box.x + SCREEN_X;
            bottom += frame_size;
        }
        CelDraw(left, bottom, spellicons_sm_cel, i+1, frame_size);
    }
}


void DrawModernSpellSetter()
{
    if(target_spell_slot < 0)
        return;

    DrawLearnedSpellsRow();
}

void OnCursorOverSpellSetter()
{

}

void OnClickSpellSetter()
{

}

DEVILUTION_END_NAMESPACE