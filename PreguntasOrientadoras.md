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
> Los “shadowed pointers”

-6- Describa los diferentes modos de privilegio y operación del Cortex M, sus relaciones y
cómo se conmuta de uno al otro. Describa un ejemplo en el que se pasa del modo
privilegiado a no privilegiado y nuevamente a privilegiado.
> Los Cortex M tiene 2 modos, privilegiado y no privilegiado. Se peude restringir accesos a espacio de memoria.

-7- ¿Qué se entiende por modelo de registros ortogonal? Dé un ejemplo
>Todos los registros son de propósito general y pueden ser llamados excepto el stack pointer, el link register y el program counter.
> Por ejemplo se puede realizar una suma entre cualquiera de los registros generales (ADD R0, R1)

-8- ¿Qué ventajas presenta el uso de instrucciones de ejecución condicional (IT)? Dé un
ejemplo
> Permite generar un código "if else" (con un máximo de 4 instrucciones de cuerpo)
> sin necesidad de usar saltos condicionales
> Ejemplo C: if (R0 > 0) {R1=1;}else{R1=0;}
> 
> CMP R0, #0
> 
> ITE GT
> 
> MOVEQ R1, #1
> 
> MOVNE R1, #0  
> 

-9- Describa brevemente las excepciones más prioritarias (reset, NMI, Hardfault).
>El reset es la excepción las alta y no puede ser enmascarada. Esta excepción ejecuta el código para inicializar el núcleo inmediatamente después del encendido.

-10- Describa las funciones principales de la pila. ¿Cómo resuelve la arquitectura el llamado
a funciones y su retorno?
> La funcion principal de la pila es guardar el contexto antes de hacer un salto y luego de reponerlo despues de regrsar. Se hace uso de PUSH y POP para guardar y recuperar los registros.

-11- Describa la secuencia de reset del microprocesador.
> El reset pone el Program Counter en la dirección 0. El micro empieza a recorrer la secuencia desde al dirección 0,  entonces cargo en el Stack Pointer la dirección. Luego carga la dirección del Handle Reset y se salta a la dirección correspondiente. 

-12- ¿Qué entiende por “core peripherals”? ¿Qué diferencia existe entre estos y el resto de
los periféricos?
>  “core peripherals”

-13- ¿Cómo se implementan las prioridades de las interrupciones? Dé un ejemplo
> Hay un vector llamado NVIC que nos permite configurar las prioridades de casi todas las interrupciones.

-14- ¿Qué es el CMSIS? ¿Qué función cumple? ¿Quién lo provee? ¿Qué ventajas aporta?
> CMSIS quiere decir Common Microcontroller Software Interface Standard
> Es un conjunto de herramientas, APIS y framework que permite la portabilidad entre cualquier Cortex sin importar el fabricante.

-15- Cuando ocurre una interrupción, asumiendo que está habilitada ¿Cómo opera el
microprocesador para atender a la subrutina correspondiente? Explique con un ejemplo
> Termina de ejecutar la instrucción, guarda el stack y salta a la interrupción, cuando esta finaliza
> vuelve a cargar el stack y regresa a la siguiente instrucción antes de la interrupción (siempre y cuando la interrupción no modifique el flujo).

-16- ¿Cómo cambia la operación de stacking al utilizar la unidad de punto flotante?
> stacking

-17- Explique las características avanzadas de atención a interrupciones: tail chaining y late
arrival.
>  tail chaining y late arrival.

-18- ¿Qué es el systick? ¿Por qué puede afirmarse que su implementación favorece la
portabilidad de los sistemas operativos embebidos?
>  Es implementado con un timer y es utilizado para independizarse de la velocidad del micro, generalmente se lo carga con 1ms y sirve para gestionar el sistema con otros timers, retardos, eventos periódicos, etc

-19- ¿Qué funciones cumple la unidad de protección de memoria (MPU)?
>  La MPU se encarga de prohibir el acceso a partes de la memoria cunado se esta en modo no privilegiado y de esta
>  manera proteger que se puedan sobrescribir datos.

-20- ¿Cuántas regiones pueden configurarse como máximo? ¿Qué ocurre en caso de haber
solapamientos de las regiones? ¿Qué ocurre con las zonas de memoria no cubiertas por las
regiones definidas?
> regiones, solapamientos de las regiones

-21- ¿Para qué se suele utilizar la excepción PendSV? ¿Cómo se relaciona su uso con el resto
de las excepciones? Dé un ejemplo
>  PendSV

-22- ¿Para qué se suele utilizar la excepción SVC? Expliquelo dentro de un marco de un sistema operativo embebido.
>  SVC

## ISA ##
-1- ¿Qué son los sufijos y para qué se los utiliza? Dé un ejemplo
>Las instrucciones pueden usar un sufijo para avisarle de actualizar las banderas, >o para generar una ejecución condicional sin que sea necearía guardar en un >registro la comparación.
>Por ejemplo en C: if(R0!=1) R1=R1+R0
>CMP R0, #1
>ADDNE R1, R1, R0 

-2- ¿Para qué se utiliza el sufijo ‘s’? Dé un ejemplo
>El sufijo ´s´ es el encargado de avisar que se requiere actualizar las banderas. 

-3- ¿Qué utilidad tiene la implementación de instrucciones de aritmética saturada? Dé un
ejemplo con operaciones con datos de 8 bits.
>Por ejemplo si se esta haciendo la suma de 2 señales, la suma no queremos que >sufra de overflow y el valor pegue la vuelta, si no que sature en el máximo valor >posible. Esto es posible con instrucciones ya preparadas con ese propósito, por >ejemplo USAR R1,8,R0

-4- Describa brevemente la interfaz entre assembler y C ¿Cómo se reciben los argumentos
de las funciones? ¿Cómo se devuelve el resultado? ¿Qué registros deben guardarse en la
pila antes de ser modificados?
> ARM usa como estándar de llamadas el ARM Architecture Procedure Call Standard (AAPCS). En este se especifica que los parámetros (máximo 4) se reciben en los >registros R0, R1, R2 y R3 directamente y el resultado se devuelve en R0. Los >registros R4-R11 y R13 deben ser guardados antes de ser modificados. R12 (IP) y >R14(LR) no son necesario ser guardados.

-5- ¿Qué es una instrucción SIMD? ¿En qué se aplican y que ventajas reporta su uso? Dé un
ejemplo.
> SIMD quiere decir "Una Instrucción de Múltiples Datos" en sus siglas en ingles.
> Teniendo en cuenta que nuestro procesador es de 32bits, permite operar 2 datos de 16bits o 4 de 8bits en una única instrucción. Principalmente se aplica a procesamiento de señales. Su ventaja es la optimización (en cuestión de velocidad) ya que carga, por ejemplo en datos de 16 bits, el doble de rápido en los registros (ya que se cargan de a dos) y se realiza la mitad de iteraciones para la misma operación si no se usara SIMD.
> 

