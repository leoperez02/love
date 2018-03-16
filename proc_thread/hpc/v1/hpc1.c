#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "libvector_fun.h"

#define NUM_H 4
#define N 64

void* funcion_hilo(void* arg);

int contador;

typedef enum{MAYOR=0, MENOR, PROMEDIO, ORDENA}TAREAS;

/* dECLARAR ARREGLO DE DATOS DE MANERA GLOBAL*/
vector *A, *B, *C;

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

	A = init_vector(N);
	B = init_vector(N);
	C = init_vector(N);

   llena_vector(A);
   llena_vector(B);
   printf("Arreglo A:");
   print_vector(A);
   printf("Aarreglo B:");
   print_vector(B);

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

   /* Impresion del producto */
   print_vector(C);

   free_vector(A);
   free_vector(B);
   free_vector(C);

	/* Librear memoria del mutex*/
	pthread_mutex_destroy( &bloqueo );

return 0;
}


void* funcion_hilo(void* arg)
{
   int nn, i;
   
   nn = *(int*)arg;
   
 
   for(i = nn ; i < N ; i+=NUM_H)
   {
      (*C).array[i] = (*A).array[i] * (*B).array[i] ;
   }
 
   
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

