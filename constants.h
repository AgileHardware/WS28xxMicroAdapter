#ifndef __constants_h__
#define __constants_h__

// Maximum / Total available Numbers for a bunch of stuff
#define NUM_COLORS      8
#define NUM_BUTTONS     3
#define NUM_CYCLES      8
#define NUM_BRIGHTNESS  8
#define NUM_PARAMETERS  4

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