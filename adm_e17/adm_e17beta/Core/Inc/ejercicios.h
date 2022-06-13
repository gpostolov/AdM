/*
 * ejercicios.h
 *  Ejercicios de la practica en C
 *  Su version en Assembly estan en asm_func
 */

#ifndef INC_EJERCICIOS_H_
#define INC_EJERCICIOS_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx_hal.h"

#define  EJERCICIO_0	0
#define  EJERCICIO_1	0
#define  EJERCICIO_2	0
#define  EJERCICIO_3	0
#define  EJERCICIO_4	0
#define  EJERCICIO_5	0
#define  EJERCICIO_6	0
#define  EJERCICIO_7	0
#define  EJERCICIO_8	0
#define  EJERCICIO_9	0
#define  EJERCICIO_11	1

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

//Ejericio 5
//Un filtro de ventana móvil de 10 valores sobre un vector de muestras.
void filtroVentana10(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitudVectorIn);

//Ejercicio 6
//Recibe un vector de números signados de 32 bits y los “empaqueta” en
//otro vector de 16 bits. Adecua los valores de entrada a la nueva precisión.
void pack32to16 (int32_t * vectorIn, int16_t *vectorOut, uint32_t longitud);

//Ejercicio 7
//Recibe un vector de números signados de 32 bits y devuelve la posición
//del máximo del vector.
int32_t max (int32_t * vectorIn, uint32_t longitud);

//Ejercicio 8
//Recibe un vector de muestras signadas de 32 bits y lo decime
//descartando una cada N muestras.
void downsampleM (int32_t * vectorIn, int32_t * vectorOut, uint32_t longitud, uint32_t N);

//Ejercicio 9
//Recibe un vector de muestras no signadas de 16 bits e invierte su orden.
void invertir (int16_t * vector, uint32_t longitud);

//Ejercicio 11
//Calcula la correlación entre dos vectores.
void corr (int16_t *vectorX, int16_t *vectorY, int16_t *vectorCorr, uint32_t longitud);
void corr_bis (int16_t *vectorX, int16_t *vectorY, int16_t *vectorCorr, uint32_t longitud);
#endif /* INC_EJERCICIOS_H_ */
