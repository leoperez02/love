#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#define N 64
#define NUM_PROC 2

void proceso_hijo(int,int*);
void proceso_padre(void);
int *res_mem(void); 
void llenar_array(int*);
void print_array(int*);
int mayor_array(int*);
int menor_array(int*);

int main(void)
{
    pid_t pid;
	register int np;	
	int *datos;
	/*int mayor,menor;*/

	datos = res_mem();	
	llenar_array(datos);
	print_array(datos);
	
	/* Asignar cada tarea a un proceso */
	for (np = 0 ; np < NUM_PROC ; np++)
	{
			pid = fork();
			if(pid == -1)
			{
				perror("ERROR CREANDO PROCESOS");
				exit(EXIT_FAILURE);
			}			
			if(!pid)
			{
				/* proceso hijo */
				proceso_hijo(np,datos);
			}
	}	
	/* Continua proceso padre*/
	proceso_padre();
    
	free(datos);
	
	return 0;
}

void proceso_hijo(int np,int* datos)
{
    int m;
	printf("Proceso hijo %d con PID %d\n",np,getpid());
	if(np == 0)
	{
	    /* busca mayor y lo regresa */
	    m = mayor_array(datos);
    	/*printf("Mayor = %d\n",mayor);      */ 
	}
	else
	{
	    /* busca el menor y lo regresa */
	    m = menor_array(datos);
	    /*printf("Menor = %d\n",menor);  */
	}
	exit(m);
}

void proceso_padre(void)
{
	/* esperar a que los hijos terminen*/
	pid_t pid;
	register int np;
	int re;	
	printf("Proceso padre con pid %d\n",getpid());
	for ( np = 0 ; np < NUM_PROC ; np++)
	{
		pid = wait(&re);
		printf("Proceso hijo terminado, con resultado %d y PID %d\n",np,re>>8);
	}	
}

int menor_array(int* datos)
{
    register int i;
    int menor;
    menor = datos[0];
	for(i = 1 ; i < N ; i++)
	{
		if (datos[i] < menor)
		{
		    menor = datos[i];
		}
	}
	return menor;    
}

int mayor_array(int* datos)
{
    register int i;
    int mayor;
    mayor = datos[0];
	for(i = 1 ; i < N ; i++)
	{
		if (datos[i] > mayor)
		{
		    mayor = datos[i];
		}
	}
	return mayor;    
}

void llenar_array(int *datos)
{
	register int i;
	for(i = 0 ; i < N ; i++)
	{
		datos[i] = rand() % 256;
	}
}

int *res_mem(void)
{
	int *mem;
	mem = (int*)malloc(sizeof(int) * N);
	if(!mem)
	{
		perror("Error al asignar memoria\n");
		exit(EXIT_FAILURE);
	}
	return mem;
}

void print_array(int* datos)
{
  	register int i;
	for(i = 0 ; i < N ; i++)
	{
		/* printf("Dato %d = %3.d\n",i,datos[i]); */
		if(i%16==0)
		{
		    printf("\n");
		}
		printf("%3.d ",datos[i]);
	}
    printf("\n");
}

/*
* Agregar 2 rutinas para arreglar el arreglo y una para el promedio 
* Fecha de entrega: siguiente viernes git -v
*/
