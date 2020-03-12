/*
 * my_it_callbacks.c
 *
 *  Created on: 10-03-2020
 *      Author: julio

*/

#include "my_it_callbacks.h"

uint8_t ok[4] = {'o','k','\r','\n'};
static uint8_t buffer[10];
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
      buffer[i] = 0;
    }
   }
   if(data != '\n')//esto se usa para indicar que cuando termina un mensaje
   {
     buffer[indice++] = data;
   }
   else //el mensaje DEBE tener '\n' al final para entrar en este else
   {
     indice = 0;
     interrupciones += 1;
     HAL_UART_Transmit(&huart2, ok, 4, 100); //cuando el MCU recibe algo envía 'ok'
     if(buffer[0] == 'o' && buffer[1] == 'n' && buffer[2] == '\0') //al enviar on\n  se prende
     //el caracter \0 es para asegurar que solo se mandó 'on\n' y no, por ejemplo, 'onu\n'
     {
       HAL_GPIO_WritePin(GPIOA,LD2_Pin,GPIO_PIN_SET);
     }
     else if(buffer[0] == 'o' && buffer[1] == 'f' && buffer[2] == 'f' && buffer[3] == '\0') //al enviar off\n se apaga
     {
       HAL_GPIO_WritePin(GPIOA,LD2_Pin,GPIO_PIN_RESET);
     }
   }
   HAL_UART_Receive_IT(&huart2, &data, 1);
 }

}
