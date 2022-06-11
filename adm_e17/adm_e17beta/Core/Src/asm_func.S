.syntax unified
.thumb
.text

@ Simbolos exportados
.global asm_svc
.global asm_sum
@ Ejercicios >>>
.global asm_zeros
.global asm_productoEscalar32
.global asm_productoEscalar16
.global asm_productoEscalar12
.global asm_filtroVentana10
.global asm_pack32to16
.global asm_max
.global asm_downsampleM
.global asm_invertir

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void asm_svc (void)
@
.thumb_func
    asm_svc:
        svc 0
        bx lr


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   uint32_t asmSum (uint32_t firstOperand, uint32_t secondOperand)
@
@ Parametros recibidos:
@   r0: firstOperand
@   r1: secondOperand
@
@ Valor de retorno:
@   r0: resultado de la suma de firstOperand y secondOperand
@
.thumb_func
    asm_sum:
        add r0, r1  @ r0 = r0 + r1
        bx lr       @ vuelve adonde fue llamada (especificamente, si "pc"
                    @ es la direccion, en el codigo del programa, de la
                    @ instruccion "bl asm_sum" usada para saltar a
                    @ esta funcion, entonces "lr" contiene ese "pc" + 4).
                    @ el valor de retorno debe quedar en el registro r0.
                    @ En este caso, r0 es el resultado de r0 + r1.

        @ Otras alternativas para el retorno
        @ mov pc,lr
        @ bx lr
        @ push {lr} ... pop {pc}

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Ejercicios de la practica implemtentados en Assembly
@ Su version en C estan en "ejercicios.c/h"


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Ejercicio 1
@ Funcion original en "C":
@ void zeros (uint32_t * vector, uint32_t longitud){
@   for(uint32_t i = 0; i < longitud; i++){
@     vector[i]=0;
@   }
@ }
@
@ Prototipo en "C":
@   void asm_zeros (uint32_t * vector, uint32_t longitud)
@
@ Parametros recibidos:
@   r0: puntero a vector 32btis
@   r1: longitud
@
@ Valor de retorno:
@   r0: void  //Preguntar que pasa cuando es void. ¿Se pone NULL en r0 o no se toca?
@
.thumb_func
    asm_zeros:
    	MOV R3,#0				@ set R3 = 0
        STR R3,[R0],#4         	@ store 32-bit R3 to [R0], then increment R0
		SUBS R1,R1,#1			@ R1 = R1 - 1, decrement the count
		CMP R1,#0 				@ compare to 0 and set Z register
		BNE asm_zeros			@ branch if compare not zero
		BX lr					@ branch and exchange Instruction Set


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Ejercicio 2
@ Funcion original en "C":
@ void productoEscalar32 (uint32_t * vectorIn, uint32_t * vectorOut, uint32_t longitud, uint32_t escalar){
@   for(uint32_t i = 0; i < longitud; i++){
@     vectorOut[i]=(uint32_t)(vectorIn[i]*escalar);
@   }
@ }
@
@ Prototipo en "C":
@   void asm_productoEscalar32 (uint32_t * vectorIn, uint32_t * vectorOut, uint32_t longitud, uint32_t escalar)
@
@ Parametros recibidos:
@   r0: vectorIn,  puntero a vector 32btis
@   r1: vectorOut, puntero a vector 32btis
@   r2: longitud
@   r3: escalar
@
@ Valor de retorno:
@   void
@
.thumb_func
    asm_productoEscalar32:
        PUSH {R4}
        PUSH {R5}
    loop_productoEscalar32:
        LDR R4, [R0], #4             @ load 32-bit R3 from [R0], then increment R0
    	MUL R5, R4, R3
    	STR R5,[R1], #4              @ store 32-bit R3 to [R0], then increment R0
		SUBS R2,R2,#1				 @ R1 = R1 - 1, decrement the count
		CMP R2,#0 					 @ compare to 0 and set Z register
		BNE loop_productoEscalar32	 @ branch if compare not zero
		POP {R5}
		POP {R4}
		BX lr						@ branch and exchange Instruction Set


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Ejercicio 3
@ Funcion original en "C":
@ void productoEscalar16 (uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar){
@   for(uint32_t i = 0; i < longitud; i++){
@     vectorOut[i]=(uint16_t)(vectorIn[i]*escalar);
@   }
@ }
@
@ Prototipo en "C":
@   void asm_productoEscalar16 (uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar)
@
@ Parametros recibidos:
@   r0: vectorIn,  puntero a vector 16btis
@   r1: vectorOut, puntero a vector 16btis
@   r2: longitud
@   r3: escalar
@
@ Valor de retorno:
@   void
@
.thumb_func
    asm_productoEscalar16:
        PUSH {R4}
        PUSH {R5}
    loop_productoEscalar16:
        LDR R4, [R0], #2             @ load 32-bit R3 from [R0], then increment R0
    	MUL R5, R4, R3
    	STR R5,[R1], #2              @ store 32-bit R3 to [R0], then increment R0
		SUBS R2,R2,#1				 @ R1 = R1 - 1, decrement the count
		CMP R2,#0 					 @ compare to 0 and set Z register
		BNE loop_productoEscalar16	 @ branch if compare not zero
		POP {R5}
		POP {R4}
		BX lr						 @ branch and exchange Instruction Set


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Ejercicio 4
@ Funcion original en "C":
@ void productoEscalar12 (uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar){
@   for(uint32_t i = 0; i < longitud; i++){
@     vectorOut[i]=((vectorIn[i]*escalar)>0x0FFF)?0x0FFF:(vectorIn[i]*escalar);
@   }
@ }
@
@ Prototipo en "C":
@   void asm_productoEscalar12 (uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar)
@
@ Parametros recibidos:
@   r0: vectorIn,  puntero a vector 16btis
@   r1: vectorOut, puntero a vector 16btis
@   r2: longitud
@   r3: escalar
@
@ Valor de retorno:
@   void
@
.thumb_func
    asm_productoEscalar12:
        PUSH {R4}
        PUSH {R5}
        PUSH {R6}
        MOV R6, #0x0FFF
    loop_productoEscalar12:
		LDR R4, [R0], #2             @ load 32-bit R3 from [R0], then increment R0
		MUL R5, R4, R3
		CMP R5, R6
		BHI isNO
  	isYES:
  		MOV R5, #0x0FFF
		B done
	isNO:
		STR R5,[R1], #2              @ store 32-bit R3 to [R0], then increment R0
	done:
		SUBS R2,R2,#1				 @ R1 = R1 - 1, decrement the count
		CMP R2,#0 					 @ compare to 0 and set Z register
		BNE loop_productoEscalar12	 @ branch if compare not zero
		POP {R6}
		POP {R5}
		POP {R4}
		BX lr						 @ branch and exchange Instruction Set


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Ejercicio 5
@ void filtroVentana10(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitudVectorIn){
@ 	int32_t i = 0;
@ 	int32_t j = 0;
@ 	int32_t VENTANA_MOVIL = 10;
@ 	uint16_t filt_aux = 0;
@
@ 	for (i = 0; i< longitudVectorIn ; i++){
@ 		filt_aux = 0;
@ 		for (j = 0; j < 10; j++){
@ 			VENTANA_MOVIL = 10;
@ 			if ((i-j)>= 0){  //Para los primeros 10 valores del vectorIn que no tiene con que filtrar.
@ 				filt_aux = filt_aux + vectorIn[i-j];
@ 			}else{
@ 				VENTANA_MOVIL = j;
@ 				break; //Salgo del for de la ventana
@ 			}
@ 		}
@ 		vectorOut[i] = filt_aux/VENTANA_MOVIL;
@ 	}
@ }
@
@ Prototipo en "C":
@ void asm_filtroVentana10(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitudVectorIn)
@ Parametros recibidos:
@   r0: vectorIn,  puntero a vector 16btis
@   r1: vectorOut,  puntero a vector 16btis
@   r2: longitud
@
@ Valor de retorno:
@   void
@
.thumb_func
@   r4: i
@   r5: j
@   r6: N (VENTANA_MOVIL)
@   r7: filt_aux
@   r8: aux1
@   r9: aux2
	asm_filtroVentana10:
		PUSH {R4}
		PUSH {R5}
		PUSH {R6}
		PUSH {R7}
		PUSH {R8}
		PUSH {R9}
		MOV R4, #0
		MOV R5, #0
		@   MOV R6, #10				@ nhf
		@   MOV R7, #0				@ nhf
	loop_filtroVentana10_vector:
		MOV R7, #0
	loop_filtroVentana10_ventana:
		MOV R6, #10
		SUBS R8, R4, R5
		BLT	loop_filtroVentana10_ventana_else
		LDRH R9, [R0,R8, LSL 1]
		ADD R7, R9
		B loop_filtroVentana10_ventana_else_end
	//Ya no se usan mas R8 y R9, quedan libres
	loop_filtroVentana10_ventana_else:
		MOV R6, R5
		B end_loop_filtroVentana10_ventana
	loop_filtroVentana10_ventana_else_end:
		ADD R5,#1					@ R5 = R5 + 1, increment the count j
		MOV R9,#10
		CMP R5,R9					@
		BNE loop_filtroVentana10_ventana		@ branch if compare not equal
	end_loop_filtroVentana10_ventana:
		MOV R5,#0
		UDIV R8, R7, R6
		STRH R8, [R1,R4, LSL 1]
		ADD R4,#1					@ R4 = R4 + 1, increment the count
		CMP R4,R2					@
		BNE loop_filtroVentana10_vector		@ branch if compare not equal
	done_filtroVentana10:
		POP {R9}
		POP {R8}
		POP {R7}
		POP {R6}
		POP {R5}
		POP {R4}
	    BX LR


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Ejercicio 6
@ void pack32to16 (int32_t * vectorIn, int16_t *vectorOut, uint32_t longitud){
@ 	uint32_t i = 0;
@
@ 	for (i = 0; i< longitud ; i++){
@ 		vectorOut[i]= (int16_t)(vectorIn[i]>>16);
@ 	}
@ }
@
@ Prototipo en "C":
@   void asm_pack32to16 (int32_t * vectorIn, int16_t *vectorOut, uint32_t longitud);
@ Parametros recibidos:
@   r0: vectorIn,  puntero a vector 32btis
@   r1: vectorOut, puntero a vector 16btis
@   r2: longitud
@
@ Valor de retorno:
@   void
@
.thumb_func
	asm_pack32to16:
		ADD R0, #2
	    LDRH R3, [R0], #2			@ R3 =  (guardo parte alta de vectorIn)
	    STRH R3, [R1], #2     		@ (cargo lo guardado en vectorOut)
		SUBS R2,R2,#1				@ R1 = R1 - 1, decrement the count
		CMP R2,#0					@ compare to 0 and set Z register
		BNE asm_pack32to16			@ branch if compare not zero
	    BX LR


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Ejercicio 7
@ int32_t max (int32_t * vectorIn, uint32_t longitud){
@ 	uint32_t i = 0;
@ 	uint16_t max_aux = 0;
@ 	uint16_t max_pos = 0;
@
@ 	for (i = 0; i< longitud ; i++){
@ 		//Max
@ 		if( max_aux < vectorIn[i] ){
@ 			max_aux = vectorIn[i];
@ 			max_pos = i;
@ 		}
@ 	}
@ 	return max_pos;
@ }
@
@ Prototipo en "C":
@   int32_t asm_max (int32_t * vectorIn, uint32_t longitud);
@ Parametros recibidos:
@   r0: vectorIn,  puntero a vector 32btis
@   r1: longitud
@
@ Valor de retorno:
@   r0: indice del maximo encontrado
@
.thumb_func
	asm_max:
		PUSH {R4}
		PUSH {R5}
		MOV R2, #0					@ R2 max_aux
		MOV R3, #0   				@ R3 max_pos
		MOV R5, R1					@ R5 longitud
	loop_asm_max:
		@compare
	    LDR R4, [R0], #4			@ R4 max_pos
		CMP R2, R4
		BGT done_comp				@ branch, GT signed >
		MOV R2, R4
		MOV	R3, R1
	done_comp:
		SUBS R1,R1,#1				@ R1 = R1 - 1, decrement the count
		CMP R1,#0					@ compare to 0 and set Z register
		BNE loop_asm_max			@ branch if compare not zero
	done_max:
	    SUB R5,R5,R3
		MOV R0, R5
		POP {R5}
		POP {R4}
	    BX LR


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Ejercicio 8
@ void downsampleM (int32_t * vectorIn, int32_t * vectorOut, uint32_t longitud, uint32_t N){
@ 	uint32_t i = 0;
@ 	uint32_t j = 0;
@
@ 	for (i = 0; i< longitud ; i++){
@ 		//Decime
@ 		if( !(i%N) ){
@ 			vectorOut[j] = vectorIn[i];
@ 			j++;
@ 		}
@ 	}
@ }
@
@ Prototipo en "C":
@   void asm_downsampleM (int32_t * vectorIn, int32_t * vectorOut, uint32_t longitud, uint32_t N);
@ Parametros recibidos:
@   r0: vectorIn,  puntero a vector 32btis
@   r1: vectorOut,  puntero a vector 32btis
@   r2: longitud
@   r3: N
@
@ Valor de retorno:
@   void
@
.thumb_func
@   r4: i
@   r5: j
@   r6: aux1
@   r7: aux2
	asm_downsampleM:
		CMP R3, #0
	    BEQ done_downsampleM		@ !division by zero
		PUSH {R4}
		PUSH {R5}
		PUSH {R6}
		PUSH {R7}
		MOV R4, #0
		MOV R5, #0
	loop_downsampleM:
    	UDIV R6,R4,R3				@ residuo
    	MUL R7,R6,R3				@ residuo
    	SUB R7,R4,R7				@ residuo
    	CMP R7, #0					@ residuo == 0
    	BNE res_distinto
		//r6 y r7 ya no tienen importancia
		//se pueden reutilizar
		LDR R6, [R0,R4, LSL 2]
		STR R6, [R1,R5, LSL 2]
		ADD R5, #1
	res_distinto:
		ADD R4,#1					@ R4 = R4 + 1, increment the count
		CMP R4,R2					@
		BNE loop_downsampleM		@ branch if compare not equal
	done_downsampleM:
		POP {R7}
		POP {R6}
		POP {R5}
		POP {R4}
	    BX LR


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Ejercicio 9
@ void invertir (uint16_t * vector, uint32_t longitud){
@ 	uint32_t i = 0;
@ 	uint16_t swap_aux = 0;
@
@ 	for (i = 0; i< (longitud / 2); i++){
@ 		//Swap
@ 		swap_aux = vector [longitud - 1 -i];
@ 		vector[longitud - 1 -i] = vector[i];
@ 		vector[i] = swap_aux;
@ 	}
@ }
@
@ Prototipo en "C":
@   void asm_invertir (uint16_t * vector, uint32_t longitud);
@ Parametros recibidos:
@   r0: vectorIn,  puntero a vector 16btis
@   r1: longitud
@
@ Valor de retorno:
@   void
@
.thumb_func
@   r2: i
@   r3: swap_aux
@   r4: longitud / 2
@   r5: longitud - 1
@   r6: aux
@   r7: longitud - 1 - i
	asm_invertir:
		PUSH {R4}
		PUSH {R5}
		PUSH {R6}
		PUSH {R7}
		MOV R2,#0
		MOV R4, R1, LSR 1
		CMP R4,#0					@ compare to 0 and set Z register
		BEQ done_invertir			@ branch if compare zero
		MOV R5, R1
		SUB R5, #1
	loop_invertir:
	    SUB  R7, R5, R2
	    LDRH R3, [R0, R7, LSL 1]	@ swap_aux = vector [longitud - 1 -i];
	    LDRH R6, [R0, R2, LSL 1]	@ R6 = vector [i];
		STRH R6, [R0, R7, LSL 1]	@ vector[longitud - 1 -i] = vector[i];
		STRH R3, [R0, R2, LSL 1]	@ vector[i] = swap_aux;
		ADD R2,#1					@ R2 = R2 + 1, increment the count
		CMP R2,R4					@
		BNE loop_invertir			@ branch if compare not equal
	done_invertir:
		POP {R7}
		POP {R6}
		POP {R5}
		POP {R4}
	    BX LR

