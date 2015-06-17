#include "FastLED.h"

#ifdef USE_EEPROM
#include <EEPROM.h>
#endif

#include "constants.h"
#include "leds.h"
#include "control.h"
#include "state_display.h"
#include "animations.h"


uint16_t tick;
uint16_t stateTick;
uint16_t loopNum = 0;

void updateLeds() {
  uint16_t ticks;
  uint16_t stateTicks;
  uint32_t color      = getPaletteColorAtIndex(getParamColorIndex());
  uint8_t  program    = getParamProgram();
  uint8_t  brightness = getParamBrightness();
  uint8_t  cycles     = getParamCycles();

  prepareLeds(brightness);

  switch (program) {
    case  0: ticks = blinkColor         (tick, color); break;
    case  1: ticks = blinkColor         (tick, color); break;
    case  2: ticks = snake1o4forward    (tick, color); break;
    case  3: ticks = snake1o4reverse    (tick, color); break;
    case  4: ticks = snake1o8forward    (tick, color); break;
    case  5: ticks = snake1o8reverse    (tick, color); break;
    case  6: ticks = snake1oAllForward  (tick, color); break;
    case  7: ticks = snake1oAllReverse  (tick, color); break;
    case  8: ticks = wave4forward       (tick, color); break;
    case  9: ticks = wave4reverse       (tick, color); break;
    case 10: ticks = wave8forward       (tick, color); break;
    case 11: ticks = wave8reverse       (tick, color); break;
    case 12: ticks = saw4forward        (tick, color); break;
    case 13: ticks = saw4reverse        (tick, color); break;
    case 14: ticks = saw8forward        (tick, color); break;
    case 15: ticks = saw8reverse        (tick, color); break;
    case 16: ticks = rainbow            (tick, color); break;
    case 17: ticks = dimRider           (tick, color); break;
    case 18: ticks = tinyExplosions     (tick, color); break;
    case 19: ticks = twinkleTwinkle     (tick, color, cycles); break;
    case 20: ticks = breathe            (tick, color); break;
    // add your own animations here. Don't forget to also increment the NUM_PROGRAMS value in "constants.h"
    // define new animations in "animations.cpp" / "animations.h"
    // case 21: ticks = yourAnimation   (tick, color); break;
  }

  if(isStateVisible()) {
    stateTicks = drawState(stateTick, getCurrentEditingParam(), getCurrentEditingValue());
    stateTick  = (stateTick+1) % stateTicks;
  }

  showLeds();

  loopNum = (loopNum + 1) % (cycles * SLOWDOWN_CYCLES);
  if (loopNum == 0) {
    tick = (tick + 1) % ticks;
  }
}

void setup() {
  Serial.begin(9600);
  setupButtons();
  setupLeds();
}

void loop() {
  checkButtons();
  updateLeds();
}

