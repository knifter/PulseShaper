#include "globals.h"

#include "gui.h"
#include "settings.h"

GUI gui;
settings_t settings;
SettingsManager setman(settings);

volatile uint32_t   pulselen;
volatile state_t    state;
volatile bool       enabled;
