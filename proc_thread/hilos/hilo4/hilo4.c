#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
/* #include "libvector_fun.h"*/

#define NUM_H 4
#define N 64

void* funcion_hilo(void* arg);

int contador;

typedef enum{MAYOR=0, MENOR, PROMEDIO, ORDENA}TAREAS;

/* dECLARAR ARREGLO DE DATOS DE MANERA GLOBAL*/

/* Objeto mutex para definir seccion critica en hilos */
pthread_mutex_t bloqueo;

int main(void)
{
	register int nh;
	int nhs[NUM_H];
	/* La variable que regresa el hilo es apuntador doble */
	int* hilo_res; 
	/* aRREGLO DE identificadores de hilos */
	pthread_t tids[NUM_H];
	/* Contador compartido por los hilos */
	contador = 0;

	/* Inicializacion del mutex*/
	pthread_mutex_init( &bloqueo, NULL);

	for(nh = 0 ; nh < NUM_H ; nh++)
	{
		/* Crear hilo con atributos default */
		/* Se pasa como argumento de la funcion el ID de hilo*/
		nhs[nh] = nh;
		pthread_create(&tids[nh], NULL, funcion_hilo, 	(void*)&nhs[nh]);
	}

	for(nh = 0 ; nh < NUM_H ; nh++)
	{
		/* Recibir los datos luegode que hilo termina */
		pthread_join(tids[nh],  (void**)&hilo_res);
		printf("Resultado del hilo es ID = %d\n", *hilo_res);
	}

	/* Librear memoria del mutex*/
	pthread_mutex_destroy( &bloqueo );

return 0;
}

void* funcion_hilo(void* arg)
{
	/*
	int* nh = (int*) malloc(sizeof(int));
	*/
	/* Variable para el contador manual */
	register int i;

	/*	*nh = *(int*) arg ;*/

	/* Inicializar con la cuenta minima */
	i = 0;

	/* Inicio de la seccion critica */
	pthread_mutex_lock( &bloqueo );

	contador++ ;
	printf("Hilo en ejecucion con contador en %d\n",contador);
	/* La funcion sleep no es re-entrante, no soporta interrumpciones */
	/* sleep(); */
	/* Contador */
	while( (--i) );

	printf("Hilo finalizado con contador en %d\n",contador);
	/* Fin de la seccion critica del hilo */
	pthread_mutex_unlock( &bloqueo );

	pthread_exit( arg );
}

