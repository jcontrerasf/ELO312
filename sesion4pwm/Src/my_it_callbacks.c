/*
 * my_it_callbacks.c
 *
 *  Created on: 09-03-2020
 *      Author: julio
 */


//esto es para el 1.3 !!!!!!!!!!!!!!!!!!!

#include "my_it_callbacks.h"

static volatile uint16_t data;
static volatile float brillo;
static volatile int brillo_int;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
 {
   if(hadc->Instance == ADC1) //aqu� poner el ADC que se est� usando
   {
    data = HAL_ADC_GetValue(&hadc1);
    brillo = 0.478*data;
    brillo_int = (int) brillo;
    __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, brillo_int);
    HAL_ADC_Start_IT(&hadc1);
   }

 }
