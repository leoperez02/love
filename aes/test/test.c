/*
* file: test.c
*/
#include <stdio.h>
#include <aes_aux_functions.h>
/* Se realiza el producto de los bytes {b1} * {b2} 
La multiplicacion de bytes no es conmutativa */
int main(void)
{
	byte b1,b2,producto ;
	printf("TEST DE FUNCIONES AUXILIARES DE AES\n");
	b1 = 0x57 ;
	b2 = 0x13 ;
	producto = multiplica(b1,b2);
	printf("Multiplicacion de {%x}*{%x} = %x\n",b1,b2,producto);
	b1 = 0x22 ;
	b2 = 0x15 ;
	producto = multiplica(b1,b2);
	printf("Multiplicacion de {%x}*{%x} = %x\n",b1,b2,producto);
	return 0;
}