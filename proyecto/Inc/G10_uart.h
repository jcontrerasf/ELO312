/*
 * G10_uart.h
 *
 *  Created on: 28-03-2020
 *      Author: Grupo 10 - Paralelo 1 ELO312 2019-2
 */

#ifndef G10_UART_H_
#define G10_UART_H_

//includes
#include "stdint.h"
#include "main.h"
#include "usart.h"
#include <string.h>


//variables globales
extern uint8_t data;
//extern uint8_t mostrar[3];


//prototipos de funciones
uint8_t G10_uart_es_num(uint8_t);
uint8_t G10_uart_recibir(void);
uint8_t* G10_uart_procesar(void);



#endif /* G10_UART_H_ */
