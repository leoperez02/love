#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "imagen.h"
#include "img_fun.h"

#define DIMASK 3
#define NUM_H 4

void *filtroPB(void *arg);

/**
 * variables globales
 */ 
unsigned char *imagenO;
unsigned char *imagenP;
uint32_t width;
uint32_t heigth;

int main(void)
{
	bmpInfoHeader info;
	unsigned char *imagenRGB,*imagenGray,*imagenAux;
	imagenRGB = abrirBMP("huella1.bmp",&info);
	displayInfo(&info);
    imagenGray = RGBToGray(imagenRGB,info.width,info.height);

	imagenAux = reservarMemoria(info.width,info.height);
	
	imagenO = imagenGray;
	imagenP = imagenAux;
	width = info.width;
	heigth = info.height;
	
	
	/**
	 * Inicio de la sección del procesamiento en paralelo
	 */
	/* Declaraciones */
	register int nh;
	int nhs[NUM_H];
	/* La variable que regresa el hilo es apuntador doble */
	int* hilo_res; 
	
	/* Arreglo de  identificadores de hilos */
	pthread_t tids[NUM_H];
	/* END Declaraciones */
		
	for(nh = 0 ; nh < NUM_H ; nh++)
	{
		/* Crear hilo con atributos default */
		/* Se pasa como argumento de la funcion el ID de hilo*/
		nhs[nh] = nh;
		pthread_create(&tids[nh], NULL, filtroPB, 	(void*)&nhs[nh]);
	}

	for(nh = 0 ; nh < NUM_H ; nh++)
	{
		/* Recibir los datos luegode que hilo termina */
		pthread_join(tids[nh],  (void**)&hilo_res);
		printf("Resultado del hilo es ID = %d\n", *hilo_res);
	}

	
	/**
	 * FIN de la sección del procesamiento en paralelo
	 */
	 
	//brilloImagen(imagenAux,info.width,info.height);
	GrayToRGB(imagenRGB,imagenAux,info.width,info.height);
    guardarBMP("huellaFPB.bmp",&info,imagenRGB);

	free(imagenRGB);
    free(imagenGray);
	free(imagenP);
	
	return 0;
}

void* filtroPB(void *arg)
{
	/**
	 * Definir bloques horizontales segun el numero de hilo 
	 */
	int nn,inicioB,finB;
	nn = *(int*)arg;
	switch (nn)
	{
		case 0:
			inicioB = 0 ;
			finB = heigth/4 + 1 ;
		break;
		
		case 1:
			inicioB = heigth/4 - 1 ;
			finB = heigth/2 + 1 ;
		break;
		
		case 2:
			inicioB = heigth/2 - 1;
			finB = 3*heigth/4 + 1 ;
		break;
		
		case 3:
			inicioB = 3*heigth/4 - 1 ;
			finB = heigth - DIMASK ;
		break;
		
		default:
			perror("ID DE HILO NO VALIDO\n");
			pthread_exit( arg );
		break;
	}	
	
	register int x,y,ym,xm;
	int conv,indiceI,indiceM;
	unsigned char mascara[DIMASK*DIMASK] = {
		1,2,1,
		2,4,2,
		1,2,1};
    for(y = inicioB ; y < finB ; y++)
    {
		for(x = 0 ; x < width-DIMASK ; x++)
		{ // para movernos por toda la imagen
                      conv = 0 ;
		    for(ym = y ; ym < y+DIMASK ;ym++)
		    {
				for(xm = x ; xm < x+DIMASK; xm++)
				{
					indiceI = ym * width + xm;
					indiceM = (ym-y)* DIMASK+ (xm-x);
					conv += (imagenO[indiceI] * mascara[indiceM]) ;
			    }
			  conv /= 9;
			  indiceI = (y+1) * width + (x+1) ;
			  imagenP[indiceI] = (conv > 255 ) ? 255 : conv;
		    }	
		}
	}
	pthread_exit( arg );
}
