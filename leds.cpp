#include "leds.h"

// the last frame of animation that was displayed
uint32_t colors[NUM_COLORS] = { GREEN, CYAN, BLUE, MAGENTA, RED, ORANGE, YELLOW, WHITE};

CRGB leds[NUM_LEDS];

void setupLeds() {
  pinMode(PIN_DATA, OUTPUT);
  pinMode(PIN_CLK,  OUTPUT);

  #if defined(USE_TM1803)
    FastLED.addLeds<TM1803, PIN_DATA, RGB>(leds, NUM_LEDS);
  #elif defined(USE_TM1804)
    FastLED.addLeds<TM1804, PIN_DATA, RGB>(leds, NUM_LEDS);
  #elif defined(USE_TM1809)
    FastLED.addLeds<TM1809, PIN_DATA, RGB>(leds, NUM_LEDS);
  #elif defined(USE_WS2811)
    FastLED.addLeds<WS2811, PIN_DATA, RGB>(leds, NUM_LEDS);
  #elif defined(USE_WS2812)
    FastLED.addLeds<WS2812, PIN_DATA, RGB>(leds, NUM_LEDS);
  #elif defined(USE_WS2812B)
    FastLED.addLeds<WS2812B, PIN_DATA, RGB>(leds, NUM_LEDS);
  #elif defined(USE_NEOPIXEL)
    FastLED.addLeds<NEOPIXEL, PIN_DATA>(leds, NUM_LEDS);
  #elif defined(USE_UCS1903)
    FastLED.addLeds<UCS1903, PIN_DATA, RGB>(leds, NUM_LEDS);
  #elif defined(USE_UCS1903B)
    FastLED.addLeds<UCS1903B, PIN_DATA, RGB>(leds, NUM_LEDS);
  #elif defined(USE_GW6205)
    FastLED.addLeds<GW6205, PIN_DATA, RGB>(leds, NUM_LEDS);
  #elif defined(USE_GW6205_400)
    FastLED.addLeds<GW6205_400, PIN_DATA, RGB>(leds, NUM_LEDS);
  #elif defined(USE_WS2801)
    FastLED.addLeds<WS2801, PIN_DATA, PIN_CLK, RGB>(leds, NUM_LEDS);
  #elif defined(USE_SM16716)
    FastLED.addLeds<SM16716, PIN_DATA, PIN_CLK, RGB>(leds, NUM_LEDS);
  #elif defined(USE_LPD8806)
    FastLED.addLeds<LPD8806, PIN_DATA, PIN_CLK, RGB>(leds, NUM_LEDS);
  #elif defined(USE_APA102)
    FastLED.addLeds<APA102, PIN_DATA, PIN_CLK, GBR>(leds, NUM_LEDS);
  #endif


  FastLED.setCorrection(COLOR_CORRECTION);
  FastLED.setTemperature(COLOR_TEMPERATURE);
}

void setLedColor(uint16_t index, CRGB color) {
  leds[index] = color;
}

void setLedColor(uint16_t index, uint32_t color) {
  leds[index] = color;
}

void prepareLeds(uint8_t brightnessParam) {
  uint8_t brightness255;
  uint8_t brightnessNoZero = brightnessParam + 1;

  brightness255 = map(brightnessNoZero, 1, NUM_BRIGHTNESS, 15, 255);
  FastLED.setBrightness(brightness255);
}

void showLeds() {
  FastLED.show();
}

uint32_t getLedColor(uint16_t index) {
  uint32_t red    = leds[index].red;
  uint32_t green  = leds[index].green;
  uint32_t blue   = leds[index].blue;

  return (red<<16)+(green<<8)+blue;
}

uint32_t dim8(uint32_t color, uint8_t levels) {
  uint32_t red, green, blue;

  red   = (color >> 16) & 0xff;
  green = (color >>  8) & 0xff;
  blue  = (color >>  0) & 0xff;

  red   = red   >> levels;
  green = green >> levels;
  blue  = blue  >> levels;

  return (red<<16)+(green<<8)+blue;
}

uint32_t dim256(uint32_t color, uint8_t levels) {
  uint32_t red, green, blue;

  red   = (color >> 16) & 0xff;
  green = (color >>  8) & 0xff;
  blue  = (color >>  0) & 0xff;

  red   = map(red,   0, 255, 0, 255-levels);
  green = map(green, 0, 255, 0, 255-levels);
  blue  = map(blue,  0, 255, 0, 255-levels);

  return (red<<16)+(green<<8)+blue;
}

uint32_t brighten8(uint32_t color, uint8_t levels) {
  uint32_t red, green, blue;

  red   = (color >> 16) & 0xff;
  green = (color >>  8) & 0xff;
  blue  = (color >>  0) & 0xff;

  red   = red   << levels;
  green = green << levels;
  blue  = blue  << levels;

  return (red<<16)+(green<<8)+blue;
}

uint32_t getPaletteColorAtIndex(uint8_t index) {
  return colors[index];
}

