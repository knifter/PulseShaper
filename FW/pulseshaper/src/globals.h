#ifndef __GLOBALS_H
#define __GLOBALS_H

#include "gui.h"
#include "settings.h"

extern settings_t settings;
extern SettingsManager setman;
extern GUI gui;

typedef enum
{
    STATE_OFF,
    STATE_GOTO_ON,
    STATE_ON,
    STATE_GOTO_OFF
} state_t;

extern volatile uint32_t    pulselen;
extern volatile bool        enabled;
extern volatile state_t     state;

#endif //__GLOBALS_H
