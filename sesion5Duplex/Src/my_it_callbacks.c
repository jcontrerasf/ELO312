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

static uint8_t buffer[10];
uint8_t indice = 0;
uint8_t data;

uint8_t flag = 0;

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
    enviar[0] = switches[0]+48; //se convierte a ascii
    HAL_UART_Transmit(&huart2, enviar, 1, 100);
  }
}



void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart)
{

 if(huart->Instance == USART2)
 {
   if(indice == 0)
   {
     for (int i = 0; i < 10; i++) {
      buffer[i] = 0;
    }
   }
   if(data != '\n')//esto se usa para indicar que cuando termina un mensaje
   {
     buffer[indice++] = data;
   }
   else
   {
     indice = 0;
     if(buffer[0] == 'o' && buffer[1] == 'k')
     {
       HAL_GPIO_TogglePin(GPIOC,LED_azul_Pin);
       //flag = 1;
       //HAL_GPIO_WritePin(GPIOC,LED_azul_Pin,GPIO_PIN_RESET);
     }
   }
   HAL_UART_Receive_IT(&huart2, &data, 1);
 }

}
