/*
 * led.h
 *
 *  Created on: Oct 12, 2020
 *      Author: nicholashansen
 */

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

enum RGBLedState
{
	Off		=	0x00,
	Red		=	0x01,
	Green	=	0x02,
	Blue	=	0x03
};

struct RGBLed
{
	uint32_t RedPin;
	uint32_t GreenPin;
	uint32_t BluePin;
	GPIO_TypeDef RedPort;
	GPIO_TypeDef GreenPort;
	GPIO_TypeDef BluePort;
	RGBLedState state;
	uint8_t brightness;
};

volatile extern RGBLed LEDControlArray[5];
volatile extern uint8_t timerLEDCount;

bool initializeLEDs(void);

bool createLED(RGBLed newLED);

bool changeBrightness(uint8_t led, uint8_t brightness);

bool changeState(uint8_t led, RGBLedState state);

#ifdef __cplusplus
}
#endif
