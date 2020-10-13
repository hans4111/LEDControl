/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_it.h"
#include "led.hpp"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM14 global interrupt.
  */
///TODO: change max to 255 to allow for RGB mixing for full color scale
static const uint8_t max=100;
static uint8_t count = 0;
void TIM14_IRQHandler(void)
{

	if (LL_TIM_IsActiveFlag_UPDATE (TIM14) == 1)
	{
		LL_TIM_ClearFlag_UPDATE (TIM14);
	}
	//Timer goes off at a rate of 1kHz we will increment a count from 0-100 for brightness, when we hit the brightness value change led to 0
	//when the counter rolls over turn led on. Use for loop to go through all the LEDs in the led array each timer

	if (count++ > max)
	{
		count = 0;
	}
	for (int i=0; i < timerLEDCount; i++)
	{
		switch (LEDControlArray[i].state)
		{
			case RGBLedState::Off:
				LL_GPIO_ResetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].BluePort,LEDControlArray[i].BluePin);
				LL_GPIO_ResetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].GreenPort,LEDControlArray[i].GreenPin);
				LL_GPIO_ResetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].RedPort,LEDControlArray[i].RedPin);
				break;
			case RGBLedState::Green:
				if (count > LEDControlArray[i].brightness)
				{
					LL_GPIO_ResetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].GreenPort,LEDControlArray[i].GreenPin);
					LL_GPIO_ResetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].RedPort,LEDControlArray[i].RedPin);
					LL_GPIO_ResetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].BluePort,LEDControlArray[i].BluePin);
					break;
				}
				else
				{
					LL_GPIO_SetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].GreenPort,LEDControlArray[i].GreenPin);
					LL_GPIO_ResetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].RedPort,LEDControlArray[i].RedPin);
					LL_GPIO_ResetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].BluePort,LEDControlArray[i].BluePin);
					break;
				}
			case RGBLedState::Red:
				if (count > LEDControlArray[i].brightness)
				{
					LL_GPIO_ResetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].GreenPort,LEDControlArray[i].GreenPin);
					LL_GPIO_ResetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].RedPort,LEDControlArray[i].RedPin);
					LL_GPIO_ResetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].BluePort,LEDControlArray[i].BluePin);
					break;
				}
				else
				{
					LL_GPIO_ResetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].GreenPort,LEDControlArray[i].GreenPin);
					LL_GPIO_SetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].RedPort,LEDControlArray[i].RedPin);
					LL_GPIO_ResetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].BluePort,LEDControlArray[i].BluePin);
					break;
				}
			case RGBLedState::Blue:
				if (count > LEDControlArray[i].brightness)
				{
					LL_GPIO_ResetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].GreenPort,LEDControlArray[i].GreenPin);
					LL_GPIO_ResetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].RedPort,LEDControlArray[i].RedPin);
					LL_GPIO_ResetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].BluePort,LEDControlArray[i].BluePin);
					break;
				}
				else
				{
					LL_GPIO_ResetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].GreenPort,LEDControlArray[i].GreenPin);
					LL_GPIO_ResetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].RedPort,LEDControlArray[i].RedPin);
					LL_GPIO_SetOutputPin((GPIO_TypeDef*)&LEDControlArray[i].BluePort,LEDControlArray[i].BluePin);
					break;
				}
			default:
				//We shouldn't ever make it to this case
				///TODO:Write Error Code
				break;

		}
	}
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
