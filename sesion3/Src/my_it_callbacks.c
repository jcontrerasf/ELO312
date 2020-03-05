/*
 * my_it_callbacks.c
 *
 *  Created on: 05-03-2020
 *      Author: julio
 */


#include "my_it_callbacks.h"


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == in1_Pin)
  {
    funcion_change();
  }
}

