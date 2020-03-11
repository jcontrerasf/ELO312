/*
 * my_it_callbacks.c
 *
 *  Created on: 05-03-2020
 *      Author: julio
 */


#include "my_it_callbacks.h"


static uint64_t tim_interrupt_counter = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == in1_Pin)
  {

  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  tim_interrupt_counter += 1;

  HAL_GPIO_TogglePin(GPIOA, out1_Pin);

  if(tim_interrupt_counter%2 == 0)
    {
      HAL_GPIO_TogglePin(GPIOA, out2_Pin);
    }

  if(tim_interrupt_counter%5 == 0)
  {
    HAL_GPIO_TogglePin(GPIOA, out3_Pin);
  }

  if(tim_interrupt_counter%10 == 0)
    {
      HAL_GPIO_TogglePin(GPIOA, out4_Pin);
    }
}
