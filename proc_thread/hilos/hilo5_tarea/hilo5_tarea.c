#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "libarray_fun2.h"
#include "libmerge_sort.h"

#define NUM_H 4
#define N 64

void* funcion_hilo(void* arg);

/* ARREGLO GLOBAL DE DATOS */
int* datos;

/* Resultados esperados */
int mayor, menor, promedio, *datos_ordenados;

/* Objeto mutex para definir seccion critica en hilos */
pthread_mutex_t bloqueo;

int main(void)
{
	register int nh;
	int nhs[NUM_H];
	
	/* La variable que regresa el hilo es apuntador doble */
	int* hilo_res;
	 
	/* Arreglo de identificadores de hilos */
	pthread_t tids[NUM_H];
	
	/* Inicializacion del arreglo */
	datos = init_array(N);
	llena_array(datos, N, 4096);

	/* Inicializacion del mutex*/
	pthread_mutex_init( &bloqueo, NULL);

	for(nh = 0 ; nh < NUM_H ; nh++)
	{
		/* Crear hilo con atributos default */
		/* Se pasa como argumento de la funcion el ID de hilo*/
		nhs[nh] = nh;
		pthread_create(&tids[nh], NULL, funcion_hilo, (void*)&nhs[nh]);
	}

	for(nh = 0 ; nh < NUM_H ; nh++)
	{
		/* Recibir los datos luego de que el hilo termina */
		pthread_join(tids[nh],  (void**)&hilo_res);
		printf("Hilo terminado con ID = %d\n", *hilo_res);
	}

	/* Desplegar resultados */
	printf("El numero MAYOR es %d\n",mayor);
	printf("El numero MENOR es %d\n",menor);
	printf("El PROMEDIO es %d\n",promedio);
	printf("Arreglo ordenado:");
	print_array(datos_ordenados,  N, 8);

	/* Librear memoria del mutex*/
	pthread_mutex_destroy( &bloqueo );
	
	/* Liberar memoria del arreglo*/
	free(datos);

	return 0;
}

void* funcion_hilo(void* arg)
{
	int id_hilo ;
	id_hilo = *(int*)arg ;

	printf("Hilo en ejecucion con ID = %d\n",id_hilo);
	
	/* Evaluar ID del hilo para asignar tareas*/
	switch (id_hilo)
	{
		case MAYOR:
			/* Inicio de la seccion critica */
			pthread_mutex_lock( &bloqueo );
			mayor = get_mayor(datos,N) ;
			/* Fin de la seccion critica del hilo */
			pthread_mutex_unlock( &bloqueo );
		break;
			
		case MENOR:
			/* Inicio de la seccion critica */
			pthread_mutex_lock( &bloqueo );
			menor = get_menor(datos,N);
			/* Fin de la seccion critica del hilo */
			pthread_mutex_unlock( &bloqueo );
		break;
		
		case PROMEDIO:
			/* Inicio de la seccion critica */
			pthread_mutex_lock( &bloqueo );
			promedio = get_promedio(datos,N);
			/* Fin de la seccion critica del hilo */
			pthread_mutex_unlock( &bloqueo );
		break;
		
		case ORDENA:
			datos_ordenados = merge_sort(datos,N);
		break;
		
		default:
			exit(EXIT_FAILURE);
		break;
	}
	pthread_exit( arg );
}
