#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void isr_signal(int signal);

int main(void)
{
	if ( signal( SIGINT, isr_signal) == SIG_ERR ) 
	{
		perror("Error en señal\n");
		exit(EXIT_FAILURE);
	}
	if ( signal( SIGTERM, isr_signal) == SIG_ERR ) 
	{
		perror("Error en señal\n");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		pause();
	}
}

void isr_signal(int signal)
{
	if ( signal == SIGINT )
	{
		printf("No quiero terminar\n");
	}
	else
	{
		if ( signal == SIGTERM )
		{
			printf("Insisto en que no quiero terminar\n");
		}
	}	
}
