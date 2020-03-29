/*
 * it_callbacks.c
 *
 *  Created on: 23-03-2020
 *      Author: julio
 */

#include <G10_it_callbacks.h>

// {0x80,0xF2,0x48,0x60,0x32,0x24,0x04,0xF0,0x00,0x20};

const uint16_t segmentos[11] = {
		a_Pin|b_Pin|c_Pin|d_Pin|e_Pin|f_Pin,			// 0
		b_Pin|c_Pin,									// 1
		a_Pin|b_Pin|d_Pin|e_Pin|g_Pin,					// 2
		a_Pin|b_Pin|c_Pin|d_Pin|g_Pin,					// 3
		b_Pin|c_Pin|f_Pin|g_Pin,						// 4
		a_Pin|c_Pin|d_Pin|f_Pin|g_Pin,					// 5
		a_Pin|c_Pin|d_Pin|e_Pin|f_Pin|g_Pin,			// 6
		a_Pin|b_Pin|c_Pin,								// 7
		a_Pin|b_Pin|c_Pin|d_Pin|e_Pin|f_Pin|g_Pin,		// 8
		a_Pin|b_Pin|c_Pin|d_Pin|f_Pin|g_Pin,			// 9
		0,												// null
};

static volatile uint16_t adc_val;
static volatile float brillo;
static volatile int brillo_int;

uint8_t ok[4] = "ok\r\n";
uint8_t dig1[5] = "uno\r\n";
uint8_t dig2[5] = "dos\r\n";
uint8_t dig3[6] = "tres\r\n";
static char buffer[10];
uint8_t indice = 0;
uint8_t data;
uint8_t mostrar[3] = {10,10,0};
int valor = 0;
int angulo = 0;

int es_num(int num)
{
	if(num >= 48 && num <= 57)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart)
{
 if(huart->Instance == USART2)
 {
   if (indice == 0)         // \ .
   {                  //  |
     for (int i = 0 ; i<10 ; i++) //  | Si no se estan recibiendo datos, entonces
     {                //  | se despeja el buffer.
       buffer[i] = 0;       //  |
     }                // /
   }
   if (data != '\n')          // \ .
   {                  //  | Si se recibe cualquier caracter que no sea un line break,
     buffer[indice++] = data;   // /  entonces agregarlo al buffer.
   }
   else
   {
     indice = 0;
     if (strlen(buffer) < 4)
     {
       if(es_num(buffer[0]) && es_num(buffer[1]) && es_num(buffer[2]))
       {
        HAL_UART_Transmit(&huart2, dig3, 6, 100);
        mostrar[0] = (int)buffer[0] - 48;
        mostrar[1] = (int)buffer[1] - 48;
        mostrar[2] = (int)buffer[2] - 48;
       }
       else if(es_num(buffer[0]) && es_num(buffer[1]))
       {
        HAL_UART_Transmit(&huart2, dig2, 5, 100);
        mostrar[2] = (int)buffer[1] - 48;
        mostrar[1] = (int)buffer[0] - 48;
        mostrar[0] = 0;
       }
       else if(es_num(buffer[0]))
       {
        HAL_UART_Transmit(&huart2, dig1, 5, 100);
        mostrar[2] = (int)buffer[0] - 48;
        mostrar[1] = 0;
        mostrar[0] = 0;
       }

       valor = mostrar[0]*100 + mostrar[1]*10 + mostrar[2];
       if(valor > 180)
       {
        valor = 180;
        mostrar[0] = 1;
        mostrar[1] = 8;
        mostrar[2] = 0;
       }
     }

     if (mostrar[0] == 0)
     {
       mostrar[0] = 10;
       if (mostrar[1] == 0)
       {
         mostrar[1] = 10;
       }
     }

     angulo = 300 - ((float)valor/15)*19;
     __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2, angulo);

   }
   HAL_UART_Receive_IT(&huart2, &data, 1);
 }
}

#define offset -25658.2
#define slope 8.90909


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	if(hadc->Instance == ADC1) //aquí poner el ADC que se está usando
	{
	adc_val = HAL_ADC_GetValue(&hadc1);
    brillo = 1960 - (adc_val*slope + offset);
    brillo_int = (int)brillo;
    if (brillo_int > 1960)
    {
    	brillo_int = 1960;
    }
    if (brillo_int < 1)
    {
    	brillo_int = 0;
    }
	}
}


#define on brillo_int
#define off 1960


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
  HAL_ADC_Start_IT(&hadc1);
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
