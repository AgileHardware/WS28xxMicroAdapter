#ifndef __state_display_h__
#define __state_display_h__


#include <Arduino.h>
#include "constants.h"
#include "settings.h"
#include "leds.h"

uint16_t drawState(uint16_t stateTick, uint8_t editingParameter, uint8_t value);

#endif