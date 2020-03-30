/*
 * G10_7segmentos.c
 *
 *  Created on: 24-03-2020
 *      Author: Grupo 10 - Paralelo 1 ELO312 2019-2

  _____                                       _
 |___  |  ___  ___  __ _ _ __ ___   ___ _ __ | |_ ___  ___
    / /  / __|/ _ \/ _` | '_ ` _ \ / _ \ '_ \| __/ _ \/ __|
   / /   \__ \  __/ (_| | | | | | |  __/ | | | || (_) \__ \
  /_/    |___/\___|\__, |_| |_| |_|\___|_| |_|\__\___/|___/
                   |___/

* Se utilizara un display de 7 segmentos con 4 digitos, modelo CL5641AH.
* Este modelo es de catodo(negativo) comun, por lo tanto, para encender
* cada segmento se debe setear un 1, mientras que para activar cada digito, estos deben ir a 0V.
* A continuacion se muestra el nombre de cada segmento.
		___________
	   /     a     \
	  _\___________/ _
	/   \          /   \
	|   |          |   |
	| f |          |   |
	|   |          | b |
	|   |          |   |
	\ _ /__________\ _ /
	   /     g     \
	  _\___________/ _
	/   \          /   \
	|   |          |   |
	| e |          |   |
	|   |          | c |
	|   |          |   |
	\ _ /__________\ _ /
		/     d    \
		\__________/


* Para reducir la cantidad de instrucciones se decide usar un solo puerto para los segmentos.
*/

#include "G10_7segmentos.h"
#define off 1960


//Se definen los segmentos a encender dependiendo del numero a mostrar
const uint16_t segmentos[11] = {
    a_Pin|b_Pin|c_Pin|d_Pin|e_Pin|f_Pin,        // 0
    b_Pin|c_Pin,                                // 1
    a_Pin|b_Pin|d_Pin|e_Pin|g_Pin,              // 2
    a_Pin|b_Pin|c_Pin|d_Pin|g_Pin,              // 3
    b_Pin|c_Pin|f_Pin|g_Pin,                    // 4
    a_Pin|c_Pin|d_Pin|f_Pin|g_Pin,              // 5
    a_Pin|c_Pin|d_Pin|e_Pin|f_Pin|g_Pin,        // 6
    a_Pin|b_Pin|c_Pin,                          // 7
    a_Pin|b_Pin|c_Pin|d_Pin|e_Pin|f_Pin|g_Pin,  // 8
    a_Pin|b_Pin|c_Pin|d_Pin|f_Pin|g_Pin,        // 9
    0,                                          // todos los segmentos apagados
};

/*
 * @brief Enciende los segmentos que corresponden de un digito a la vez.
 * @note Cada vez que se llama esta funcion enciende el siguiente digito con los segmentos que corresponden.
 * @note Esta hecha para controlar 3 digitos.
 * @note Todos los segmentos deben estar conectados al mismo puerto
 * @param GPIOx: puerto al que estan conectados los segmentos
 * @param brillo: brillo de los digitos. Admite valores entre 0 (maximo brillo) y 1960 (minimo brillo).
 */

void G10_7segmentos_mostrar(GPIO_TypeDef* GPIOx, uint8_t* mostrar , int brillo)
{
    static uint8_t contador = 0;  //contador para indicar que digito mostrar

    if(contador == 3) //se resetea el contador cuando llega a 3
    {
      contador = 0;
    }

    HAL_GPIO_WritePin(GPIOx, GPIO_PIN_All, GPIO_PIN_RESET); //se apagan los segmentos
                                                            //del digito anterior

    //se enciende un digito a la vez
    switch (contador) {
        case 0:
          __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, brillo);
          __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, off);
          __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, off);
          break;
        case 1:
          __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, off);
          __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, brillo);
          __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, off);
          break;
        case 2:
          __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, off);
          __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, off);
          __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, brillo);
          break;
        default:
          HAL_GPIO_WritePin(GPIOx, GPIO_PIN_All, GPIO_PIN_RESET);
          __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2, off);
          __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3, off);
          __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4, off);
          break;
      }

      //se eliminan los ceros a la izquierda
      if (mostrar[0] == 0)
        {
          mostrar[0] = 10;
          if (mostrar[1] == 0)
            {
              mostrar[1] = 10;
            }
         }

      //se encienden los segmentos que corresponden
      HAL_GPIO_WritePin(GPIOx, segmentos[mostrar[contador]], GPIO_PIN_SET);

      //se incrementa el contador para cambiar de digito en la siguiente llamada
      contador++;
}
