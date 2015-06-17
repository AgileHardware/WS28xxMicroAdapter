#include "control.h"

uint8_t cycles     = 4;
uint8_t colorIndex = 0;
uint8_t program    = 16;
uint8_t brightness = 0;

// the parameter that is currently being edited, see list of parameter constants
uint8_t editingParameter = 0;

// global variables for button reading / debouncing
// adapted from example code at http://arduino.cc/en/Tutorial/Debounce
// Index to pin mapping:
// 0: Cycle editing parameter
// 1: Decrement parameter
// 2: Increment parameter
bool buttonState[NUM_BUTTONS];
bool lastButtonState[NUM_BUTTONS]   = {HIGH, HIGH, HIGH};
long lastDebounceTime[NUM_BUTTONS]  = {0,0,0};
uint8_t debounceDelay               = 20;
long showStateTimeout          = millis();



void setupButtons() {
  pinMode(PIN_PROGRAM, INPUT_PULLUP);
  pinMode(PIN_COLOR,   INPUT_PULLUP);
  pinMode(PIN_CYCLES,  INPUT_PULLUP);
}

/*
button control related functions
*/

void incrementColor() {
  colorIndex = (colorIndex + 1) % NUM_COLORS;
}

void decrementColor() {
  if(colorIndex > 0) {
    colorIndex--;
  } else {
    colorIndex = NUM_COLORS - 1;
  }
}

void incrementProgram() {
  program = (program + 1) % NUM_PROGRAMS;
}

void decrementProgram() {
  if (program > 0) {
    program--;
  } else {
    program = NUM_PROGRAMS - 1;
  }
}

void incrementSpeed() {
  if(cycles > 0) {
    cycles--;
  } else {
    cycles = NUM_CYCLES - 1;
  }
}

void decrementSpeed() {
  if(cycles < NUM_CYCLES - 1){
    cycles++;
  } else {
    cycles = 0;
  }
}

void incrementBrightness() {
  if(brightness < NUM_BRIGHTNESS - 1) {
    brightness ++;
  } else {
    brightness = 0;
  }
}

void decrementBrightness() {
  if (brightness > 0) {
    brightness--;
  } else {
    brightness = NUM_BRIGHTNESS - 1;
  }
}

void cycleEditingParameter() {
  editingParameter = (editingParameter + 1) % NUM_PARAMETERS;
}

void incrementParameter(uint16_t parameter) {
  switch (parameter) {
    case PARAMETER_PROGRAM    : incrementProgram();     break;
    case PARAMETER_COLORS     : incrementColor();       break;
    case PARAMETER_CYCLES     : incrementSpeed();       break;
    case PARAMETER_BRIGHTNESS : incrementBrightness();  break;
  }
}

void decrementParameter(uint16_t parameter) {
  switch (parameter) {
    case PARAMETER_PROGRAM    : decrementProgram();    break;
    case PARAMETER_COLORS     : decrementColor();      break;
    case PARAMETER_CYCLES     : decrementSpeed();      break;
    case PARAMETER_BRIGHTNESS : decrementBrightness(); break;
  }
}

void checkButtons() {
  // adapted from http://arduino.cc/en/Tutorial/Debounce
  // read the state of the switch into a local variable:
  bool reading[NUM_BUTTONS];
  reading[0] = digitalRead(PIN_PROGRAM);
  reading[1] = digitalRead(PIN_COLOR);
  reading[2] = digitalRead(PIN_CYCLES);
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    // If the switch changed, due to noise or pressing:
    if (reading[i] != lastButtonState[i]) {
      // reset the debouncing timer if there was a change
      lastDebounceTime[i] = millis();
    } // no else, if the reading is the same as last time nothing needs to be reset
  }
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    // if there was no change for the last 50 ms
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      // see if the current state of the button is different from the last one that was processed
      if (reading[i] != buttonState[i]) {
        // store the new state for the next comparison
        buttonState[i] = reading[i];
        // if the new state of the button is "pressed" = LOW
        if (buttonState[i] == LOW) {
          showStateTimeout = millis() + STATE_DISPLAY_TIMEOUT;
          switch (i) {
            case 0: cycleEditingParameter();              break;
            case 1: decrementParameter(editingParameter); break;
            case 2: incrementParameter(editingParameter); break;
          }
        }
      }
    }
  }

  // save the reading for the next check of the debounce timer
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    lastButtonState[i] = reading[i];
  }
}

// getters for global parameters

uint8_t getParamCycles() {
  // offset cycles by 1 because 0 is supposed to be the fastest speed not the stop
  return cycles + 1;
}

uint8_t getParamBrightness() {
  return brightness;
}

uint8_t getParamProgram() {
  return program;
}

uint8_t getParamColorIndex() {
  return colorIndex;
}

bool isStateVisible() {
  return millis() < showStateTimeout;
}

uint16_t getCurrentEditingParam() {
  return editingParameter;
}

uint8_t getCurrentEditingValue() {
  switch (editingParameter) {
    case PARAMETER_PROGRAM    : return program;
    case PARAMETER_COLORS     : return colorIndex;
    case PARAMETER_CYCLES     : return cycles;
    case PARAMETER_BRIGHTNESS : return brightness;
  }
}
