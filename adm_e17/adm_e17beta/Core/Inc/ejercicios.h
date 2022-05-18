/*
 * ejercicios.h
 *
 *  Created on: May 18, 2022
 *      Author: Gabriel
 */

#ifndef INC_EJERCICIOS_H_
#define INC_EJERCICIOS_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx_hal.h"

//Ejercicio 1
//Realizar una función que inicialice un vector con ceros.
void zeros (uint32_t * vector, uint32_t longitud);

//Ejercicio 2
//Realizar una función que realice el producto de un vector y un escalar
//(por ejemplo, podría servir para cambiar el nivel de amplitud de una señal).
void productoEscalar32 (uint32_t * vectorIn, uint32_t * vectorOut, uint32_t longitud, uint32_t escalar);

//Ejercicio 3
//Adapte la función del ejercicio 2 para realizar operaciones sobre vectores de 16 bits
void productoEscalar16 (uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar);

//Ejericio 4
//Adapte la función del ejercicio 3 para saturar el resultado del producto a 12 bits
void productoEscalar12 (uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar);

#endif /* INC_EJERCICIOS_H_ */
