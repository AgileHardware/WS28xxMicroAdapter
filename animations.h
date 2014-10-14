#ifndef __animations_h__
#define __animations_h__


#include <Arduino.h>
#include "constants.h"
#include "leds.h"

// All animations described in "animations.cpp" need to be added here

// uint16_t yourAnimation		(uint16_t tick, uint32_t color);
uint16_t staticColor				(uint16_t tick, uint32_t color);
uint16_t blinkColor					(uint16_t tick, uint32_t color);
uint16_t snake1o4forward		(uint16_t tick, uint32_t color);
uint16_t snake1o4reverse		(uint16_t tick, uint32_t color);
uint16_t snake1o8forward		(uint16_t tick, uint32_t color);
uint16_t snake1o8reverse		(uint16_t tick, uint32_t color);
uint16_t snake1oAllForward	(uint16_t tick, uint32_t color);
uint16_t snake1oAllReverse	(uint16_t tick, uint32_t color);
uint16_t wave4forward				(uint16_t tick, uint32_t color);
uint16_t wave4reverse				(uint16_t tick, uint32_t color);
uint16_t wave8forward				(uint16_t tick, uint32_t color);
uint16_t wave8reverse				(uint16_t tick, uint32_t color);
uint16_t saw4forward				(uint16_t tick, uint32_t color);
uint16_t saw4reverse				(uint16_t tick, uint32_t color);
uint16_t saw8forward				(uint16_t tick, uint32_t color);
uint16_t saw8reverse				(uint16_t tick, uint32_t color);
uint16_t rainbow						(uint16_t tick, uint32_t color);
uint16_t knightRider				(uint16_t tick, uint32_t color);
uint16_t twinkleTwinkle			(uint16_t tick, uint32_t color, uint8_t cycles);
uint16_t competitivePixels	(uint16_t tick, uint32_t color);
uint16_t tinyExplosions			(uint16_t tick, uint32_t color);
uint16_t barelyAlive				(uint16_t tick, uint32_t color);
uint16_t drunkenPixelParty	(uint16_t tick, uint32_t color);
uint16_t dryPixelParty			(uint16_t tick, uint32_t color);
uint16_t uniformPixelParty	(uint16_t tick, uint32_t color);
uint16_t dimRider						(uint16_t tick, uint32_t color);
uint16_t breathe						(uint16_t tick, uint32_t color);

#endif