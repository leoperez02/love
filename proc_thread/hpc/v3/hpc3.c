#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "libarray_fun.h"

#define NUM_H 4
#define N 1024

void* funcion_hilo(void* arg);

int contador;

typedef enum{MAYOR=0, MENOR, PROMEDIO, ORDENA}TAREAS;

/* dECLARAR ARREGLO DE DATOS DE MANERA GLOBAL*/
int *A, promedio;

/* Objeto mutex para definir seccion critica en hilos */
pthread_mutex_t bloqueo;

int main(void)
{
   /* Declaraciones */
	register int nh;
	int i;
	int nhs[NUM_H];
	int* hilo_res; /* La variable que regresa el hilo es apuntador doble */
	/* aRREGLO DE identificadores de hilos */
	pthread_t tids[NUM_H];
	/* END Declaraciones */
   promedio = 0;
	A = init_array(N);
	
   llena_array(A,N,4096);
   printf("Arreglo A:");
   print_array(A,N,8);
   
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

   /* Impresion del promedio */
   printf("Promedio del arreglo por hilo= %d\n",promedio/N);
   
   promedio = 0;
   for(i=0; i < N ; i++)
   {
      promedio += A[i]; 
   }
   printf("Promedio del areglo normal = %d",promedio/N);

   free(A);

	/* Librear memoria del mutex*/
	pthread_mutex_destroy( &bloqueo );

return 0;
}


void* funcion_hilo(void* arg)
{
   int nn, i;
   int suma;
   suma = 0;
   nn = *(int*)arg;
   
 
   for(i = nn ; i < N ; i+=NUM_H)
   {
      suma += A[i] ;
   }
   
   /* Inicio de la seccion critica */
	pthread_mutex_lock( &bloqueo );
   promedio += suma;
   /* Fin de la seccion critica del hilo */
	pthread_mutex_unlock( &bloqueo );
	
	pthread_exit( arg );
}

/*
 aregealo A hamming coseno
 arreglo b señal senoidal
 eliminacion de fenomeno gibs
 
 -> generar ventana hamming
 
 guardar los valores de ventana haming, señal senoidal y resultado en distintos archivos
 -> graficar con gnuplot
 v1 - hilos
 v2 - proceso
 
 512 muestras 
 
*/


/*
void* funcion_hilo(void* arg)
{
   int nn, i,ini_bloque, tan_bloque,fin_bloque;
   
   nn = *(int*)arg;
   tan_bloque = N / NUM_H;
   ini_bloque = nn * tan_bloque;
   fin_bloque = ini_bloque + tan_bloque ;
 
   for(i = ini_bloque ; i < fin_bloque ; i++)
   {
      (*C).array[i] = (*A).array[i] * (*B).array[i] ;
   }
 # link/ether d8:cb:8a:d5:7f:82 brd ff:ff:ff:ff:ff:ff
    inet 8.110.0.208/24 brd 8.110.0.255 scope glo
   
	pthread_exit( arg );
}
*/

