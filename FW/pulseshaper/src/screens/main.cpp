#include "screens.h"

#include <memory>
#include <soogh.h>

#include "gui.h"

#include "config.h"
#include "tools-log.h"
#include "globals.h"

#include <treemenu.h>

// C-style callbacks

/*********************************************************************************************************************************/
MainScreen::MainScreen(SooghGUI& g) : Screen(g)
{
    lbl_len = lv_label_create(_screen);
    lv_obj_set_size(lbl_len, LV_PCT(100), 20);
	lv_obj_align(lbl_len, LV_ALIGN_TOP_LEFT, 5, 5);
    lv_obj_set_style_text_align(lbl_len, LV_TEXT_ALIGN_LEFT, 0);

    lbl_enable = lv_label_create(_screen);
    lv_obj_set_size(lbl_len, LV_PCT(100), 20);
    lv_obj_align_to(lbl_enable, lbl_len, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_obj_set_style_text_align(lbl_enable, LV_TEXT_ALIGN_LEFT, 0);
};

void MainScreen::loop()
{
    lv_label_set_text_fmt(lbl_enable, "Shortened: %s", enabled ? "YES" : "NO");
    return;
};

bool MainScreen::handle(soogh_event_t key)
{
    static uint32_t oldlen = pulselen;
	switch(key)
	{
        case KEY_A_SHORT:
            pulselen -= 1;
            break;
        case KEY_A_LONG:
        case KEY_A_LONG_REPEAT:
            pulselen -= 10;
            break;
        case KEY_B_SHORT:
            pulselen = 100;
            // pulse_on = ~pulse_on;
            break;
        case KEY_C_SHORT:
            pulselen += 1;
            break;
        case KEY_C_LONG:
        case KEY_C_LONG_REPEAT:
            pulselen += 10;
            break;
        default: break;
    };
    if(oldlen != pulselen)
    {
        if(pulselen < PULSELEN_MIN)
            pulselen = PULSELEN_MIN;
        if(pulselen > PULSELEN_MAX)
            pulselen = PULSELEN_MAX;
        lv_label_set_text_fmt(lbl_len, "Pulse length: %d", pulselen);
        return true;
    };
	return false;
};
