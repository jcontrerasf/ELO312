/*
 * my_it_callbacks.c
 *
 *  Created on: 09-03-2020
 *      Author: julio
 */


//esto es para el 1.3 !!!!!!!!!!!!!!!!!!!

#include "my_it_callbacks.h"

static volatile uint16_t data;
double promedio;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) //no se si esta bien el *
 {
   if(hadc->Instance == ADC1) //aqu� poner el ADC que se est� usando
   {
    data = HAL_ADC_GetValue(&hadc1);
    promedio = promedio_ultimos((double) HAL_ADC_GetValue(&hadc1));
    prender_leds(data);
    HAL_ADC_Start_IT(&hadc1);
   }

 }

 double promedio_ultimos(double ultimo)
 {
   static double lista[5];

   lista[4] = lista[3];
   lista[3] = lista[2];
   lista[2] = lista[1];
   lista[1] = lista[0];
   lista[4] = ultimo;

   return (lista[0]+lista[1]+lista[2]+lista[3]+lista[4])/5;
 }

void prender_leds(double valor)
{
  HAL_GPIO_WritePin(GPIOA,out1_Pin|out2_Pin|out3_Pin|out4_Pin|out5_Pin|out6_Pin|out7_Pin|out8_Pin,GPIO_PIN_RESET);
  //primero se resetean todos los leds

  if(valor == 0)
  {
    HAL_GPIO_WritePin(GPIOA,out1_Pin|out2_Pin|out3_Pin|out4_Pin|out5_Pin|out6_Pin|out7_Pin|out8_Pin,GPIO_PIN_RESET);
  }
  else if(valor < 500) //intervalos de 4033/8
  {
    HAL_GPIO_WritePin(GPIOA,out1_Pin,GPIO_PIN_SET);
  }
  else if(valor < 1000)
  {
    HAL_GPIO_WritePin(GPIOA,out1_Pin|out2_Pin,GPIO_PIN_SET);
  }
  else if(valor < 2000)
  {
    HAL_GPIO_WritePin(GPIOA,out1_Pin|out2_Pin|out3_Pin,GPIO_PIN_SET);
  }
  else if(valor < 2500)
  {
    HAL_GPIO_WritePin(GPIOA,out1_Pin|out2_Pin|out3_Pin|out4_Pin,GPIO_PIN_SET);
  }
  else if(valor < 3000)
  {
    HAL_GPIO_WritePin(GPIOA,out1_Pin|out2_Pin|out3_Pin|out4_Pin|out5_Pin,GPIO_PIN_SET);
  }
  else if(valor < 3500)
  {
    HAL_GPIO_WritePin(GPIOA,out1_Pin|out2_Pin|out3_Pin|out4_Pin|out5_Pin|out6_Pin,GPIO_PIN_SET);
  }
  else if(valor < 4000)
  {
    HAL_GPIO_WritePin(GPIOA,out1_Pin|out2_Pin|out3_Pin|out4_Pin|out5_Pin|out6_Pin|out7_Pin,GPIO_PIN_SET);
  }
  else
  {
    HAL_GPIO_WritePin(GPIOA,out1_Pin|out2_Pin|out3_Pin|out4_Pin|out5_Pin|out6_Pin|out7_Pin|out8_Pin,GPIO_PIN_SET);
  }
}
