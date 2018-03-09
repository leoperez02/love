/**
 * file: array_fun.h
 * brief: funciones auxiliares para trabajar con arreglos 
 */
 
#include "array_fun.h"
#include "merge_sort.h"

int* init_array(int n)
{
	int* mem;
	mem = (int*)malloc(sizeof(int) * n);
	if(!mem)
    {
		perror("Error al asignar memoria\n");
		exit(EXIT_FAILURE);
    }
	return mem;
}

void llena_array(int* array, int n)
{
	register int i;
	for(i = 0 ; i < n ; i++)
	{
		array[i] = rand() % 4096 ;
	}
}

void print_array(int* array,int n)
{
	register int i;
	for(i = 0 ; i < n ; i++)
	{
		if (i % 16 == 0)
		{
			printf("\n");
		}
		printf("%4d ",array[i]);
	}
	printf("\n");
}

void* get_mayor(void* arg)
{
	register int i;
	static int mayor;
	int* datos;
	datos = (int*)arg;
	mayor = datos[0];
	for(i = 1 ; i < N ; i++)
	{
		if(datos[i] > mayor)
		{
			mayor = datos[i];
		}
	}
	pthread_exit( (void*) &mayor);
}

void* get_menor(void* arg)
{
	register int i;
	static int menor;
	int* datos;
	datos = (int*) arg;
	menor = datos[0];
	for(i = 1 ; i < N ; i++)
	{
		if(datos[i] < menor)
		{
			menor = datos[i];
		}
	}
	pthread_exit( (void*) &menor);
}

int get_promedio(int* datos,int n)
{
	register int i;
	int promedio;
	promedio = 0;
	for(i = 0 ; i < n ; i++)
	{
		promedio += datos[i];
	}
	promedio=promedio>>6;
	return promedio;
}

int* sort_array(int* array,int n)
{
	return merge_sort(array, n);
}
