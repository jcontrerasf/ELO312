/*
 * my_it_callbacks.c
 *
 *  Created on: 10-03-2020
 *      Author: julio



#include "my_it_callbacks.h"

uint8_t dat[4] = {'o','k','\r','\n'};
static uint8_t buffer_2[10];
uint8_t interrupciones = 0;
uint8_t indice = 0;
uint8_t data;


void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart)
{

 if(huart->Instance == USART2)
 {
   if(indice == 0)
   {
     for (int i = 0; i < 10; i++) {
      buffer_2[i] = 0;
    }
   }
   else if(data != 13)  //13 es enter en ascii
   {
     buffer_2[indice++] = data;
   }
   else
   {
     indice = 0;
     HAL_UART_Transmit(&huart2, buffer_2, sizeof(buffer_2), 100);
     HAL_GPIO_TogglePin(GPIOA,LD2_Pin);
     interrupciones += 1;
   }
   HAL_UART_Receive_IT(&huart2, &data, 1);
 }

}

 */