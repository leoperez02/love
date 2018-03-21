#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libarray_fun.h"

#define NUM_PROC 4
#define N 32
#define ROWS 8

/* dECLARAR ARREGLO DE DATOS DE MANERA GLOBAL*/
int *A, promedio;

void proceso_hijo(int,int*);
void proceso_padre(int [2]);

int main(void)
{
	pid_t pid;
	register int i;
	
	/* Descriptor de archivo para la tuberia */
	int pipefd[2];
	int edo_pipe;
	
	A = init_array(N);	
	llena_array(A,N,256);
	printf("Arreglo A: \n");
	print_array(A,N,ROWS);
	
	
	/* Creación de tubería*/
	edo_pipe = pipe( pipefd );
	if(edo_pipe == -1)
	{
		perror("ERROR EN PIPE");
		exit(EXIT_FAILURE);
	}

	/* Creando procesos para cada tarea */
	for(i = 0 ; i < NUM_PROC ; i++)
	{
		pid = fork();
		if(pid == -1)
		{
			perror("ERROR AL CREAR PROCESO\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			if(!pid) /* PID == 0 --> proceso hijo */
			{
				proceso_hijo(i,pipefd);
			}
			/* El valor de retorno es el PID(!=0) en el proceso padre */
		}
	}
	/* El proceso padre continua la ejecucion */
	proceso_padre(pipefd);
	
	printf("Promedio = %d \n",promedio);
	
	free(A);
	
	return 0;
}

void proceso_hijo(int id,int* pipefd)
{
	register int i;
	int promedio;
	/*
	int ini_bloque, tam_bloque,fin_bloque;
	*/
	/*printf("Proceso hijo  #%d, con PID = %d\n",id,getpid());*/
	/* Evaluar ID  para asginar tarea a cada proceso hijo */
	
	/* Cerrar derscriptor 0 por seguridad*/
	close(pipefd[0]);
		
	/* Calculo de los bloques */
	/*
	tam_bloque = N / NUM_PROC;
	ini_bloque = id * tam_bloque;
	fin_bloque = ini_bloque + tam_bloque ;
   */
	/* sumatoria de bloques */
	promedio = 0 ;
	for(i = id ; i < N ; i+=NUM_PROC)
	{
		promedio += A[i] ;
	}
	
	/* Escritura a través de la tubería */
	write(pipefd[1], &promedio, sizeof(int));
	/*write(pipefd[1],C+ini_bloque,sizeof(int)*tamb_bloque);*/
	close(pipefd[1]);
	exit(id);
}

void proceso_padre(int pipefd[2])
{
	register int i;
	int proc_ID;
	int suma_parcial;
	pid_t pid;
	
	printf("Proceso padre con PID %d \n",getpid());
	
	/* Cerrar descriptor 1*/
	close(pipefd[1]);

   promedio = 0 ;
	/* Esperar a que los procesos hijos terminen y recibir resultados */
	for(i = 0 ; i < NUM_PROC ; i++)
	{
	
		pid = wait(&proc_ID);
		proc_ID = proc_ID>>8;
			
		/* Leer segmentos del array  */		
		read (pipefd[0], &suma_parcial, sizeof(int));
		printf("Proceso #%d con PID %d -> ",proc_ID,pid);
		promedio += suma_parcial;
	}
	close( pipefd[0] );
   promedio /= N ;		
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
 * 
 * guardar todo en 3 archivos: señal denoidal ventana hamming y resutlado
 * 
 * declarar variables globales en main y usar en otros modulos con extern
 
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

