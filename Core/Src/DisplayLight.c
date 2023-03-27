/*
 * DisplayLight.c
 *
 *  Created on: Jan 26, 2022
 *      Author: Margit Robert
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "DisplayLight.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static TIM_HandleTypeDef *_htim;
uint8_t _backlightPercent;
uint8_t _backlightEnabled;

/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/

void BacklightInit(TIM_HandleTypeDef *htim)
{
  _htim = htim;
  HAL_TIM_PWM_Start(_htim,TIM_CHANNEL_4);
  BacklightSet(10);
}

uint8_t BacklightGet(void)
{
  return _backlightPercent;
}

void BacklightSet(uint8_t percent)
{
  _backlightPercent = percent;
  percent = 100 - percent;
  uint32_t arr = __HAL_TIM_GET_AUTORELOAD(_htim);
  uint32_t ccr = (arr * percent) / 100;
  __HAL_TIM_SET_COMPARE(_htim,TIM_CHANNEL_4, ccr);
}

void BacklightEn(uint8_t onoff)
{
  if(onoff)
  {
    _backlightEnabled = 1,
    HAL_GPIO_WritePin(DISP_EN_GPIO_Port, DISP_EN_Pin, GPIO_PIN_SET);
  }
  else
  {
    _backlightEnabled = 0,
    HAL_GPIO_WritePin(DISP_EN_GPIO_Port, DISP_EN_Pin, GPIO_PIN_RESET);
  }
}


uint8_t BacklightIsEnabled(void)
{
  return _backlightEnabled;
}

/************************ (C) COPYRIGHT KonvolucioBt ***********END OF FILE****/
