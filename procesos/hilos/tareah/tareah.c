/*
 * file: tareah.c
 * brief: este programa crea un arreglo de N elementos y lo llena con 
 * valores aleatorios entre 0 y 255 (8 bits). Obtiene el elemento mayor,
 * el menor, el promedio y ordena los elementos creando un hilo para cada tarea
 * */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_fun.h"

int num1=60;
int num2=40;

int main(void)
{
	pthread_t tid_mayor, tid_menor;
	int *mayor, *menor;
	array datos;
	
	datos = init_array(N);
	/*
	llena_array(datos,N);
	print_array(datos,N);
	*/
	
	/* Crear hilo con atributos default */
	/*
	pthread_create(&tid_mayor, NULL, get_mayor, 	(void*)datos);
	pthread_create(&tid_menor, NULL, get_menor, 	(void*)datos);
	*/

	/* Recibir los datos luegode que hilo termina */
	/*
	pthread_join(tid_mayor,  (void**)&mayor);
	pthread_join(tid_menor, (void**)&menor);
	
	printf("La mayor es %d\n", *mayor);
	printf("La menor es %d\n", *menor);
	*/
	return 0;
}

void* suma(void* arg)
{
	static int res;
	res = num1 + num2;
	/*return &res;*/
	/* Rregeresar valor con */
	pthread_exit( (void*) &res );
}

void* resta(void* arg)
{
	int* res;
	res = (int*)malloc(sizeof(int));
	*res = num1 - num2;
	/*return &res;*/
	/* Rregeresar valor con */
	pthread_exit( (void*) res );
}
void* multi(void* arg)
{
	static int res;
	res = num1 * num2;
	/*return &res;*/
	/* Rregeresar valor con */
	pthread_exit( (void*) &res );
}
void* divi(void* arg)
{
	int res;
	res = num1 / num2;
	/*return &res;*/
	/* Rregeresar valor con */
	pthread_exit( (void*) &res );
}
