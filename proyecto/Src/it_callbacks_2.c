/*
 * it_callbacks.c
 *
 *  Created on: 23-03-2020
 *      Author: julio
 */

#include "it_callbacks.h"

#define on 0
#define off 1960
// {0x80,0xF2,0x48,0x60,0x32,0x24,0x04,0xF0,0x00,0x20};

const uint16_t segmentos[10] = {
		a_Pin|b_Pin|c_Pin|d_Pin|e_Pin|f_Pin,			// 0
		b_Pin|c_Pin,									// 1
		a_Pin|b_Pin|d_Pin|e_Pin|g_Pin,					// 2
		a_Pin|b_Pin|c_Pin|d_Pin|g_Pin,					// 3
		b_Pin|c_Pin|f_Pin|g_Pin,						// 4
		a_Pin|c_Pin|d_Pin|f_Pin|g_Pin,					// 5
		a_Pin|c_Pin|d_Pin|e_Pin|f_Pin|g_Pin,			// 6
		a_Pin|b_Pin|c_Pin,								// 7
		a_Pin|b_Pin|c_Pin|d_Pin|e_Pin|f_Pin|g_Pin,		// 8
		a_Pin|b_Pin|c_Pin|d_Pin|f_Pin|g_Pin				// 9
};

uint8_t ok[4] = "ok\r\n";
uint8_t dig1[5] = "uno\r\n";
uint8_t dig2[5] = "dos\r\n";
uint8_t dig3[5] = "tres\r\n";
static char buffer[10];
uint8_t indice = 0;
uint8_t data;
uint8_t mostrar[3] = {0,0,0};

void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart)
{
 if(huart->Instance == USART2)
 {
	 if (indice == 0)					// \ .
	 {									//  |
		 for (int i = 0 ; i<10 ; i++)	//  | Si no se estan recibiendo datos, entonces
		 {								//  | se despeja el buffer.
			 buffer[i] = 0;				//  |
		 }								// /
	 }
	 if (data != '\n')					// \ .
	 {									//  | Si se recibe cualquier caracter que no sea un line break,
		 buffer[indice++] = data;		// /  entonces agregarlo al buffer.
	 }
	 else
	 {
	     indice = 0;
		 if (isdigit(buffer[0]) && isdigit(buffer[1]) && isdigit(buffer[2]))
		 {
			 if (strlen(buffer) == 1)
			 {
				 HAL_UART_Transmit(&huart2, dig1, 5, 100);
				 mostrar[2] = (int)buffer[0] - 48;
				 mostrar[1] = 0;
				 mostrar[0] = 0;
			 }
			 else if (strlen(buffer) == 2)
			 {
				 HAL_UART_Transmit(&huart2, dig2, 5, 100);
				 mostrar[2] = (int)buffer[1] - 48;
				 mostrar[1] = (int)buffer[0] - 48;
				 mostrar[0] = 0;
			 }
			 else if (strlen(buffer) == 3)
			 {
				 HAL_UART_Transmit(&huart2, dig3, 5, 100);
				 mostrar[2] = (int)buffer[2] - 48;
				 mostrar[1] = (int)buffer[1] - 48;
				 mostrar[0] = (int)buffer[0] - 48;
			 }
		 }
	 }
	 HAL_UART_Receive_IT(&huart2, &data, 1);
 }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_All, GPIO_PIN_RESET);
  static uint8_t contador = 0;
  //contador para indicar que digito mostrar
  if(contador == 3)
  {
    contador = 0;
  }
  //prender un digito a la vez
  switch (contador) {
    case 0:
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, on);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, off);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, off);
      break;
    case 1:
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, off);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, on);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, off);
      break;
    case 2:
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, off);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, off);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, on);
      break;
    default:
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_All, GPIO_PIN_RESET);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, off);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, off);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, off);
      break;
  }
  HAL_GPIO_WritePin(GPIOB, segmentos[mostrar[contador]], GPIO_PIN_SET);

  contador += 1;
}













/*
    case 0:
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, on);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, off);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, off);
      HAL_GPIO_WritePin(GPIOB, segmentos[mostrar[contador]], GPIO_PIN_SET);
      break;
    case 1:
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, off);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, on);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, off);
      HAL_GPIO_WritePin(GPIOB, segmentos[mostrar[contador]], GPIO_PIN_SET);
      break;
    case 2:
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, off);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, off);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, on);
      HAL_GPIO_WritePin(GPIOB, segmentos[mostrar[contador]], GPIO_PIN_SET);
      break;
    default:
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, off);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, off);
      __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, off);
      HAL_GPIO_WritePin(GPIOB, segmentos[mostrar[contador]], GPIO_PIN_RESET);
      break;
      */
