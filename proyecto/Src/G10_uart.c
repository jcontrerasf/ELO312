/*
 * G10_uart.c
 *
 *  Created on: 28-03-2020
 *      Author: Grupo 10 - Paralelo 1 ELO312 2019-2
 */

#include "G10_uart.h"

uint8_t data;
uint8_t mostrar[3] = {10,10,0};

void G10_uart_recibir() //Basado en: https://www.youtube.com/watch?v=VdHt_wJdezM
{
  static char buffer[10];
  static uint8_t indice = 0;
  uint8_t dig1[5] = "uno\r\n";
  uint8_t dig2[5] = "dos\r\n";
  uint8_t dig3[6] = "tres\r\n";

  if (indice == 0)                  // \ .
     {                              //  |
       for (int i = 0 ; i<10 ; i++) //  | Si no se estan recibiendo datos, entonces
       {                            //  | se despeja el buffer.
         buffer[i] = 0;             //  |
       }                            // /
     }
     if (data != '\n')             // \ .
     {                             //  | Si se recibe cualquier caracter que no sea un line break,
       buffer[indice++] = data;    // /  entonces agregarlo al buffer.
     }
     else
     {
       indice = 0;
       return buffer;
     }
}


int G10_uart_procesar(){
  if (strlen(buffer) < 4)
         {
           if(G10_uart_es_num(buffer[0]) && G10_uart_es_num(buffer[1]) && G10_uart_es_num(buffer[2]))
           {
            HAL_UART_Transmit(&huart2, dig3, 6, 100);
            mostrar[0] = (int)buffer[0] - 48;
            mostrar[1] = (int)buffer[1] - 48;
            mostrar[2] = (int)buffer[2] - 48;
           }
           else if(G10_uart_es_num(buffer[0]) && G10_uart_es_num(buffer[1]))
           {
            HAL_UART_Transmit(&huart2, dig2, 5, 100);
            mostrar[2] = (int)buffer[1] - 48;
            mostrar[1] = (int)buffer[0] - 48;
            mostrar[0] = 0;
           }
           else if(G10_uart_es_num(buffer[0]))
           {
            HAL_UART_Transmit(&huart2, dig1, 5, 100);
            mostrar[2] = (int)buffer[0] - 48;
            mostrar[1] = 0;
            mostrar[0] = 0;
           }

           valor = mostrar[0]*100 + mostrar[1]*10 + mostrar[2];
           if(valor > 180)
           {
            valor = 180;
            mostrar[0] = 1;
            mostrar[1] = 8;
            mostrar[2] = 0;
           }
         }


         angulo = 300 - ((float)valor/15)*19;
         __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2, angulo);
}

int G10_uart_es_num(int num)
{
  if(num >= 48 && num <= 57)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}