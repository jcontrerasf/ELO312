/*
 * G10_adc.c
 *
 *  Created on: 28-03-2020
 *      Author: Grupo 10 - Paralelo 1 ELO312 2019-2


		 _    ____   ____
		/ \  |  _ \ / ___|
	   / _ \ | | | | |
	  / ___ \| |_| | |___
	 /_/   \_\____/ \____|


 */

#include "G10_adc.h"

#define offset -25658.2
#define slope 8.90909

/*
 * @brief Lee el valor desde la fotorresistencia conectada al ADC y lo convierte
 * @note  offset y slope se usan para la conversion de datos y dependen de la luz ambiente
 *        y la calidad de la fotorresistencia.
 * @param hadc: ADC handle
 * @retval brillo en variable de tipo int en el rango valido para G10_7segmentos_mostrar().
 */

int G10_adc_leer_brillo(ADC_HandleTypeDef *hadc)
{
  static volatile uint16_t adc_val;
  static volatile float brillo;
  static volatile int brillo_int;

  adc_val = HAL_ADC_GetValue(hadc);
  brillo = 1960 - (adc_val*slope + offset);
  brillo_int = (int)brillo; // Se convierte a int

  if (brillo_int > 1960) // En caso de ser mayor, se satura a 1960
  {
    brillo_int = 1960;
  }
  if (brillo_int < 1) // En caso de ser menor, se satura a 0
  {
    brillo_int = 0;
  }
  return brillo_int;
}

