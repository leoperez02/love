/*
 * file: tarea_p.c
 * brief: este programa crea un arreglo de N elementos y lo llena con 
 * valores aleatorios entre 0 y 255 (8 bits). Obtiene el elemento mayor,
 * el menor, el promedio y ordena los elementos creando un proceso para
 * cada tarea 
 * */
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "array_fun.h"

#define N 64
#define NUM_PROC 4

void proceso_hijo(int,int*,int);
void proceso_padre(void);

int main(void)
{
	pid_t pid;
	register int i;
	int* datos;
	datos = init_array(N);
	llena_array(datos,N);
	print_array(datos,N);
	
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
				proceso_hijo(i,datos,N);
			}
			/* El valor de retorno es el PID(!=0) en el proceso padre */
		}
	}
	/* El proceso padre continua la ejecucion */
	proceso_padre();
	
	free(datos);
	
	return 0;
}

void proceso_hijo(int id,int* datos,int n)
{
	int var;
	printf("Proceso hijo  #%d, con PID = %d\n",id,getpid());
	/* Evaluar ID  para asginar tarea a cada proceso hijo */
	switch (id)
	{
		case 0: /* Buscar el mayor del arreglo */
			var = get_mayor(datos,n);
			printf("Mayor = %d\n",var);
			exit(var);
			break;
		
		case 1: /* Buscar el menor del arreglo */
			var = get_menor(datos,n);
			printf("Menor = %d\n",var);
			exit(var);
			break;
		
		case 2: /* Obtiene el promedio del arreglo */
			var = get_promedio(datos,n);
			printf("Promedio = %d\n",var);
			exit(var);
			break;
		
		case 3: /* Ordena el arreglo */
			print_array(sort_array(datos,n),n);
			exit(EXIT_SUCCESS);
			break;
		
		default:
			exit(EXIT_FAILURE);
			break;
	}
}

void proceso_padre(void)
{
	register int i;
	int res;
	pid_t pid;
	printf("Proceso padre con PID %d \n",getpid());
	/* Esperar a que los procesos hijos terminen y recibir resultados */
	for(i = 0 ; i < NUM_PROC ; i++)
	{
		pid = wait(&res);
		printf("Proceso #%d con PID %d -> res = %d\n",i,pid,res>>8);
	}
}

