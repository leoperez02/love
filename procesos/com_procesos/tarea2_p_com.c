/*
 * file: tarea2_p_com.c
 * brief: este programa crea un arreglo de N elementos y lo llena con 
 * valores aleatorios entre 0 y 4096 . Obtiene el elemento mayor,
 * el menor, el promedio y ordena los elementos creando un proceso para
 * cada tarea. Al final cada proceso regresa el resultado al proceso 
 * padre a través de tuberías 
 * */
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "array_fun.h"

#define N 64
#define NUM_PROC 4

void proceso_hijo(int,int*,int,int*);
void proceso_padre(int*);

int main(void)
{
	pid_t pid;
	register int i;
	int* datos;
	/* Descriptor de archivo para la tuberia */
	int pipefd[2];
	int edo_pipe;
	
	datos = init_array(N);
	llena_array(datos,N);
	printf("Arreglo original: \n");
	print_array(datos,N);
	
	/* Creación de tubería*/
	edo_pipe = pipe(pipefd);
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
				proceso_hijo(i,datos,N,pipefd);
			}
			/* El valor de retorno es el PID(!=0) en el proceso padre */
		}
	}
	/* El proceso padre continua la ejecucion */
	proceso_padre(pipefd);
	
	free(datos);
	
	return 0;
}

void proceso_hijo(int id,int* datos,int n,int* pipefd)
{
	int var;
	/*printf("Proceso hijo  #%d, con PID = %d\n",id,getpid());*/
	/* Evaluar ID  para asginar tarea a cada proceso hijo */
	
	/* Cerrar derscriptor 0 por seguridad*/
	close(pipefd[0]);
	
	switch (id)
	{
		case 0: /* Buscar el mayor del arreglo */
			var = get_mayor(datos,n);
			/*printf("Mayor = %d\n",var);*/
			/* Escvritura a través de la tubería */
			write(pipefd[1],&var,sizeof(int));
			close(pipefd[1]);
			exit(id);
			break;
		
		case 1: /* Buscar el menor del arreglo */
			var = get_menor(datos,n);
			/*printf("Menor = %d\n",var);*/
			/* Escritura a través de la tubería */
			write(pipefd[1],&var,sizeof(int));
			close(pipefd[1]);
			exit(id);
			break;
		
		case 2: /* Obtiene el promedio del arreglo */
			var = get_promedio(datos,n);
			/*printf("Promedio = %d\n",var);*/
			/* Escritura a través de la tubería */
			write(pipefd[1],&var,sizeof(int));
			close(pipefd[1]);
			exit(id);
			break;
		
		case 3: /* Ordena el arreglo */
			/* Escritura a través de la tubería */
			write(pipefd[1],sort_array(datos,n),sizeof(int)*N);
			close(pipefd[1]);
			exit(id);
			break;
		
		default:
			exit(EXIT_FAILURE);
			break;
	}
}

void proceso_padre(int* pipefd)
{
	register int i;
	int res,proc_ID;
	int* array;
	pid_t pid;
	array=init_array(N);
	printf("Proceso padre con PID %d \n",getpid());
	
	/* Cerrar descriptor 1*/
	close(pipefd[1]);
	
	/* Esperar a que los procesos hijos terminen y recibir resultados */
	for(i = 0 ; i < NUM_PROC ; i++)
	{
		pid = wait(&proc_ID);
		printf("Proceso #%d con PID %d -> ",proc_ID>>8,pid);
		/* Evaluar proc_ID para identificar la tarea del proceso */
		switch (proc_ID>>8)
		{
			case 0: /* Mayor */
				/* Recibiendo dato int con read */
				read (pipefd[0], &res, sizeof(int));
				printf("Mayor = %d\n",res);
				break;
				
			case 1: /* Menor */
				/* Recibiendo dato int con read */
				read (pipefd[0], &res, sizeof(int));
				printf("Menor = %d\n",res);
				break;
				
			case 2: /* Promedio */
				/* Recibiendo dato int con read */
				read (pipefd[0], &res, sizeof(int));
				printf("Promedio = %d\n",res);
				break;
				
			case 3: /* Ordenamiento */
				/* Recibiendo arreglo de int con read */
				read (pipefd[0], array, sizeof(int)*N);
				printf("Arreglo ordenado: \n");
				print_array(array,N);
				break;
				
			default:
				perror("ID DE PROCESO ERRONEO");
				exit(EXIT_FAILURE);
				break;
		}		
	}
	close(pipefd[0]);
	free(array);
}
