#include "modern_spell_setter.h"
#include "modern_control_panel.h"
#include "utils.h"

DEVILUTION_BEGIN_NAMESPACE

int  target_spell_slot = -1;

const int margin = 6;

const int frame_size = 34;

int class_skill[MAX_SPELLS] = {};
Rect class_skill_box = {0, 0, 0, 0};

int charge_spell[MAX_SPELLS] = {};
Rect charge_spell_box = {0, 0, 0, 0};

int scroll_spells[MAX_SPELLS] = {};
Rect scroll_spells_box = {0, 0, 0, 0};

int known_spells[MAX_SPELLS]  = {};
Rect known_spells_box = {0, 0, 0, 0};


void SetSpells(unsigned long long int mask, int *spells)
{
    unsigned long long int ctrl_bit = 1;
    int curr_index = -1;
    for(int spell = 1; spell < MAX_SPELLS; ctrl_bit <<= 1, spell++) {
        if(!(ctrl_bit & mask))
            continue;
        spells[++curr_index] = spell;
    } if(curr_index < MAX_SPELLS - 1) {
        spells[++curr_index] = 0;
    }
}

void SetSpellsBoundingBoxSizes(int *spells, Rect *box)
{
    int num_spells = 0;
    for(int i = 0; i < MAX_SPELLS; i++, num_spells++) {
        if(spells[i] == 0)
            break;
    }
    int num_rows = (num_spells/19) + 1;
    int num_cols = num_rows > 1? 19 : num_spells;
    box->w = num_cols * frame_size;
    box->h = num_rows * frame_size;
}

void PositionSpellsBoxes()
{
    known_spells_box.x = (SCREEN_WIDTH - known_spells_box.w) / 2;
    known_spells_box.y = panel_rect.y - known_spells_box.h - 16;

    scroll_spells_box.x = (SCREEN_WIDTH - scroll_spells_box.w) / 2;
    scroll_spells_box.y = known_spells_box.y - scroll_spells_box.h - 16;

    class_skill_box.x = (SCREEN_WIDTH/2) - class_skill_box.w - 8;
    class_skill_box.y = scroll_spells_box.y - class_skill_box.h - 16;

    charge_spell_box.x = (SCREEN_WIDTH/2) + 8;
    charge_spell_box.y = class_skill_box.y;
}

void OpenModernSpellSetter(int spell_index)
{
    target_spell_slot = spell_index;
    SetSpells(plr[myplr]._pAblSpells,  &class_skill[0]);
    SetSpells(plr[myplr]._pMemSpells,  &known_spells[0]);
    SetSpells(plr[myplr]._pScrlSpells, &scroll_spells[0]);
    SetSpells(plr[myplr]._pISpells,    &charge_spell[0]);

    SetSpellsBoundingBoxSizes(&class_skill[0], &class_skill_box);
    SetSpellsBoundingBoxSizes(&known_spells[0], &known_spells_box);
    SetSpellsBoundingBoxSizes(&scroll_spells[0], &scroll_spells_box);
    SetSpellsBoundingBoxSizes(&charge_spell[0], &charge_spell_box);

    PositionSpellsBoxes();
}

void CloseModernSpellSetter()
{
    target_spell_slot = -1;
}

bool IsSpellSetterOpen()
{
    return target_spell_slot >= 0;
}

void DrawSpellsRow(char *label, int spells[], Rect box)
{
    if(!box.w)
        return;

    Rect bkg = box;
    bkg.h += 16; bkg.y -= 14;
    DrawRectangle(bkg, PAL16_GRAY + 15, true);
    DrawString(bkg.x, bkg.y, label);

    int left   = SCREEN_X + box.x;
    int bottom = SCREEN_Y + box.y + frame_size;
    
    for(int i = 0; i < MAX_SPELLS; i++) {
        if(spells[i] == 0)
            break;
        if(i == 19) {
            left = SCREEN_X + box.x;
            bottom += frame_size;
        }
        CelDraw(left, bottom, spellicons_sm_cel, 1, frame_size);
        left += frame_size;
    }
}


void DrawModernSpellSetter()
{
    if(!IsSpellSetterOpen())
        return;
    DrawSpellsRow("Known",   known_spells,  known_spells_box);
    DrawSpellsRow("Scrolls", scroll_spells, scroll_spells_box);
    DrawSpellsRow("Item",    charge_spell,  charge_spell_box);
    DrawSpellsRow("Skill",   class_skill,   class_skill_box);
}


bool CheckCursorOverSpellSetter()
{
    if(!IsSpellSetterOpen())
        return false;
    
    if(
        CoordInsideRect(MouseX, MouseY, known_spells_box)   ||
        CoordInsideRect(MouseX, MouseY, scroll_spells_box ) ||
        CoordInsideRect(MouseX, MouseY, charge_spell_box )  ||
        CoordInsideRect(MouseX, MouseY, class_skill_box )
    )
        return true;

    return false;
}

void OnCursorOverSpellSetter()
{

}

void OnClickSpellSetter()
{

}

DEVILUTION_END_NAMESPACE