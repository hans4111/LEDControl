/*
 * led.h
 *
 *  Created on: Oct 12, 2020
 *      Author: nicholashansen
 */

#pragma once

enum RGBLedState
{
	Off,
	Red,
	Green,
	Blue
};

struct RGBLed
{
	uint32_t RedPin;
	uint32_t GreenPin;
	uint32_t BluePin;
	uint32_t RedPort;
	uint32_t GreenPort;
	uint32_t BluePort;
	LedState state;
	uint8_t brightness;
};

volatile extern RGBLed LEDControlArray[5];
volatile extern uint8_t timerLEDCount;

bool initializeLEDs(void);

bool createLED(RGBLed newLED);

void changeBrightness(uint8_t led, uint8_t brightness);

void changeState(uint8_t led, RGBLedState state);
