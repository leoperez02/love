/*
* file: aes_aux_functions.c
*/
#include <aes_aux_functions.h>
/* Se realiza el producto de los bytes {b1} * {b2} 
La multiplicacion de bytes no es conmutativa */
byte multiplica(byte b1, byte b2)
{
	byte register i,j;
	/* El producto resultado de la multiplicacion se almacena en un byte */
	byte pro = 0 ;
	byte tmp = b1 ;
	/* Se recorre el byte b2 desde el LSB para obtener las posiciones 
	donde hay '1' */
	for(i = 0 ; i < NUM_BITS ; i++)
	{
		/* Por cada 1 en el byte b2 se hace un corrimiento de 'i' bits en b1 */
		if(b2 & (1 << i))	
		{	
			tmp = b1 ;
			/* el corrimiento de 'i' bits se hace uno a la vez */
			for(j = 0 ; j < i ; j++) 
			{
				/*Si el corrimiento causa overflow se hace xor con el modulo*/
				tmp = (tmp & MSB_BYTE) ? tmp << 1 ^ MODULO_MX : tmp << 1 ;
				/*printf("bit %d: temp = %x\n",i,tmp);*/
			}
			/* Los resultados de corrimientos de b1 por cada bit '1' de b2 se
			suman a traves de un XOR para dar el producto final */
			pro ^= tmp ;
		}
	}
	return pro ;
}