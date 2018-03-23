#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "libarray_fun.h"
#include "defs.h"
#include "archivos.h"
#include "procesamiento.h"

#define NUM_H 4

void* funcion_hilo(void* arg);

/* dECLARAR ARREGLO DE DATOS DE MANERA GLOBAL*/
float *seno, *hamm, *prod;

/* Objeto mutex para definir seccion critica en hilos */
pthread_mutex_t bloqueo;

int main(void)
{
   /* Declaraciones */
	register int nh;
	int nhs[NUM_H];
	int* hilo_res; /* La variable que regresa el hilo es apuntador doble */
	/* aRREGLO DE identificadores de hilos */
	pthread_t tids[NUM_H];
	/* END Declaraciones */

	seno = init_array(MUESTRAS);
	hamm = init_array(MUESTRAS);
	prod = init_array(MUESTRAS);
	
	genera_seno(seno);
	genera_hamming(hamm);
	
	guarda_datos(seno, "seno.dat");
	guarda_datos(hamm, "hamm.dat");

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

   guarda_datos(prod, "prod.dat");

   free(seno);
   free(hamm);
   free(prod);

	/* Librear memoria del mutex*/
	pthread_mutex_destroy( &bloqueo );

	return 0;
}


void* funcion_hilo(void* arg)
{
	int nn, i;
	nn = *(int*)arg;
   
   	for(i = nn ; i < MUESTRAS ; i+=NUM_H)
   	{
      prod[i] = seno[i] * hamm[i] ;
   	}
	pthread_exit( arg );
}

