/*
 * it_callbacks.h
 *
 *  Created on: 23-03-2020
 *      Author: julio
 */

#ifndef IT_CALLBACKS_H_
#define IT_CALLBACKS_H_

#include "stdint.h"
#include "gpio.h"
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include <string.h>

int es_num(int num);

extern uint8_t data;  //muy importante para usar data en main.c

#endif /* IT_CALLBACKS_H_ */
