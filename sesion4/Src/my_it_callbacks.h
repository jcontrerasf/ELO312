/*
 * my_it_callbacks.h
 *
 *  Created on: 09-03-2020
 *      Author: julio
 */

#ifndef MY_IT_CALLBACKS_H_
#define MY_IT_CALLBACKS_H_

#include "stdint.h"
#include "gpio.h"
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"


void prender_leds(double);

double promedio_ultimos(double);

#endif /* MY_IT_CALLBACKS_H_ */