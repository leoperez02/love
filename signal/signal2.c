#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_PROC 4

void isr_signal(int signal);
void proceso_hijo(int);
void proceso_padre(pid_t pid[NUM_PROC]);

int main(void)
{
	pid_t pid_array[NUM_PROC];
	register int np;	

	// Colocando señales a escuchar 
	if ( signal( SIGUSR1, isr_signal) == SIG_ERR ) 
	{
		perror("Error en señal\n");
		exit(EXIT_FAILURE);
	}
	
	/* Asignar cada tarea a un proceso */
	for (np = 0 ; np < NUM_PROC ; np++)
	{
			pid_array[np] = fork();
			if(pid_array[np] == -1)
			{
				perror("ERROR CREANDO PROCESOS");
				exit(EXIT_FAILURE);
			}			
			if(!pid_array[np])
			{
				/* proceso hijo */
				proceso_hijo(np);
			}
	}	
	/* Continua proceso padre*/
	proceso_padre(pid_array);

	return 0;
}
void proceso_hijo(int np)
{
	printf("Proceso hijo %d con pid %d\n",np,getpid());
	pause();
	printf("Señal recibida en el proceso hijo\n");
	exit(np);
}

void proceso_padre(pid_t pids[NUM_PROC])
{
	/* esperar a que los hijos terminen*/
	pid_t pid;
	register int np;
	int re;	
	printf("Proceso padre con pid %d\n",getpid());
	sleep(10);
	for ( np = 0 ; np < NUM_PROC ; np++)
	{
		kill( pids[np], SIGUSR1 );
	}
	for ( np = 0 ; np < NUM_PROC ; np++)
	{
		pid = wait(&re);
		printf("Proceso hijo terminado, con resultado %d y PID %d\n",np,re>>8);
	}			
}

void isr_signal(int signal)
{
	if ( signal == SIGUSR1 )
	{
		printf("Señal SIGUSR1 recibida\n");
	}
}
