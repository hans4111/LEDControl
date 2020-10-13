/*
 * led.cpp
 *
 *  Created on: Oct 12, 2020
 *      Author: nicholashansen
 */



#include <led.hpp>
#include <main.h>
#include <memory.h>

static void newLEDInit(uint8_t newLedIndex);

static uint8_t ledIndex = 0;
static bool initialized = false;

/**
 * Global LEDControlArray used to maintain list of used to walk through configured LEDs in timer to manage
 * brightness and state change
 */
///TODO: Assess need for volatility or if protection with a mutex lock is necessary
volatile RGBLed LEDControlArray[5] = {};
/**
 * Global timerLEDCount used to track index maximum for the timer while walking through LEDs
 * to be controlled
 */
///TODO: Assess need for volatility or if protection with a mutex lock is necessary
volatile uint8_t timerLEDCount = 0;

/**
 * Initializes the GPIO for the LED Structure
 *
 * Individually steps through each pin and port of the structure to enable them individually
 * @return Boolean for successful LED initialization
 */
///TODO: Add led initialization failure OR switch from bool to void type
bool initializeLEDs(void)
{
	for (int i =0; i<ledIndex; i++)
	{
		newLEDInit(i);
	}
	return true;
}

/**
 * Add a new LED to LEDControl
 *
 * Take in a new RGBLed Structure and if there is space amend it to the list of LEDs to be processed
 *
 * @param new RGBLed struct pre-defined with pins, ports, state, and brightness
 * @return boolean true if there is space for the LED false if there is not
 */
bool createLED(RGBLed newLED)
{
	if (ledIndex < 5)
	{
		//LEDControlArray[ledIndex++] = newLED;
		memcpy((void*)&LEDControlArray[ledIndex], &newLED, sizeof(RGBLed));
		ledIndex++;
		if (initialized == true)
		{
			newLEDInit(ledIndex-1);
		}
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * Change the brightness setting of a LED
 *
 * Change brightness setting on led from 0-100% with base zero led selection
 *
 * @param uint8_t led selection 0-4, 5 LEDs total
 * @param uint8_t led brightness from 0-100 percent
 * @return boolean true for success false for bad brightness or LED choice
 */
bool changeBrightness(uint8_t led, uint8_t brightness)
{
	if (led > 4 || brightness > 100)
	{
		return false;
	}

	LEDControlArray[led].brightness = brightness;
	return true;
}

/**
 * Change state of an LED
 *
 * Change state of LED from RGBLedState enumeration with base zero led selection
 *
 * @param uint8_t led selection 0-4, 5 LEDs total
 * @param RGBLedState enumeration selected state off, red, green, blue
 * @return boolean true for success false for bad led or state selection
 */
bool changeState(uint8_t led, RGBLedState state)
{
	//TODO: there has to be a better way to check valid enumeration, I know you can in C# investigate c++/c
	if (led >4 || (uint8_t)state > 0x03)
	{
		return false;
	}

	LEDControlArray[led].state = state;
	return true;
}

/**
 * Local LED GPIO Init Function
 *
 * Initialize the GPIO of new LED in control structure.
 *
 * @param uint8_t newLedIndex The index in the control array of the new LED to be initalized
 */
static void newLEDInit(uint8_t newLedIndex)
{
	RGBLed *temp = (RGBLed *)&LEDControlArray[newLedIndex];
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;

	GPIO_InitStruct.Pin = temp->BluePin;
	LL_GPIO_Init(&(temp->BluePort), &GPIO_InitStruct);

	GPIO_InitStruct.Pin = temp->GreenPin;
	LL_GPIO_Init(&temp->GreenPort, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = temp->RedPin;
	LL_GPIO_Init(&temp->RedPort, &GPIO_InitStruct);

	//TODO: Decide if we want a base state or brightness defined here
	//TODO: Can we fail to initialize GPIO? We need to manage any failures if so
}
