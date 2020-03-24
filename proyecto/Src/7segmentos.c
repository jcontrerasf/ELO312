/*
 * 7segmentos.c
 *
 *  Created on: 24-03-2020
 *      Author: Julio Contreras

  _____                                       _
 |___  |  ___  ___  __ _ _ __ ___   ___ _ __ | |_ ___  ___
    / /  / __|/ _ \/ _` | '_ ` _ \ / _ \ '_ \| __/ _ \/ __|
   / /   \__ \  __/ (_| | | | | | |  __/ | | | || (_) \__ \
  /_/    |___/\___|\__, |_| |_| |_|\___|_| |_|\__\___/|___/
                   |___/

* Se utilizara un display de 7 segmentos con 4 digitos, modelo CL5641AH.
* Este modelo es de anodo(positivo) comun, por lo tanto, para encender
* cada segmento se debe setear un 0.
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
* Especificamente se usa el puerto GPIOC. El pin 0 de ese puerto esta siendo utilizado por
* el ADC1, de modo que no se modifica aqui (ver columna x). Los siguientes pines se utilizan
* de manera continua, del 1 al 6 estan conectados a los segmentos a al g, respectivamente.
* Esto esta basado en el funcionamiento de la funcion HAL_GPIO_WritePin y de las definiciones
* de GPIO_PIN_X (linea 84 de stm32l4xx_hal_gpio.h).

+-------+---+---+---+---+---+---+---+---+------+
| valor | g | f | e | d | c | b | a | x | HEX  |
+-------+---+---+---+---+---+---+---+---+------+
|   0   | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x80 |
+-------+---+---+---+---+---+---+---+---+------+
|   1   | 1 | 1 | 1 | 1 | 0 | 0 | 1 | 0 | 0xF2 |
+-------+---+---+---+---+---+---+---+---+------+
|   2   | 0 | 1 | 0 | 0 | 1 | 0 | 0 | 0 | 0x48 |
+-------+---+---+---+---+---+---+---+---+------+
|   3   | 0 | 1 | 1 | 0 | 0 | 0 | 1 | 0 | 0x60 |
+-------+---+---+---+---+---+---+---+---+------+
|   4   | 0 | 0 | 1 | 1 | 0 | 0 | 1 | 0 | 0x32 |
+-------+---+---+---+---+---+---+---+---+------+
|   5   | 0 | 0 | 1 | 0 | 0 | 1 | 0 | 0 | 0x24 |
+-------+---+---+---+---+---+---+---+---+------+
|   6   | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0x04 |
+-------+---+---+---+---+---+---+---+---+------+
|   7   | 1 | 1 | 1 | 1 | 0 | 0 | 0 | 0 | 0xF0 |
+-------+---+---+---+---+---+---+---+---+------+
|   8   | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0x00 |
+-------+---+---+---+---+---+---+---+---+------+
|   9   | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0x20 |
+-------+---+---+---+---+---+---+---+---+------+



 */


