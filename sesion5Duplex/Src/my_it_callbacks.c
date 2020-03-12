/*
 * my_it_callbacks.c
 *
 *  Created on: 05-03-2020
 *      Author: julio
 */


#include "my_it_callbacks.h"

uint8_t interrupciones = 0;
uint8_t switches[1];
uint8_t enviar[1];

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switches[0] = 0;

  if(GPIO_Pin == enviar_Pin)
  {
    interrupciones++;
    switches[0] |= HAL_GPIO_ReadPin(GPIOC,switch1_Pin);
    switches[0] |= HAL_GPIO_ReadPin(GPIOC,switch2_Pin)<<1;
    switches[0] |= HAL_GPIO_ReadPin(GPIOC,switch3_Pin)<<2;
    switches[0] += HAL_GPIO_ReadPin(GPIOC,switch4_Pin);
    enviar[0] = switches[0]+48;
    HAL_UART_Transmit(&huart2, enviar, 1, 100);
  }

}

