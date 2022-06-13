#ifndef __CONFIG_H
#define __CONFIG_H

#include <Arduino.h>

#define _STRINGIFY(x)      #x
#define STRINGIFY(x)      _STRINGIFY(x)

#define VERSION                BUILD_DATETIME
#define VERSIONSTR_LONG        STRINGIFY(GIT_BRANCH-VERSION)
#define VERSIONSTR_SHORT       STRINGIFY(VERSION)

#ifdef DEBUG
	// Enable DBG(...) globally:
	// #define TOOLS_LOG_DEBUG

	// Or per file:
	#define DEBUG_MAIN_CPP

	// Specific parts:
#endif

#define BOOTSCREEN_TIMEOUT_MS   2000
#define PULSELEN_MIN            35
#define PULSELEN_MAX            4000
#define PULSELEN_DEFAULT        160
#define PULSELEN_CORRECTION     4          // subtracted from pulselen to correct for context-switching

// PINS M5CORE2
// #define PIN_SCLK				GPIO_NUM_18
// #define PIN_MOSI				GPIO_NUM_23
// #define PIN_MISO				GPIO_NUM_38
// #define PIN_RXD0                GPIO_NUM_3
// #define PIN_TXD0                GPIO_NUM_1
// #define PIN_RXD2                GPIO_NUM_13
// #define PIN_TXD2                GPIO_NUM_14
// #define PIN_INT_SDA             GPIO_NUM_21
// #define PIN_INT_SCL             GPIO_NUM_22
// #define PIN_SDA                 GPIO_NUM_32
// #define PIN_SCL                 GPIO_NUM_33

// PINS M5Core
// #define PIN_SCLK				GPIO_NUM_18
// #define PIN_MOSI				GPIO_NUM_23
// #define PIN_MISO				GPIO_NUM_19
// #define PIN_RXD0                GPIO_NUM_3
// #define PIN_TXD0                GPIO_NUM_1
// #define PIN_RXD2                GPIO_NUM_16
// #define PIN_TXD2                GPIO_NUM_17
// #define PIN_SDA                 GPIO_NUM_21
// #define PIN_SCL                 GPIO_NUM_22
#define PIN_BTN_A				GPIO_NUM_39
#define PIN_BTN_B 				GPIO_NUM_38
#define PIN_BTN_C 				GPIO_NUM_37

#define PIN_SPEAKER             GPIO_NUM_25

#define PIN_TRIGGER             GPIO_NUM_15
#define PIN_PORTAND             GPIO_NUM_13
#define PIN_ENABLE              GPIO_NUM_34


#endif // __CONFIG_H

