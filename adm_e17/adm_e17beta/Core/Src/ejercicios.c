/*
 * ejercicios.c
 *
 *  Created on: May 18, 2022
 *      Author: Gabriel
 */

#include "ejercicios.h"

//
//void zeros (uint32_t * vector, uint32_t longitud){
//	memset(vector, 0, longitud);
//}

//1)
//Lo hago asi para poder comparar contra el codigo en assembly
void zeros (uint32_t * vector, uint32_t longitud){
	for(uint32_t i = 0; i < longitud; i++){
		vector[i]=0;
	}
}

//2)
//No hago ningun tipo de comprobacion de datos ni de overload
void productoEscalar32 (uint32_t * vectorIn, uint32_t * vectorOut, uint32_t longitud, uint32_t escalar){
	for(uint32_t i = 0; i < longitud; i++){
		vectorOut[i]=(uint32_t)(vectorIn[i]*escalar);
	}
}

//3)
//No hago ningun tipo de comprobacion de datos ni de overload
void productoEscalar16 (uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar){
	for(uint32_t i = 0; i < longitud; i++){
		vectorOut[i]=(uint16_t)(vectorIn[i]*escalar);
	}
}

//4) Idem 3 pero satura en 12bits
void productoEscalar12 (uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar){
	for(uint32_t i = 0; i < longitud; i++){
		vectorOut[i]=((vectorIn[i]*escalar)>0x0FFF)?0x0FFF:(vectorIn[i]*escalar);
	}
}
