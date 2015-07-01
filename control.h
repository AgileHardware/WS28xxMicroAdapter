#ifndef __control_h__
#define __control_h__


#include <Arduino.h>
#include "constants.h"
#include "settings.h"


void setupButtons();
void checkButtons();

uint8_t getParamCycles();
uint8_t getParamBrightness();
uint8_t getParamColorIndex();
uint8_t getParamProgram();

uint16_t getCurrentEditingParam();
uint8_t  getCurrentEditingValue();
bool     isStateVisible();


#endif