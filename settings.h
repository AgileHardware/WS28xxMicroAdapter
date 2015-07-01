#ifndef __settings_h__
#define __settings_h__

// uncomment only the LED chipset you are using
// we have only tested with NEOPIXEL, WS2801 and APA102 (aka adafruit DotStar) so far
// #define USE_TM1803
// #define USE_TM1804
// #define USE_TM1809
// #define USE_WS2811
// #define USE_WS2812
// #define USE_WS2812B
#define USE_NEOPIXEL
// #define USE_UCS1903
// #define USE_UCS1903B
// #define USE_GW6205
// #define USE_GW6205_400
// #define USE_WS2801
// #define USE_SM16716
// #define USE_LPD8806
// #define USE_APA102

// Number of LEDs in your Strip
#define NUM_LEDS        144

// The first program is 0. If you just added programm 21, make NUM_PROGRAMS 22.
#define NUM_PROGRAMS    21

// Factor by which animations are slowed down
// You can adjust this if you think animations run to slow or to fast. 1 means no slowdown, higher numbers = more slow
#define SLOWDOWN_CYCLES 144 / NUM_LEDS

// White Point
// Adjust this value so that 0xFFFFFF displays as a neutral blue-ish white on your LED Strip.
// The lower you go, the more brightness you loose, so try to find the closest value to 0xFFFFFF that looks right. At least one color should be FF.
// For an Adafruit DotStar strip, for example, we found 0x80FFFF to be a good value, but this can really differ on each individual strip.
#define COLOR_CORRECTION 0xFFFFFF

// If you dont actually want a blueish white, you can choose a different color temperature.
// FastLED provides these pre-conigured incandescent color profiles:
//     Candle, Tungsten40W, Tungsten100W, Halogen, CarbonArc,
//     HighNoonSun, DirectSunlight, OvercastSky, ClearBlueSky,
// FastLED provides these pre-configured gaseous-light color profiles:
//     WarmFluorescent, StandardFluorescent, CoolWhiteFluorescent,
//     FullSpectrumFluorescent, GrowLightFluorescent, BlackLightFluorescent,
//     MercuryVapor, SodiumVapor, MetalHalide, HighPressureSodium,
// FastLED also provides an "Uncorrected temperature" profile
//    UncorrectedTemperature
#define COLOR_TEMPERATURE UncorrectedTemperature


// display style for state display
// STATE_VALUE_WIDTH should be a minimum of 5, if you want to display all values including the selected program. Values up to 32 (2^STATE_VALUE_WIDTH) can be shown in binary. For higher values the area will be blank.
// STATE_MODE_WIDTH can be set to 1 and you can still distinguish the mode by the color of the single LED (orange = program, green = color, blue = cycles, white = brightness)
// Set all to 0 to disable state display completely
#define STATE_BORDER_WIDTH          1
#define STATE_BORDER_COLOR          GREY
#define STATE_MODE_WIDTH            8
#define STATE_VALUE_WIDTH           8
#define STATE_DISPLAY_TIMEOUT       4000
#define STATE_VALUE_OFFSET          STATE_BORDER_WIDTH * 2 + STATE_MODE_WIDTH
#define STATE_MAX_BINARY_VALUE      STATE_VALUE_WIDTH^2 - 1


#endif