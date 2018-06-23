/*
 * filtro_gauss.c
 * 
 * Copyright 2018 Lain Iwakura <lain@pavilion>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include "imagen_fun.h"

void get_bordes (char *fileO, char *fileD)
{
	bmpInfoHeader info;
	unsigned char *imagenRGB,*imagenGray,*imagenAux;
	imagenRGB = abrirBMP(fileO,&info);
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
		syslog(LOG_INFO,"Resultado del hilo es ID = %d\n", *hilo_res);
	}

	
	/**
	 * FIN de la sección del procesamiento en paralelo
	 */
	 
	//brilloImagen(imagenAux,info.width,info.height);
	GrayToRGB(imagenRGB,imagenAux,info.width,info.height);
    guardarBMP(fileD,&info,imagenRGB);

	free(imagenRGB);
    free(imagenGray);
	free(imagenP);	
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
			syslog(LOG_ERR,"ID DE HILO NO VALIDO\n");
			pthread_exit( arg );
		break;
	}	
	
	register int x,y,ym,xm;
	register int GX , GY, modulo;
	int conv,indiceI,indiceM;
	short maskx[DIMASK*DIMASK] = {
		-1, 0,  1,
		-2, 0,  2,
		-1, 0,  1 };
		
	short masky[DIMASK*DIMASK] = {
		-1, -2, -1,
		 0,  0,  0,
		 1,  2,  1 };
    for(y = inicioB ; y < finB ; y++)
    {
		for(x = 0 ; x < width-DIMASK ; x++)
		{ // para movernos por toda la imagen
            
            modulo = 0;
			GX = 0;
			GY = 0;
			
		    for(ym = y ; ym < y+DIMASK ;ym++)
		    {
				for(xm = x ; xm < x+DIMASK; xm++)
				{
					indiceI = ym * width + xm;
					indiceM = (ym-y)* DIMASK+ (xm-x);
//					conv += (imagenO[indiceI] * mascara[indiceM]) ;
					GX += (imagenO[indiceI] * maskx[indiceM]) >>2 ;
					GY += (imagenO[indiceI] * masky[indiceM]) >>2 ;
			    }
				//conv /= 9;
				indiceI = (y+1) * width + (x+1) ;
				modulo = sqrt(GX*GX+GY*GY);
				imagenP[indiceI] = (modulo > 255 ) ? 255 : modulo;
		    }	
		}
	}
	pthread_exit( arg );
}
