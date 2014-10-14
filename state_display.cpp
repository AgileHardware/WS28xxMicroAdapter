#include "state_display.h"

void drawDecimalValue(int value) {
  setLedColor(value + STATE_VALUE_OFFSET, RED);
}

void drawBinaryValue(int value) {
  for (uint8_t i=0; i<8; i++) {
		if((value+1 >> i) & 0x01) {
		  setLedColor(i + STATE_VALUE_OFFSET, RED);
		} // no else, only light up pixels that are part of the binary number
  }
}

void drawValue(int value, int maxValue) {
  // amount of numbers that can be displayed in binary 2^STATE_VALUE_WIDTH. 1 is subtracted because the 0 value is not used for display
  if(maxValue <= STATE_VALUE_WIDTH) {
		drawDecimalValue(value);
  } else if(maxValue <= STATE_MAX_BINARY_VALUE) {
		drawBinaryValue(value);
  }
}

uint16_t drawProgramState(uint16_t stateTick, uint8_t program) {
  for (uint8_t i=0; i<STATE_MODE_WIDTH; i++) {
		setLedColor(i+STATE_BORDER_WIDTH, dim8(ORANGE, stateTick/2));
  }

  drawValue(program, NUM_PROGRAMS);
  return 16;
}

uint16_t drawColorState(uint16_t stateTick, uint8_t colorIndex) {
  for (uint8_t i=0; i<STATE_MODE_WIDTH; i++) {
		setLedColor(i+STATE_BORDER_WIDTH, getPaletteColorAtIndex(i % NUM_COLORS));
  }

  drawValue(colorIndex, NUM_COLORS);
  return 1;
}

uint16_t drawCyclesState(uint16_t stateTick, uint8_t cycles) {
  setLedColor(stateTick / STATE_MODE_WIDTH + STATE_BORDER_WIDTH, BLUE);
	// reverse the display for cycles value because low cycles = high speed, and speed is what the user feels he controls
  drawValue(NUM_CYCLES - cycles - 1, NUM_CYCLES);
  return pow(STATE_MODE_WIDTH, 2);
}

uint16_t drawBrightnessState(uint16_t stateTick, uint8_t brightness) {
  for (uint8_t i=0; i<STATE_MODE_WIDTH; i++) {
		setLedColor(i + STATE_BORDER_WIDTH, dim8(WHITE, STATE_MODE_WIDTH - i));
  }
  drawValue(brightness, NUM_BRIGHTNESS);
  return 1;
}

uint16_t drawState(uint16_t stateTick, uint8_t editingParameter, uint8_t value) {
  uint8_t borderLocations[3];
  // clear the display area
  for (uint8_t i=0; i<STATE_MODE_WIDTH + STATE_VALUE_WIDTH + STATE_BORDER_WIDTH*3; i++) {
		setLedColor(i, BLACK);
  }

  // draw borders for the display parts
  borderLocations[0] = 0;
  borderLocations[1] = STATE_BORDER_WIDTH + STATE_MODE_WIDTH;
  borderLocations[2] = STATE_BORDER_WIDTH*2 + STATE_MODE_WIDTH + STATE_VALUE_WIDTH;

  for (uint8_t i=0; i<STATE_BORDER_WIDTH; i++) {
		setLedColor(borderLocations[0]+i, STATE_BORDER_COLOR);
		setLedColor(borderLocations[1]+i, STATE_BORDER_COLOR);
		setLedColor(borderLocations[2]+i, STATE_BORDER_COLOR);
  }

  switch (editingParameter) {
		case PARAMETER_PROGRAM    : return drawProgramState			(stateTick, value);
		case PARAMETER_COLORS     : return drawColorState				(stateTick, value);
		case PARAMETER_CYCLES     : return drawCyclesState				(stateTick, value);
		case PARAMETER_BRIGHTNESS : return drawBrightnessState		(stateTick, value);
	}
}