#include "proc_dot_prod.h"
#include "defs.h"

int main(void)
{
	register int i;
	
	/* Vectores para realizar el producto punto A * B */
	vector *A, *B;
	
	/* Resultado escalar del producto */
	int C;
	
	/* Inicializacion de vectores */
	A = init_vector(N);
	B = init_vector(N);

	/** Llenado aleatorio de datos */
	llena_vector(A,MAX);
	llena_vector(B,MAX);
	
	printf("Vector A:");
	print_vector(A,ROWS);
	printf("Vector B:");
	print_vector(B,ROWS);
	
	/* Invocacion de funcion producto punto con procesos */
	C = dot_prod(A, B);
	printf("Producto punto A * B = %d\n",C);
	
	/* Producto punto secuencial para comprobar funcion */
	C = 0;
	for(i = 0 ; i < (*A).size ; i++)
	{
		C += (*A).array[i] * (*B).array[i] ;
	}
	printf("Producto punto A * B = %d\n",C);
	
	/** Liberar memoria */
	free_vector(A);
	free_vector(B);
	
	return 0;
}
