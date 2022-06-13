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

//Ejericio 5
//Un filtro de ventana móvil de 10 valores sobre un vector de muestras.
void filtroVentana10(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitudVectorIn){
	int32_t i = 0;
	int32_t j = 0;
	int32_t VENTANA_MOVIL = 10;
	uint16_t filt_aux = 0;

	for (i = 0; i< longitudVectorIn ; i++){ //vector
		filt_aux = 0;
		for (j = 0; j < 10; j++){			//ventana
			VENTANA_MOVIL = 10;
			if ((i-j)>= 0){  //Para los primeros 10 valores del vectorIn que no tiene con que filtrar.
				filt_aux = filt_aux + vectorIn[i-j];
			}else{
				VENTANA_MOVIL = j;
				break; //Salgo del for de la ventana
			}
		}
		vectorOut[i] = filt_aux/VENTANA_MOVIL;
	}
}

//Ejercicio 6
//Recibe un vector de números signados de 32 bits y los “empaqueta” en
//otro vector de 16 bits. Adecua los valores de entrada a la nueva precisión.
void pack32to16 (int32_t * vectorIn, int16_t *vectorOut, uint32_t longitud){
	uint32_t i = 0;

	for (i = 0; i< longitud ; i++){
		vectorOut[i]= (int16_t)(vectorIn[i]>>16);
	}
}

//Ejercicio 7
//Recibe un vector de números signados de 32 bits y devuelve la posición
//del máximo del vector.
int32_t max (int32_t * vectorIn, uint32_t longitud){
	uint32_t i = 0;
	uint16_t max_aux = 0;
	uint16_t max_pos = 0;

	for (i = 0; i< longitud ; i++){
		//Max
		if( max_aux < vectorIn[i] ){
			max_aux = vectorIn[i];
			max_pos = i;
		}
	}
	return max_pos;
}

//Ejercicio 8
//Recibe un vector de muestras signadas de 32 bits y lo decime
//descartando una cada N muestras.
void downsampleM (int32_t * vectorIn, int32_t * vectorOut, uint32_t longitud, uint32_t N){
	uint32_t i = 0;
	uint32_t j = 0;

	for (i = 0; i< longitud ; i++){
		//Decime
		if( !(i%N) ){
			vectorOut[j] = vectorIn[i];
			j++;
		}
	}
}

//Ejercicio 9
//Recibe un vector de muestras no signadas de 16 bits e invierte su orden.
void invertir (int16_t * vector, uint32_t longitud){
	uint32_t i = 0;
	uint16_t swap_aux = 0;

	for (i = 0; i< (longitud / 2); i++){
		//Swap
		swap_aux = vector [longitud - 1 -i];
		vector[longitud - 1 -i] = vector[i];
		vector[i] = swap_aux;
	}
}

//Ejercicio 11
//Calcula la correlación entre dos vectores.
void corr (int16_t *vectorX, int16_t *vectorY, int16_t *vectorCorr, uint32_t longitud){
	//Asumo que VectorX, VectorY tienen la misma longitud
	uint32_t K = 0; //Para ver el valor en el debugging
	int32_t i = 0;
	int32_t j = 0;
	int32_t aux_corr = 0;
	K = (longitud*2)-1;
	for (i = 0; i < K; i++){								//indice de vectorCorr
		aux_corr = 0;
		for (j = 0; j < longitud; j++){ 					//indice de la sumatoria
			if (((i-j) >=0) && ((i-j)<longitud)){
				aux_corr = aux_corr + vectorX[j]*vectorY[i-j];
			}
		}
		vectorCorr[i] = aux_corr;
	}
}

//Ejercicio 11 bis, nueva implementacion para poder usar SIMD en Assembly
//Calcula la correlación entre dos vectores
void corr_bis (int16_t *vectorX, int16_t *vectorY, int16_t *vectorCorr, uint32_t longitud){
	uint32_t K = 0; //Para ver el valor en el debugging
	int32_t i = 0;
	int32_t j = 0;
	int32_t aux_corr = 0;
	K = (longitud*2)-1;
	for(i=0;i<K;i++){
		aux_corr = 0;
		for(j=0;j<longitud;j++){
			aux_corr = aux_corr + vectorX[j]*vectorY[K-1+j-i];
		}
		vectorCorr[i] = aux_corr;
	}
}



















