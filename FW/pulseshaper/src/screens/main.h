#ifndef __SCREENS_MAIN_H
#define __SCREENS_MAIN_H

#include <stdlib.h>
#include <stdint.h>

#include <soogh.h>

#include "gui.h"

/*** MAIN ************************************************************************************/
class MainScreen : public Screen
{
    public:
		MainScreen(SooghGUI& g);

		virtual ScreenType type() { return ScreenType::MAIN; };

        virtual void loop();
		virtual bool handle(soogh_event_t);
	
	private:
        lv_obj_t *lbl_len, *lbl_enable;
};

#endif // __SCREENS_MAIN_H
