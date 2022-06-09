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
