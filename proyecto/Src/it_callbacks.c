/*
 * it_callbacks.c
 *
 *  Created on: 23-03-2020
 *      Author: julio
 */

#include "it_callbacks.h"

const uint16_t segmentos[10] = {0x80,0xF2,0x48,0x60,0x32,0x24,0x04,0xF0,0x00,0x20};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  static uint8_t contador = 0;
  //contador para indicar que digito mostrar
  if(contador == 3)
  {
    contador = 0;
  }
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_All, GPIO_PIN_RESET);
  //prender un digito a la vez
  switch (contador) {
    case 0:
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, 0);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, 1960);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, 1960);
      break;
    case 1:
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, 1960);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, 0);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, 1960);
      break;
    case 2:
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, 1960);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, 1960);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, 0);
      break;
    default:
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, 0);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, 0);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, 0);
      break;
  }
  //definir los segmentos a mostrar
  uint8_t mostrar[3] = {1,2,0}; // esta variable debe provenir desde la uart

  HAL_GPIO_WritePin(GPIOC, segmentos[mostrar[contador]], GPIO_PIN_SET);

  contador += 1;
}
