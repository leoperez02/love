#include "thread_dot_prod.h"

/* Vectores a multiplicar */
vector *A, *B;

/* Resultado escalar del producto punto */
int C;

/* Objeto mutex para definir seccion critica en hilos */
pthread_mutex_t bloqueo;

int dot_prod(vector *A_aux, vector *B_aux)
{
   /* Declaraciones */
	register int nh;
	int nhs[NUM_H];
	/* La variable que regresa el hilo es apuntador doble */
	int* hilo_res; 
	
	/* Arreglo de  identificadores de hilos */
	pthread_t tids[NUM_H];
	/* END Declaraciones */
	
	/** Validar que el size de A es igual al size de B */
	if( (*A_aux).size != (*B_aux).size )
	{
		perror("ERROR AL MULTPLICAR VECTORES. DIFERENTE LOGNGITUD\n");
		exit(EXIT_FAILURE);
	}
	
	/* Asignar direcciones de los vectores a las variables globales */
	A = A_aux;
	B = B_aux;

	/* Inicializacion del mutex*/
	pthread_mutex_init( &bloqueo, NULL);

	/* Inicializacion del resultado C */
	C = 0 ;
	
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

	return C;
}


void* funcion_hilo(void* arg)
{
	int nn, i, suma_parcial;
	nn = *(int*)arg;
   
	/* Multiplicar bloques y acumular suma en variable local */
	suma_parcial = 0 ;
   	for(i = nn ; i < (*A).size ; i+=NUM_H)
   	{
      suma_parcial += (*A).array[i] * (*B).array[i] ;
   	}
   	
   	/* Seccion critica del hilo */
   	pthread_mutex_lock( &bloqueo );
   	C += suma_parcial;
   	pthread_mutex_unlock( &bloqueo );
	
	pthread_exit( arg );
}
