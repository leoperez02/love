#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_fun.h"

#define N 64

void* suma(void*);
void* resta(void*);
void* multi(void*);
void* divi(void*);

int num1=60;
int num2=40;

int main(void)
{
	pthread_t tid_suma, tid_resta, tid_multi, tid_divi;
	int* res_suma, *res_resta, *res_multi, *res_divi;
	
	/* Crear hilo con atributos default */
	pthread_create(&tid_suma, NULL, suma, 	NULL);
	pthread_create(&tid_resta, NULL, resta, 	NULL);
	pthread_create(&tid_multi, NULL, multi, 	NULL);
	pthread_create(&tid_divi, NULL, divi, 	NULL);

	/* Recibir los datos luegode que hilo termina */
	pthread_join(tid_suma,  (void**)&res_suma);
	pthread_join(tid_resta, (void**)&res_resta);
	pthread_join(tid_multi, (void**)&res_multi);
	pthread_join(tid_divi,  (void**)&res_divi);
	
	printf("La suma es %d\n", *res_suma);
	printf("La resta es %d\n", *res_resta);
	printf("La multi es %d\n", *res_multi);
	printf("La divi es %d\n", *res_divi);
	
	
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
	static int res;
	res = num1 / num2;
	/*return &res;*/
	/* Rregeresar valor con */
	pthread_exit( (void*) &res );
}
