/*
 * G10_uart.c
 *
 *  Created on: 28-03-2020
 *      Author: Grupo 10 - Paralelo 1 ELO312 2019-2


	  _   _   _    ____ _____
	 | | | | / \  |  _ \_   _|
	 | | | |/ _ \ | |_) || |
	 | |_| / ___ \|  _ < | |
	  \___/_/   \_\_| \_\|_|


 */

#include "G10_uart.h"

uint8_t data;
static char buffer[10];


/*
 * @brief Acumula en un buffer los datos recibidos por UART
 */

uint8_t G10_uart_recibir() // Basado en: https://www.youtube.com/watch?v=VdHt_wJdezM
{
  static uint8_t indice = 0;

	if (indice == 0)                  // \ .
	{                              //  |
	   for (int i = 0 ; i<10 ; i++) //  | Si no se estan recibiendo datos, entonces
	   {                            //  | se despeja el buffer.
		 buffer[i] = 0;             //  |
	   }                            // /
	}
	if (data != '\n')              // \ .
	{                              //  | Si se recibe cualquier caracter que no sea un line break,
	buffer[indice++] = data;     // /  entonces agregarlo al buffer.
	return 0;
	}
	else
	{
	indice = 0;
	return 1;
	}
}

/*
 * @brief Procesa los datos del buffer para definir el angulo del servo y mostrar el valor en el display
 * @retval puntero al array que debe mostrarse.
 */

uint8_t* G10_uart_procesar(){

  uint8_t dig1[5] = "uno\r\n";
  uint8_t dig2[5] = "dos\r\n";
  uint8_t dig3[6] = "tres\r\n";
  static uint8_t mostrar[3] = {10,10,0};

  if (strlen(buffer) < 4)
	 {
	   if(G10_uart_es_num(buffer[0]) && G10_uart_es_num(buffer[1]) && G10_uart_es_num(buffer[2]))
	   {
		HAL_UART_Transmit(&huart2, dig3, 6, 100); // Se envia un mensaje de verificacion
		/*
		* Una manera sencilla de convertir un caracter numerico a un entero es restarle 48, porque '0' = 48 en ASCII.
		* Ejemplo: '1' es el caracter 49 -> 49-48 = 1.
		* Sin embargo, para evitar el uso de "magic numbers" se restara '0' en vez de 48, aunque es lo mismo.
		*/
		mostrar[0] = (int)buffer[0] - '0';
		mostrar[1] = (int)buffer[1] - '0';
		mostrar[2] = (int)buffer[2] - '0';
	   }
	   else if(G10_uart_es_num(buffer[0]) && G10_uart_es_num(buffer[1]))
	   {
		HAL_UART_Transmit(&huart2, dig2, 5, 100); // Se envia un mensaje de verificacion
		mostrar[2] = (int)buffer[1] - '0';
		mostrar[1] = (int)buffer[0] - '0';
		mostrar[0] = 0;
	   }
	   else if(G10_uart_es_num(buffer[0]))
	   {
		HAL_UART_Transmit(&huart2, dig1, 5, 100); // Se envia un mensaje de verificacion
		mostrar[2] = (int)buffer[0] - '0';
		mostrar[1] = 0;
		mostrar[0] = 0;
	   }

	 }
	return mostrar;
}

/*
 * @brief Detecta si el caracter corresponde a un numero
 * @param num: caracter a analizar
 * @retval 1 si es un numero, 0 si no
 */

uint8_t G10_uart_es_num(uint8_t num)
{
  if(num >= '0' && num <= '9')
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
