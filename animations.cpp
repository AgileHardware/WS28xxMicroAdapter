#include "animations.h"


uint32_t getRandomColor() {
  return random(BLACK, WHITE);
}

uint32_t getRandomFromPalette() {
  return getPaletteColorAtIndex(random(0, NUM_COLORS));
}

boolean chanceOneIn(long probability) {
  return (random(0, probability) == 0);
}

// the signature for every animation is uint16_t animationName(uint16_t tick, uint32_t color)
// "tick" is the timing clock for animations. Each tick is a step in the animation. It increments from 0 up to the number that you return, then starts back from 0 again.
// If your animation is based on a main color, use the one defined in "color". Its user selectable at runtime.


uint16_t yourAnimation(uint16_t tick, uint32_t color) {
  // Edit away or copy it to make your own.
  // The resulting animation looks the same as "snake1ToAllForward"

  for (uint16_t i = 0; i<NUM_LEDS; i++) {
  // go through the entire strip of LEDs and set each one
    if(i == tick) {
      // set the led with the index of the current "tick"/step to color
      setLedColor(i, color);
    } else {
      // Set all other LEDs to black / OFF
      // Without this, the LEDs from the previous tick would remain on and the entire strip would will up.
      setLedColor(i, BLACK);
    }
  }

  // The number of "frames" of the animation.
  // Since the dot is supposed to go through every single LED of the strip, the animation length is the number of LEDs that the strip has. This number is defined in the constant NUM_LEDS.
  // "tick" increments from 0 to this value.
  return NUM_LEDS;
}

uint16_t staticColor(uint16_t tick, uint32_t color) {
  for (uint16_t i = 0; i<NUM_LEDS; i++) {
    setLedColor(i, color);
  }

  return 1;
}

uint16_t blinkColor(uint16_t tick, uint32_t color) {
  uint32_t _color;

  if (tick == 0) {
    _color = color;
  } else {
    _color = BLACK;
  }

  for (uint16_t i = 0; i<NUM_LEDS; i++) {
    setLedColor(i, _color);
  }

  return 2;
}

uint16_t snake1(uint16_t tick, uint32_t color, uint16_t length, uint16_t increment) {
  uint16_t offset = (tick % length) * increment;

  for (uint16_t i = 0; i<NUM_LEDS; i++) {
    if (0==((offset+i)%length)) {
      setLedColor(i, color);
    } else {
      setLedColor(i, BLACK);
    }
  }

  return length;
}

uint16_t snake1o4forward(uint16_t tick, uint32_t color) {
  return snake1(tick, color, 4, 1);
}

uint16_t snake1o4reverse(uint16_t tick, uint32_t color) {
  return snake1(tick, color, 4, 3);
}

uint16_t snake1o8forward(uint16_t tick, uint32_t color) {
  return snake1(tick, color, 8, 1);
}

uint16_t snake1o8reverse(uint16_t tick, uint32_t color) {
  return snake1(tick, color, 8, 7);
}

uint16_t snake1oAllForward(uint16_t tick, uint32_t color) {
  return snake1(tick, color, NUM_LEDS, 1);
}

uint16_t snake1oAllReverse(uint16_t tick, uint32_t color) {
  return snake1(tick, color, NUM_LEDS, NUM_LEDS-1);
}

uint16_t wave4(uint16_t tick, uint32_t color, boolean forward) {
  uint16_t offset;

  if (forward) {
    offset = tick;
  } else {
    offset = 3-tick;
  }
  for (uint16_t i = 0; i<NUM_LEDS; i++) {
    switch ((i+offset) % 4) {
      case 0: setLedColor(i, dim8(color, 8));   break;
      case 1: // fall through
      case 3: setLedColor(i, dim8(color, 4));   break;
      case 2: setLedColor(i, color);           break;
    }
  }

  return 4;
}

uint16_t wave4forward(uint16_t tick, uint32_t color) {
  return wave4(tick, color, true);
}

uint16_t wave4reverse(uint16_t tick, uint32_t color) {
  return wave4(tick, color, false);
}

uint16_t wave8(uint16_t tick, uint32_t color, boolean forward) {
  uint16_t offset;

  if (forward) {
    offset = tick;
  } else {
    offset = 7-tick;
  }
  for (uint16_t i = 0; i<NUM_LEDS; i++) {
    switch ((i+offset) % 8) {
      case 0: setLedColor(i, dim8(color, 8));   break;
      case 1: // fall through
      case 7: setLedColor(i, dim8(color, 6));   break;
      case 2: // fall through
      case 6: setLedColor(i, dim8(color, 4));   break;
      case 3: // fall through
      case 5: setLedColor(i, dim8(color, 2));   break;
      case 4: setLedColor(i, color);           break;
    }
  }

  return 8;
}

uint16_t wave8forward(uint16_t tick, uint32_t color) {
  return wave8(tick, color, true);
}

uint16_t wave8reverse(uint16_t tick, uint32_t color) {
  return wave8(tick, color, false);
}

uint16_t saw(uint16_t tick, uint32_t color, uint16_t length, boolean forward) {
  uint16_t level;

  for (uint16_t i=0; i<NUM_LEDS; i++) {
    if (forward) {
      level = ((tick+i)%length) * (8/length);
    } else {
      level = ((tick+(length-i))%length) * (8/length);
    }
    setLedColor(i, dim8(color, level));
  }

  return length;
}

uint16_t saw4forward(uint16_t tick, uint32_t color) {
  return saw(tick, color, 4, true);
}

uint16_t saw4reverse(uint16_t tick, uint32_t color) {
  return saw(tick, color, 4, false);
}

uint16_t saw8forward(uint16_t tick, uint32_t color) {
  return saw(tick, color, 8, true);
}

uint16_t saw8reverse(uint16_t tick, uint32_t color) {
  return saw(tick, color, 8, false);
}

uint32_t rainbowColor(uint16_t input, uint16_t outOf) {
  uint32_t red, green, blue;
  uint32_t zero, one, two, three, four, five, six;
  uint32_t index;

  index = input % outOf;

  zero  = map(0, 0, 6, 0, outOf);
  one   = map(1, 0, 6, 0, outOf);
  two   = map(2, 0, 6, 0, outOf);
  three = map(3, 0, 6, 0, outOf);
  four  = map(4, 0, 6, 0, outOf);
  five  = map(5, 0, 6, 0, outOf);
  six   = map(6, 0, 6, 0, outOf);

  if (index < one) {
    red   = 255;
    green = map(index, zero, one, 0, 255);
    blue  = 0;
  } else if (index < two) {
    red   = map(index, one, two, 255, 0);
    green = 255;
    blue  = 0;
  } else if (index < three) {
    red   = 0;
    green = 255;
    blue  = map(index, two, three, 0, 255);
  } else if (index < four) {
    red   = 0;
    green = map(index, three, four, 255, 0);
    blue  = 255;
  } else if (index < five) {
    red   = map(index, four, five, 0, 255);
    green = 0;
    blue  = 255;
  } else {
    red   = 255;
    green = 0;
    blue  = map(index, five, six, 255, 0);
  }

  return (red<<16)+(green<<8)+(blue);
}

uint16_t rainbow(uint16_t tick, uint32_t color) {

  for (uint16_t i=0; i<NUM_LEDS; i++) {
    setLedColor(i, rainbowColor(i+tick, NUM_LEDS));
  }

  return NUM_LEDS;
}

uint16_t knightRider(uint16_t tick, uint32_t color) {
  for (uint16_t i=0; i<NUM_LEDS; i++) {
    setLedColor(i, BLACK);
  }

  if (tick < NUM_LEDS) {
    setLedColor(tick, color);
  } else {
    setLedColor(NUM_LEDS-(2+tick-NUM_LEDS), color);
  }

  return 2*NUM_LEDS-2;
}

uint16_t twinkleTwinkle(uint16_t tick, uint32_t color, uint8_t cycles) {
  for (uint16_t i=0; i<NUM_LEDS; i++) {
    if(getLedColor(i) > BLACK) {
      setLedColor(i, dim256(getLedColor(i), map(cycles, NUM_CYCLES, 0, 10, 100)));
    } else if (chanceOneIn(map(cycles, NUM_CYCLES, 0, 500, 10))) {
      setLedColor(i, getRandomColor());
    }
  }

  return 1;
}

uint16_t competitivePixels(uint16_t tick, uint32_t color) {
  uint8_t speed;

  for (uint16_t i=0; i<NUM_LEDS; i++) {
    if(getLedColor(i) > BLACK) {
      speed = getLedColor(i) % 5;
      setLedColor(i + speed, getLedColor(i));
      setLedColor(i, BLACK);
      i = i + speed;
    } else if(i == 0 && chanceOneIn(100)) {
      setLedColor(i, getRandomColor());
    }
  }

  return 1;
}

void drawExplosion(uint16_t position) {
  setLedColor(position, MAGENTA);
}

void movePixel(int position, int moveBy) {
  int targetPosition = position + moveBy;

  if(targetPosition >= 0 && targetPosition < NUM_LEDS) {
    setLedColor(targetPosition, getLedColor(position));
  }

  setLedColor(position, BLACK);
}


void moveAllPixelsForward(uint32_t color) {
  for (int i = NUM_LEDS-1; i >= 0; i--) {
    if (getLedColor(i) == color) {
      movePixel(i, 1);
    }
  }
}

void moveAllPixelsBackward(uint32_t color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (getLedColor(i) == color) {
      movePixel(i, -1);
    }
  }
}

bool isDimmedMagenta(uint32_t color) {
  if (color > BLACK &&
      color != RED &&
      color != BLUE) {
      return true;
  } else {
    return false;
  }
}

bool checkForCollision(uint16_t position) {
  if(getLedColor(position) == RED && getLedColor(position+1) != BLACK) {
    return true;
  } else if(getLedColor(position) == BLUE && getLedColor(position-1) != BLACK) {
    return true;
  } else {
    return false;
  }
}


void drawAllCollisions() {
  // No explosions in the outer 5% of the strip, they tend to last too long
  for (uint16_t i = NUM_LEDS/20; i<NUM_LEDS-NUM_LEDS/20; i++) {
    if (checkForCollision(i)) {
      drawExplosion(i);
    }
  }
}

void flickerDim(uint16_t position) {
  if(chanceOneIn(50)){
    setLedColor(position, brighten8(getLedColor(position), 1));
  } else {
    setLedColor(position, dim256(getLedColor(position), 4));
  }
}

uint16_t tinyExplosions(uint16_t tick, uint32_t color) {

  for (uint16_t i=0; i<NUM_LEDS; i++) {
    if (isDimmedMagenta(getLedColor(i))) {
      flickerDim(i);
    }
  }

  drawAllCollisions();
  moveAllPixelsForward(RED);
  drawAllCollisions();
  moveAllPixelsBackward(BLUE);

  // put in new pixels at the end of the strip
  if(chanceOneIn(300)) {
    setLedColor(0, RED);
  }

  if(chanceOneIn(300)) {
    setLedColor(NUM_LEDS-1, BLUE);
  }

  return 1;
}

uint16_t dimRider(uint16_t tick, uint32_t color) {
  uint8_t dimBy;
  for (uint16_t i=0; i<NUM_LEDS; i++) {
    setLedColor(i, BLACK);
  }
  if(tick < NUM_LEDS / 2) {
    dimBy = map(tick, 0, NUM_LEDS/2, 255, 0);
  } else {
    dimBy = map(NUM_LEDS - tick, 0, NUM_LEDS/2, 255, 0);
  }
  setLedColor(tick, dim256(color, dimBy));
  return NUM_LEDS;
}

uint16_t breathe(uint16_t tick, uint32_t color) {
  uint8_t dimBy;
  if(tick < 32) {
    dimBy = tick;
  } else {
    dimBy = 64 - tick;
  }
  if(dimBy >= 256) {
    dimBy = 255;
  }
  for (uint16_t i=0; i<NUM_LEDS; i++) {
      setLedColor(i, dim8(color, dimBy * 8));
  }

  return 64;
}

#define SPARKING  150
#define COOLING   55

uint16_t fire2012(uint16_t tick, uint32_t color) {
  // Fire2012 by Mark Kriegsman, July 2012
  // as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
  // adapted from example included with fastLED
  if(tick == 0) {
    random16_add_entropy( random());

    static byte heat[NUM_LEDS];

    // Array of temperature readings at each simulation cell
    // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for(uint16_t j = 0; j < NUM_LEDS; j++) {
      CRGB hColor = HeatColor(heat[j]);
      uint32_t red    = hColor.red;
      uint32_t green  = hColor.green;
      uint32_t blue   = hColor.blue;

      uint32_t intColor = (red<<16)+(green<<8)+blue;
      setLedColor(j, HeatColor(heat[j]));
    }
  }
  return 4;
}

