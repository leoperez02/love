#include "serial.h"
/*
GGA Time, position and fix type data.
GLL Latitude, longitude, UTC time of position fix and 
RMC Time, date, position, course and speed data
*/

extern char tiempo[10];
extern char latitud[9];
extern char longitud[10];

void proceso(char *cadena)
{
	register int i ,j,k;
	char gga[] = "$GPGGA";
	char ggl[] = "$GPGLL";
	char rmc[] = "$GPRMC";
	char *protocolo;
	
    //printf("Cadena: %s\n",cadena);
    protocolo = strtok(cadena,",");
     //printf("Protocolo: %s\n",protocolo);
			if(strcmp(gga,protocolo)==0)
			{
			  	      k=0;
					  for(j=7;j < 17;j++){
                			tiempo[k] = cadena[j];
                            k++;
            			}
                        tiempo[k]= '\0';
                        k=0;
            			for(j=18;j < 27;j++){
                			latitud[k] = cadena[j];
                			k++;
            			}
            			latitud[k] = '\0';
            			k=0;
            			for(j=30;j < 40;j++){
                			longitud[k] = cadena[j];
                			k++;
            			}
            			longitud[k] = '\0';
			}else if(strcmp(ggl,protocolo)==0)
			{
					k=0;
					  for(j=7;j < 16;j++){
                			latitud[k] = cadena[j];
                            k++;
            			}
            			latitud[k] = '\0';
            			k=0;
            			for(j=19;j < 29;j++){
                			longitud[k] = cadena[j];
                            k++;
            			}
            			longitud[k] = '\0';
            			k=0;
            			for(j=32;j < 42;j++){
                			tiempo[k] = cadena[j];
                            k++;
            			}
            			tiempo[k] = '\0';
			}else if(strcmp(rmc,protocolo)==0)
			{
					 k=0;
					  for(j=7;j < 17;j++){
                			tiempo[k] = cadena[j];
                            k++;
            			}
            			tiempo[k] = '\0';
            			k=0;
            			for(j=20;j < 30;j++){
                			latitud[k] = cadena[j];
                            k++;
            			}
            			latitud[k]= '\0';
            			k=0;
            			for(j=32;j < 42;j++){
                			longitud[k] = cadena[j];
                            k++;
            			}
            			 longitud[k] = '\0';
			}
			else
			{
				printf("Protocolo no valido\n");
			}
          printf("Protocolo: %s\n",protocolo);
          //printf("Latitud: %s\n",latitud);
          //printf("Tiempo: %s\n",tiempo);
          //printf("Longitud: %s\n",longitud);
       
}
/*
int main ()
{
 	char c[100];
	fgets(c,100, stdin);
         proceso(c);
	//printf("%s",c);
	return 0;
}
*/
