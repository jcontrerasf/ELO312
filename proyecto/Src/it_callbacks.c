/*
 * it_callbacks.c
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

#include "it_callbacks.h"


int brillo = 0;
uint8_t *mostrar;


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM2) // Timer que se está usando
  {
    G10_7segmentos_mostrar(GPIOB, mostrar, brillo);
    HAL_ADC_Start_IT(&hadc1); // se inicia la conversion del ADC con interrupciones
  }
}


void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart)
{
 if(huart->Instance == USART2)  // USART que se está usando
 {
   G10_uart_recibir();
   mostrar = G10_uart_procesar();
   HAL_UART_Receive_IT(&huart2, &data, 1); //se reinicia la recepcion
 }
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  if(hadc->Instance == ADC1) // ADC que se está usando
  {
    brillo = G10_adc_leer_brillo(&hadc1);
  }
}
