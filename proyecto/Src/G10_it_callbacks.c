/*
 * G10_it_callbacks.c
 *
 *  Created on: 23-03-2020
 *      Author: Grupo 10 - Paralelo 1 ELO312 2019-2
 *

	  _ _               _ _ _                _
	 (_) |_    ___ __ _| | | |__   __ _  ___| | _____
	 | | __|  / __/ _` | | | '_ \ / _` |/ __| |/ / __|
	 | | |_  | (_| (_| | | | |_) | (_| | (__|   <\__ \
	 |_|\__|  \___\__,_|_|_|_.__/ \__,_|\___|_|\_\___/


 * Este archivo contiene las funciones que se ejecutan cuando ocurren las interrupciones
 */

#include "G10_it_callbacks.h"

int valor = 0;
int angulo = 0;
int brillo = 0;
uint8_t init[3] = {10,10,0};
uint8_t *mostrar = init;

void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart)
{
 static uint8_t transmision_terminada;

 if(huart->Instance == USART2)  // USART que se está usando
 {
	transmision_terminada = G10_uart_recibir();
	if (transmision_terminada)
	{
		mostrar = G10_uart_procesar();

		valor = mostrar[0]*100 + mostrar[1]*10 + mostrar[2];
		if(valor > 180) // En caso de ser mayor a 180°, se satura
		{
		   valor = 180;
		   mostrar[0] = 1;
		   mostrar[1] = 8;
		   mostrar[2] = 0;
		}

		angulo = 300 - ((float)valor/15)*19; //  Se convierte el valor numerico del angulo a un valor
											//  válido para controlar el servo con PWM.
		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2, angulo);
	}
	HAL_UART_Receive_IT(&huart2, &data, 1); // Se reinicia la recepcion
 }
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM2) // Timer que se está usando
  {
    G10_7segmentos_mostrar(GPIOB, mostrar, brillo);
    HAL_ADC_Start_IT(&hadc1); // Se inicia la conversion del ADC con interrupciones
  }
}



void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  if(hadc->Instance == ADC1) // ADC que se está usando
  {
    brillo = G10_adc_leer_brillo(&hadc1);
  }
}
