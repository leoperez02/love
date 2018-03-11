#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "libvector_fun.h"

#define N 64

int main(void)
{
	pthread_t tid_mayor, tid_menor;
	int *mayor, *menor;
	vector* datos;
	
	datos = init_vector(N);
	llena_vector(datos);
	print_vector(datos);
	
	/* Crear hilo con atributos default */
	pthread_create(&tid_mayor, NULL, get_mayor, 	(void*)datos);
	pthread_create(&tid_menor, NULL, get_menor, 	(void*)datos);
	

	/* Recibir los datos luegode que hilo termina */
	pthread_join(tid_mayor,  (void**)&mayor);
	pthread_join(tid_menor, (void**)&menor);
	
	printf("La mayor es %d\n", *mayor);
	printf("La menor es %d\n", *menor);
	
	
	return 0;
}
