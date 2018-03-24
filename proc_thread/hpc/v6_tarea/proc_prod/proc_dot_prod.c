#include "proc_dot_prod.h"

/* Vectores a multiplicar */
vector *A, *B;

/* Resultado escalar del producto punto */
int C;

/*
 * 
 * name: dot_prod
 * @param
 * @return
 * 
 */
int dot_prod(vector *A_aux, vector *B_aux)
{
	pid_t pid;
	register int i;
	
	/* Descriptor de archivo para la tuberia */
	static int pipefd[NUM_PROC][2];
	int edo_pipe;
	
	/** Validar que el size de A es igual al size de B */
	if( (*A_aux).size != (*B_aux).size )
	{
		perror("ERROR AL MULTPLICAR VECTORES. DIFERENTE LOGNGITUD\n");
		exit(EXIT_FAILURE);
	}
	
	/* Asignar direcciones de los vectores a las variables globales */
	A = A_aux;
	B = B_aux;
		
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
	
	return C;
}

void proceso_hijo(int id,int* pipefd)
{
	register int i;
	int ini_bloque, tam_bloque,fin_bloque;
	/*printf("Proceso hijo  #%d, con PID = %d\n",id,getpid());*/
	
	/* Cerrar derscriptor 0 por seguridad*/
	close(pipefd[0]);
		
	/* Calculo de los bloques */
	tam_bloque = (*A).size / NUM_PROC;
	ini_bloque = id * tam_bloque;
	fin_bloque = ini_bloque + tam_bloque ;

	/* MULTIPLICAR BLOQUES Y ACUMULAR SUMA */
	C = 0 ;
	for(i = ini_bloque ; i < fin_bloque ; i++)
	{
		C += (*A).array[i] * (*B).array[i] ;
	}
	/* Escritura de la suma parcial a través de la tubería */
	write(pipefd[1],&C,sizeof(int));
	
	close(pipefd[1]);
	exit(id);
}

void proceso_padre(int pipefd[NUM_PROC][2])
{
	register int i;
	int proc_ID;
	int suma_parcial;
	pid_t pid;
	
	/*printf("Proceso padre con PID %d \n",getpid());*/
	
	/* Esperar a que los procesos hijos terminen y recibir resultados */
	C = 0;
	for(i = 0 ; i < NUM_PROC ; i++)
	{
		/* Cerrar descriptor 1*/
		close(pipefd[i][1]);
	
		pid = wait(&proc_ID);
		proc_ID = proc_ID>>8;
			
		/* Leer sumas parciales */		
		read (pipefd[proc_ID][0], &suma_parcial, sizeof(int));
		printf("Proceso #%d con PID %d\n",proc_ID,pid);
		C += suma_parcial;
		
		close( pipefd[proc_ID][0] );
	}
}
