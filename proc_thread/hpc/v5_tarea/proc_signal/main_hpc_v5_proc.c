#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libarray_fun.h"
#include "defs.h"
#include "archivos.h"
#include "procesamiento.h"

#define NUM_PROC 4
#define N 64
#define ROWS 8

/* dECLARAR ARREGLO DE DATOS DE MANERA GLOBAL*/
float *seno, *hamm, *prod;

void proceso_hijo(int,int*);
void proceso_padre(int [NUM_PROC][2]);

int main(void)
{
	pid_t pid;
	register int i;
	
	/* Descriptor de archivo para la tuberia */
	int pipefd[NUM_PROC][2];
	int edo_pipe;
	
	seno = init_array(MUESTRAS);
	hamm = init_array(MUESTRAS);
	prod = init_array(MUESTRAS);
	
	genera_seno(seno);
	genera_hamming(hamm);
	
	guarda_datos(seno, "seno.dat");
	guarda_datos(hamm, "hamm.dat");
		
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
	
	guarda_datos(prod, "prod.dat");
	
	free(seno);
	free(hamm);
	free(prod);
	
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
	tam_bloque = MUESTRAS / NUM_PROC;
	ini_bloque = id * tam_bloque;
	fin_bloque = ini_bloque + tam_bloque ;

	/* MULTIPLICAR BLOQUES*/
	for(i = ini_bloque ; i < fin_bloque ; i++)
	{
		prod[i] = seno[i] * hamm[i] ;
	}
	/* Escvritura a través de la tubería */
	write(pipefd[1],prod+ini_bloque,sizeof(float)*tam_bloque);
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
	
	tam_bloque = MUESTRAS / NUM_PROC;
	
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
		read (pipefd[proc_ID][0], prod+ini_bloque, sizeof(float)*tam_bloque);
		printf("Proceso #%d con PID %d\n ",proc_ID,pid);
		
		close( pipefd[proc_ID][0] );
	}
}



