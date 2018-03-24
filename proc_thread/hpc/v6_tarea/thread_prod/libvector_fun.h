#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "libmerge_sort.h"

typedef struct vector vector;

/**
 * Estructura para definir un arreglo de enteros y la longitud del 
 * arreglo 
 * */
struct vector
{
	int size;
	int* array;
};

vector* init_vector(int size);

void llena_vector(vector* vec, int max);
void print_vector(vector* vec, int rows);
void free_vector(vector* vec);

void* get_mayor(void* vec);
void* get_menor(void* vec);
void* get_promedio(void* vec);
void* sort_vector(void* vec);

/** It's smoke on my code */
