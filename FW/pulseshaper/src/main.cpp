#include <Arduino.h>

#include "config.h"
#include "globals.h"
#include "settings.h"
#include "screens.h"

#include "tools-log.h"

void halt(const char*);
void IRAM_ATTR ISR_trigger_rise();
void IRAM_ATTR ISR_trigger_fall();
void IRAM_ATTR ISR_timer();

uint32_t scan_keys();
hw_timer_t * timer = NULL;
// esp_timer_handle_t oneshot;

void IRAM_ATTR ISR_trigger_rise()
{
    // High: Start timer
    timerStart(timer);

    // Next is falling
    usleep(1);
    attachInterrupt(PIN_TRIGGER, ISR_trigger_fall, FALLING);
};
void IRAM_ATTR ISR_trigger_fall()
{
    // make sure timer doesn't fire anymore, pulse was shorter than set amount
    timerStop(timer);

    // re-enable AND-gate
    gpio_set_level(PIN_PORTAND, HIGH);

    // reset timer for next round
    timerWrite(timer, 0);

    // Next is rising
    usleep(1);
    attachInterrupt(PIN_TRIGGER, ISR_trigger_rise, RISING);
};

void IRAM_ATTR ISR_timer()
{
    gpio_set_level(PIN_PORTAND, LOW);

    timerStop(timer);
};

void setup()
{
	Serial.begin(115200);

    // Init IO
	gpio_set_level(PIN_SPEAKER, LOW);
	gpio_set_direction(PIN_SPEAKER, GPIO_MODE_OUTPUT);
	pinMode(PIN_BTN_A, INPUT_PULLUP);
	pinMode(PIN_BTN_B, INPUT_PULLUP);
	pinMode(PIN_BTN_C, INPUT_PULLUP);
    pinMode(PIN_TRIGGER, INPUT);
    pinMode(PIN_ENABLE, INPUT);
    gpio_set_level(PIN_PORTAND, HIGH);
    pinMode(PIN_PORTAND, OUTPUT);

    // Hold on key-press
    while(scan_keys() == KEY_AB);

    // Init globals
    pulselen = PULSELEN_DEFAULT;
    state = STATE_OFF;

    // Start up GUI
	gui.begin();

    // Initialize sensors etc
    attachInterrupt(PIN_TRIGGER, ISR_trigger_rise, RISING);

    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &ISR_timer, false);
    timerStop(timer);
    timerAlarmWrite(timer, pulselen, true);
    timerAlarmDisable(timer);

    // Bootstrap the GUI
    ScreenPtr scr = std::make_shared<BootScreen>(gui);
    gui.pushScreen(scr);

    DBG("setup() done.");
};

void loop()
{
    soogh_event_t e = static_cast<soogh_event_t>(key2event(scan_keys()));

    static uint32_t prv_pulselen = 0;
    if(pulselen != prv_pulselen)
    {
        timerAlarmWrite(timer, pulselen - PULSELEN_CORRECTION, true);
        prv_pulselen = pulselen;
    };

    int new_enabled = digitalRead(PIN_ENABLE);
    if(new_enabled != enabled)
    {
        if(new_enabled == HIGH)
        {
            timerAlarmEnable(timer);
            enabled = HIGH;
        }else{
            timerAlarmDisable(timer);
            enabled = LOW;
        };
    };

	gui.handle(e);

	setman.loop();
	gui.loop();
};


void halt(const char* error)
{
	gui.showMessage("ERROR:", error);
	// DBG("HALT: %s", error);
	while(true)
		gui.loop();
};

uint32_t scan_keys()
{
	// Read current states
	uint32_t pressed = KEY_NONE;
	if(digitalRead(PIN_BTN_A) == LOW)
		pressed |= KEY_A;
	if(digitalRead(PIN_BTN_B) == LOW)
		pressed |= KEY_B;
	if(digitalRead(PIN_BTN_C) == LOW)
		pressed |= KEY_C;
	// if(digitalRead(PIN_POWERINT) == LOW)
	// 	pressed |= KEY_P;
	return pressed;
};
