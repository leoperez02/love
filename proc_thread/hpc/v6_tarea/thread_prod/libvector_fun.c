/**
 * file: array_fun.h
 * brief: funciones auxiliares para trabajar con estructuras vectores
 * La funciones estan orintadas a trabajar con hilos 
 */

#include "libvector_fun.h"

/*
* init_vector(): reserva memoria para la estructura vector
* 
*/
vector* init_vector(int n)
{
	/* Reserva memoria para la estructura */
	vector* ptr_vector;
	ptr_vector = (vector*)malloc(sizeof(vector));
	if(!ptr_vector)
    {
		perror("Error al asignar memoria para la estructura\n");
		exit(EXIT_FAILURE);
    }
    /* Asginando la longitud del arreglo */
    (*ptr_vector).size = n;
    /* Reservado memoria para el arreglo */
    (*ptr_vector).array = (int*)malloc(sizeof(int)*n);
    if(! (*ptr_vector).array)
    {
		perror("Error al asignar memoria para el arreglo\n");
		exit(EXIT_FAILURE);
    }
	return ptr_vector;
}
/*
 * 
 * name: llena_vector
 * @param vector
 * @return void
 * 
 */

void llena_vector(vector* vec, int max)
{
	register int i;
	srand(getpid());
	for(i = 0 ; i < (*vec).size ; i++)
	{
		(*vec).array[i] = rand() % max ;
	}
}

void print_vector(vector* vec, int rows)
{
	register int i;
	for(i = 0 ; i < (*vec).size ; i++)
	{
		if (i % rows == 0)
		{
			printf("\n");
		}
		printf("%4d ",(*vec).array[i]);
	}
	printf("\n");
}

void* get_mayor(void* arg)
{
	register int i;
	static int mayor;
	vector* vec;
	vec = (vector*) arg;
	mayor = (*vec).array[0];
	for(i = 1 ; i < (*vec).size ; i++)
	{
		if((*vec).array[i] > mayor)
		{
			mayor = (*vec).array[i];
		}
	}
	pthread_exit( (void*) &mayor);
}

void* get_menor(void* arg)
{
	register int i;
	static int menor;
	vector* vec;
	vec = (vector*) arg;
	menor = (*vec).array[0];
	for(i = 1 ; i < (*vec).size ; i++)
	{
		if((*vec).array[i] < menor)
		{
			menor = (*vec).array[i];
		}
	}
	pthread_exit( (void*) &menor);
}

/*
 * 
 * name: get_promedio
 * @param arg
 * @return void
 * 
 * La funcion obtiene el promedio del vector de datos enteros
 * NOTA: el promedio se calcula usando un rigth shift de 6 bits
 * 		por lo que solo funciona cuando el vector tiene 64 elementos
 */
void* get_promedio(void* arg)
{
	register int i;
	static int promedio;
	vector* vec;
	vec = (vector*) arg;
	promedio = 0;
	for(i = 0 ; i < (*vec).size ; i++)
	{
		promedio += (*vec).array[i];
	}
	promedio=promedio>>6;
	pthread_exit( (void*) &promedio);
}

void* sort_vector(void* arg)
{
	static vector* vec;
	vec = (vector*) arg;
	(*vec).array = merge_sort((*vec).array, (*vec).size);
	pthread_exit( (void*) vec);
}

void free_vector(vector* vec)
{	
    /* Liberar memoria del arreglo */
    free((*vec).array);
    /* Liberar memoria de la estructura */
	free(vec);
	vec = NULL;
}
