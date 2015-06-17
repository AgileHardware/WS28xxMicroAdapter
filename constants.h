#ifndef __constants_h__
#define __constants_h__

// uncomment only the LED chipset you are using
// we have only tested with NEOPIXEL and WS2801 so far
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

// Maximum / Total available Numbers for a bunch of stuff
#define NUM_LEDS        46
#define NUM_COLORS      8
// The first program is 0. If you just added programm 21, make NUM_PROGRAMS 22.
#define NUM_PROGRAMS    21
#define NUM_BUTTONS     3
#define NUM_CYCLES      8
#define NUM_BRIGHTNESS  8
#define NUM_PARAMETERS  4

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

// Pin assignment on the Arduino
#define PIN_DATA        0
#define PIN_CLK         1
#define PIN_PROGRAM     2
#define PIN_COLOR       3
#define PIN_CYCLES      4

// EEPROM Settings
#define USE_EEPROM
#define EEPROM_START    (0)
#define EEPROM_PROGRAM  (EEPROM_START)
#define EEPROM_COLOR    (EEPROM_PROGRAM + size(program))
#define EEPROM_CYCLES   (EEPROM_COLOR   + size(color))
#define EEPROM_1ST_FREE (EEPROM_CYCLES  + size(cycles))

// List of parameters that can be editied with the buttons
#define PARAMETER_PROGRAM     0
#define PARAMETER_COLORS      1
#define PARAMETER_CYCLES      2
#define PARAMETER_BRIGHTNESS  3

// Some named Colors
#define BLACK    0x000000
#define BLUE     0x0000ff
#define GREEN    0x00ff00
#define CYAN     0x00ffff
#define RED      0xff0000
#define MAGENTA  0xff00ff
#define ORANGE   0xff8800
#define YELLOW   0xffff00
#define WHITE    0xffffff
#define GREY     0x222222

// Some helpful defenitions to make function calls more clear

#define DIRECTION_FORWARD   1
#define DIRECTION_BACKWARD  -1

#endif