#ifndef __MODERNCONTROLPANEL_H__
#define __MODERNCONTROLPANEL_H__

#include "../../SourceS/devilution.h"

DEVILUTION_BEGIN_NAMESPACE

extern BYTE* ctrl_panel_cel;

extern int panel_width;  
extern int panel_left;   
extern int panel_bottom; 

void load_modern_control_panel();

void draw_modern_control_panel();

void unload_modern_control_panel();

DEVILUTION_END_NAMESPACE
#endif //__MODERNCONTROLPANEL_H__s