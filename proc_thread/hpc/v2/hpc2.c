#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libarray_fun.h"

#define NUM_PROC 4
#define N 64
#define ROWS 8

/* dECLARAR ARREGLO DE DATOS DE MANERA GLOBAL*/
int *A, *B, *C;

void proceso_hijo(int,int*);
void proceso_padre(int [NUM_PROC][2]);

int main(void)
{
	pid_t pid;
	register int i;
	
	/* Descriptor de archivo para la tuberia */
	int pipefd[NUM_PROC][2];
	int edo_pipe;
	
	A = init_array(N);
	B = init_array(N);
	C = init_array(N);
	
	llena_array(A,N,4096);
	printf("Arreglo A: \n");
	print_array(A,N,ROWS);
	
	llena_array(B,N,4096);
	printf("Arreglo B: \n");
	print_array(B,N,ROWS);
		
	/* Creando procesos para cada tarea */
	for(i = 0 ; i < NUM_PROC ; i++)
	{
		/* Creación de tubería*/
		edo_pipe = pipe( &pipefd[i][0] );
		if(edo_pipe == -1)
		{
			perror("ERROR EN PIPE");
			exit(EXIT_FAILURE);
		}

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
				proceso_hijo(i,pipefd[i]);
			}
			/* El valor de retorno es el PID(!=0) en el proceso padre */
		}
	}
	/* El proceso padre continua la ejecucion */
	proceso_padre(pipefd);
	
	printf("Arreglo C: \n");
	print_array(C,N,ROWS);
	
	free(A);
	free(B);
	free(C);
	return 0;
}

void proceso_hijo(int id,int* pipefd)
{
	register int i;
	int ini_bloque, tam_bloque,fin_bloque;
	/*printf("Proceso hijo  #%d, con PID = %d\n",id,getpid());*/
	/* Evaluar ID  para asginar tarea a cada proceso hijo */
	
	/* Cerrar derscriptor 0 por seguridad*/
	close(pipefd[0]);
		
	/* Calculo de los bloques */
	tam_bloque = N / NUM_PROC;
	ini_bloque = id * tam_bloque;
	fin_bloque = ini_bloque + tam_bloque ;

	/* MULTIPLICAR BLOQUES*/
	for(i = ini_bloque ; i < fin_bloque ; i++)
	{
		C[i] = A[i] * B[i] ;
	}
	/* Escvritura a través de la tubería */
	write(pipefd[1],&C[ini_bloque],sizeof(int)*tam_bloque);
	/*write(pipefd[1],C+ini_bloque,sizeof(int)*tamb_bloque);*/
	close(pipefd[1]);
	exit(id);
}

void proceso_padre(int pipefd[NUM_PROC][2])
{
	register int i;
	int proc_ID;
	int ini_bloque, tam_bloque;
	pid_t pid;
	
	tam_bloque = N / NUM_PROC;
	
	printf("Proceso padre con PID %d \n",getpid());
	
	/* Esperar a que los procesos hijos terminen y recibir resultados */
	for(i = 0 ; i < NUM_PROC ; i++)
	{
		/* Cerrar descriptor 1*/
		close(pipefd[i][1]);
	
		pid = wait(&proc_ID);
		proc_ID = proc_ID>>8;
		
		/* Calculo de los bloques */
		ini_bloque = proc_ID * tam_bloque;
	
		/* Leer segmentos del array  */		
		read (pipefd[proc_ID][0], C+ini_bloque, sizeof(int)*tam_bloque);
		printf("Proceso #%d con PID %d -> ",proc_ID,pid);
		
		close( pipefd[proc_ID][0] );
	}
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

