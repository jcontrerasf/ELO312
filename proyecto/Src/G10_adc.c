/*
 * G10_adc.c
 *
 *  Created on: 28-03-2020
 *      Author: julio
 */

#define offset -25658.2
#define slope 8.90909


int G10_adc_leer_valor()
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
  return brillo_int;
}


