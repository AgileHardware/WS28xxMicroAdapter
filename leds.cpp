#include "leds.h"

// the last frame of animation that was displayed
uint32_t lastColors[NUM_LEDS];
uint32_t colors[NUM_COLORS] = { GREEN, CYAN, BLUE, MAGENTA, RED, ORANGE, YELLOW, WHITE};

#ifdef USE_WS2812
Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUM_LEDS, PIN_DATA, NEO_GRB + NEO_KHZ800);
#endif

void setupLeds() {
  pinMode(PIN_DATA, OUTPUT);
  pinMode(PIN_CLK,  OUTPUT);

  #ifdef USE_WS2812
  leds.begin();
  #endif
}

void setLedColor(uint16_t index, uint32_t color) {
  #ifdef USE_WS2812
  leds.setPixelColor(index, color);
  #endif
  lastColors[index] = color;
}

void prepareLeds(uint8_t brightnessParam) {
  uint8_t brightness255;
  uint8_t brightnessNoZero = brightnessParam + 1;
	brightness255 = map(brightnessNoZero, 1, NUM_BRIGHTNESS, 15, 255);
	leds.setBrightness(brightness255);
}

void showLeds() {
	leds.show();
}

uint32_t getLedColor(uint16_t index) {
  return lastColors[index];
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

