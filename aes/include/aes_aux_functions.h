/*
* file: aes_aux_functions.h
*/

/*#include<stdio.h>*/

/* CONSTANTES */

/* Numero de bits que conforman un byte */
#define NUM_BITS 8
/* Un '1' para representar la posicion del bit mas significativo */
#define MSB_BYTE 1<<(NUM_BITS-1)
/* Modulo m(x) = x^8 + x^4 + x^3 + x +1 de la norma para multiplicar bytes */
#define MODULO_MX 0x1B

/* ESTRUCTURAS */

/* Tipo de dato byte */
typedef unsigned char byte ;

/* PROTOTIPOS DE FUNCIONES */

/* Multiplicacion no conmutativa de bytes modulo m(x) */
byte multiplica(byte b1, byte b2) ;