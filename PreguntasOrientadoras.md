# Preguntas orientadoras #

## General ##
-1- Describa brevemente los diferentes perfiles de familias de
microprocesadores/microcontroladores de ARM. Explique alguna de sus diferencias
características.


> Existen tres perfiles dentro de los microcontroladores ARM (A, R y M), cada uno esta optimizado para distintas implementaciones.
> 
> 
> - A (perfil aplicación): Muy alta capacidad de procesamiento (con cache)
> 
> 
> - R (perfil RealTime): Orientado a Baja latencia y alta capacidad
> 
> 
> - M (perfil Microcontroladores): Orientado a dispositivos de uso masivo.
> 
> Se diferencian en rendimiento y funcionalidad.

## Cortex M ##


-1- Describa brevemente las diferencias entre las familias de procesadores Cortex M0, M3 y M4.
> El M0 esta optimizado para el mínimo consumo y sin necesidad de funcionalidades especiales.
> Cuando vamos subiendo en el número se le van agregando funcionalidades dentro del microcontrolador (Comunicación CAN, etc) y también se diferencian en capacidad.
> La arquitectura ARM del M0 es ARMv6-M, mientras que M3 y M4 tiene una arquitectura ARMv7
> La arquitectura de memoria del M0 es Von Neumann, en el caso del M3 y M4 es Harvard


-2-  ¿Por qué se dice que el set de instrucciones Thumb permite mayor densidad de código?
> Con el set de instrucciones Thumb2 el ensamblador toma la decisión de tomar funciones de 16bits o 32bits logrando alta densidad de código y alta eficiencia (flexible y potente además de fácil de usar).

-3- ¿Qué entiende por arquitectura load-store? ¿Qué tipo de instrucciones no posee este tipo de arquitectura?
> Las instrucciones lógicas solo se realizan entre los registros. Este tipo de arquitectura no posee
> instrucciones que operen con la memoria directamente. Primero es necesario cargar el dato y luego guardarlo. 

-4- ¿Cómo es el mapa de memoria de la familia?
> Los procesadores Cortex-M tiene una memoria de 32 bits que permiten un direccionamiento máximo de 4GB. El espacio de memoria esta unificado, lo que significa que instrucciones y datos comparten el mismo espacio de direcciones.
> Se la divide en regiones fijas:
> 
> - Code &ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp; 0x00000000 &ensp; 0x1FFFFFFF
> - SRAM &ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&nbsp; 0x20000000 &ensp; 0x3FFFFFFF
> - Peripherals &ensp;&ensp;                        0x40000000 &ensp; 0x5FFFFFFF
> - RAM &ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&nbsp;&nbsp;  0x60000000 &ensp; 0x9FFFFFFF
> - Devices &ensp;&ensp;&ensp; &ensp;&nbsp;         0xA0000000 &ensp; 0xDFFFFFFF
> - System &ensp;&ensp;&ensp;&ensp; &ensp;          0xE0000000 &ensp; 0XFFFFFFFF

-5- ¿Qué ventajas presenta el uso de los “shadowed pointers” del PSP y el MSP?


-6- Describa los diferentes modos de privilegio y operación del Cortex M, sus relaciones y
cómo se conmuta de uno al otro. Describa un ejemplo en el que se pasa del modo
privilegiado a no privilegiado y nuevamente a privilegiado.


-7- ¿Qué se entiende por modelo de registros ortogonal? Dé un ejemplo
>Todos los registros son de propósito general y pueden ser llamados excepto el stack pointer, el link register y el program counter.
> Por ejemplo se puede realizar una suma entre cualquiera de los registros generales (ADD R0, R1)

-8- ¿Qué ventajas presenta el uso de instrucciones de ejecución condicional (IT)? Dé un
ejemplo


-9- Describa brevemente las excepciones más prioritarias (reset, NMI, Hardfault).


-10- Describa las funciones principales de la pila. ¿Cómo resuelve la arquitectura el llamado
a funciones y su retorno?
> PUSH y POP << falta

-11- Describa la secuencia de reset del microprocesador.


-12- ¿Qué entiende por “core peripherals”? ¿Qué diferencia existe entre estos y el resto de
los periféricos?


-13- ¿Cómo se implementan las prioridades de las interrupciones? Dé un ejemplo


-14- ¿Qué es el CMSIS? ¿Qué función cumple? ¿Quién lo provee? ¿Qué ventajas aporta?


-15- Cuando ocurre una interrupción, asumiendo que está habilitada ¿Cómo opera el
microprocesador para atender a la subrutina correspondiente? Explique con un ejemplo


-16- ¿Cómo cambia la operación de stacking al utilizar la unidad de punto flotante?


-17- Explique las características avanzadas de atención a interrupciones: tail chaining y late
arrival.


-18- ¿Qué es el systick? ¿Por qué puede afirmarse que su implementación favorece la
portabilidad de los sistemas operativos embebidos?


-19- ¿Qué funciones cumple la unidad de protección de memoria (MPU)?


-20- ¿Cuántas regiones pueden configurarse como máximo? ¿Qué ocurre en caso de haber
solapamientos de las regiones? ¿Qué ocurre con las zonas de memoria no cubiertas por las
regiones definidas?


-21- ¿Para qué se suele utilizar la excepción PendSV? ¿Cómo se relaciona su uso con el resto
de las excepciones? Dé un ejemplo


-22- ¿Para qué se suele utilizar la excepción SVC? Expliquelo dentro de un marco de un sistema operativo embebido.


## ISA ##
-1- ¿Qué son los sufijos y para qué se los utiliza? Dé un ejemplo


-2- ¿Para qué se utiliza el sufijo ‘s’? Dé un ejemplo


-3- ¿Qué utilidad tiene la implementación de instrucciones de aritmética saturada? Dé un
ejemplo con operaciones con datos de 8 bits.


-4- Describa brevemente la interfaz entre assembler y C ¿Cómo se reciben los argumentos
de las funciones? ¿Cómo se devuelve el resultado? ¿Qué registros deben guardarse en la
pila antes de ser modificados?


-5- ¿Qué es una instrucción SIMD? ¿En qué se aplican y que ventajas reporta su uso? Dé un
ejemplo.


