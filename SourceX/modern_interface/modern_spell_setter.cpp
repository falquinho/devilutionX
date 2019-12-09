#include "modern_spell_setter.h"
#include "modern_control_panel.h"
#include "modern_spellbar.h"
#include "../Source/spells.h"
#include "../Source/control.h"
#include "utils.h"

DEVILUTION_BEGIN_NAMESPACE

const int MAX_COLS = 19;

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

char spell_setter_title[128];


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
    int num_rows = num_spells? (num_spells/MAX_COLS) + 1 : 0;
    int num_cols = num_rows > 1? MAX_COLS : num_spells;
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

void OpenModernSpellSetter(int slot_index)
{
    target_spell_slot = slot_index;
    SetSpells(plr[myplr]._pAblSpells,  &class_skill[0]);
    SetSpells(plr[myplr]._pMemSpells,  &known_spells[0]);
    SetSpells(plr[myplr]._pScrlSpells, &scroll_spells[0]);
    SetSpells(plr[myplr]._pISpells,    &charge_spell[0]);

    SetSpellsBoundingBoxSizes(&class_skill[0], &class_skill_box);
    SetSpellsBoundingBoxSizes(&known_spells[0], &known_spells_box);
    SetSpellsBoundingBoxSizes(&scroll_spells[0], &scroll_spells_box);
    SetSpellsBoundingBoxSizes(&charge_spell[0], &charge_spell_box);

    PositionSpellsBoxes();

    sprintf(&spell_setter_title[0], "SET SLOT #%d SPELL:", slot_index+1);
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
        if(i == MAX_COLS) {
            left = SCREEN_X + box.x;
            bottom += frame_size;
        }
        CelDraw(left, bottom, spellicons_sm_cel, SpellITbl[spells[i]], frame_size);
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

    Rect title_bkg = {0, class_skill_box.y - 40, (strlen(spell_setter_title) * 6) + 8, 18};
    title_bkg.x = (SCREEN_WIDTH - title_bkg.w) / 2;
    DrawRectangle(title_bkg, PAL16_GRAY + 15, true);
    DrawString(title_bkg.x + 4, title_bkg.y + 2, spell_setter_title);
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


int CursPosToArrayIndex(Rect rect)
{
    int col = (MouseX - rect.x) / frame_size;
    int row = (MouseY - rect.y) / frame_size;
    return (row * MAX_COLS) + col;
}

void OnCursorOverSpellSetter()
{
    if(CoordInsideRect(MouseX, MouseY, class_skill_box)) {
        pnumlines = 0;
        SetSpellInfo(class_skill[0], RSPLTYPE_SKILL);
    }
    else if(CoordInsideRect(MouseX, MouseY, scroll_spells_box )) {
        pnumlines = 0;
        int index = CursPosToArrayIndex(scroll_spells_box);
        SetSpellInfo(scroll_spells[index], RSPLTYPE_SCROLL);
    }
    else if(CoordInsideRect(MouseX, MouseY, charge_spell_box)) {
        pnumlines = 0;
        SetSpellInfo(charge_spell[0], RSPLTYPE_CHARGES);
    }
    else if(CoordInsideRect(MouseX, MouseY, known_spells_box)) {
        pnumlines = 0;
        int index = CursPosToArrayIndex(known_spells_box);
        SetSpellInfo(known_spells[index], RSPLTYPE_SPELL);
    }
}

void OnClickSpellSetter()
{
    int spell_index;
    if(CoordInsideRect(MouseX, MouseY, class_skill_box)) {
        SetSpell(target_spell_slot, class_skill[0], RSPLTYPE_SKILL);
    }
    else if(CoordInsideRect(MouseX, MouseY, scroll_spells_box)) {
        spell_index = CursPosToArrayIndex(scroll_spells_box);
        SetSpell(target_spell_slot, scroll_spells[spell_index], RSPLTYPE_SCROLL);
    }
    else if(CoordInsideRect(MouseX, MouseY, charge_spell_box)) {
        SetSpell(target_spell_slot, charge_spell[0], RSPLTYPE_CHARGES);
    }
    else if(CoordInsideRect(MouseX, MouseY, known_spells_box)) {
        spell_index = CursPosToArrayIndex(known_spells_box);
        SetSpell(target_spell_slot, known_spells[spell_index], RSPLTYPE_SPELL);
    }
    CloseModernSpellSetter();
}

DEVILUTION_END_NAMESPACE