#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 64
int* init_array(int);
void llena_array(int*,int);
void print_array(int*,int);

void* get_mayor(void*);
void* get_menor(void*);

int get_promedio(int*,int);
int* sort_array(int*,int);
