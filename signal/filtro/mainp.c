#include<stdio.h>
#include<stdlib.h>
#include"imagen.h"

#define DIMASK 3
 
unsigned char* rgb_to_gray(unsigned char *img, uint32_t width, uint32_t height);
void gray_to_rgb(unsigned char *imagenGray, unsigned char *imagenRGB, uint32_t width, uint32_t height);
void brilloImagen(unsigned char *imagenGray, uint32_t width, uint32_t height);
unsigned char *getMem ( uint32_t width, uint32_t height);
void filtroPB(unsigned char *imagenGray,unsigned char *imG, uint32_t width, uint32_t height);

int main(void)
{
	bmpInfoHeader bmpinfo;
	unsigned char *imagenRGB, *imagenGray, *imagenAux;
	
	imagenRGB = abrirBMP("huella1.bmp", &bmpinfo);
	displayInfo(&bmpinfo);

	imagenGray = rgb_to_gray(imagenRGB, bmpinfo.width, bmpinfo.height );
	
	imagenAux= getMem(bmpinfo.width , bmpinfo.height);
	filtroPB( imagenGray, imagenAux, bmpinfo.width, bmpinfo.height);
	//brilloI magen(imagenGray, bmpinfo.width, bmpinfo.height);
	
	
	gray_to_rgb(imagenGray,imagenRGB,bmpinfo.width, bmpinfo.height);
	
	guardarBMP("huella1B.bmp",&bmpinfo,imagenRGB);
	
	
	
	free(imagenRGB);
	free(imagenGray);
	
	return 0;
}

void brilloImagen(unsigned char *imagenGray, uint32_t width, uint32_t height)
{
			register int x,y;
	int index,indexGray;
	int nivel_gris;
	int brillo;
	
	for( y = 0 ; y < height ; y++)
	{
		for( x = 0 ; x < width ; x++)
		{
			indexGray = (y * width + x) ;
			index = indexGray * 3;
			
			brillo = imagenGray[indexGray] + 40;
			imagenGray[indexGray] = (brillo > 255)? 255: brillo;
		}
	}
}	

void gray_to_rgb(unsigned char *imagenGray, unsigned char *imagenRGB, uint32_t width, uint32_t height)
{
	register int x,y;
	int index,indexGray;
	int nivel_gris;
	
	for( y = 0 ; y < height ; y++)
	{
		for( x = 0 ; x < width ; x++)
		{
			indexGray = (y * width + x) ;
			index = indexGray * 3;
			 
			nivel_gris = imagenGray[indexGray];
			
			imagenRGB[index]   = nivel_gris;
			imagenRGB[index+1] = nivel_gris;
			imagenRGB[index+2] = nivel_gris;
			//nivel_gris /= 3;
			/*
			imagenRGB[index] = nivel_gris;
			imagenRGB[index+1] = nivel_gris;
			imagenRGB[index+2] = nivel_gris;
			* 
			* */
		}
	}
}

unsigned char* rgb_to_gray(unsigned char *imagenRGB, uint32_t width, uint32_t height)
{
	register int x,y;
	int index,indexGray;
	int nivel_gris;
	unsigned char *imagenGray;
	
	imagenGray = getMem(width, height);
	
	for( y = 0 ; y < height ; y++)
	{
		for( x = 0 ; x < width ; x++)
		{
			indexGray = (y * width + x) ;
			index = indexGray * 3;
			 
			nivel_gris =(
				11*imagenRGB[index] + 
				59*imagenRGB[index+1] + 
				60*imagenRGB[index+2]) / 100 ;
			//nivel_gris /= 3;
			/*
			imagenRGB[index] = nivel_gris;
			imagenRGB[index+1] = nivel_gris;
			imagenRGB[index+2] = nivel_gris;
			* 
			* */
			imagenGray[indexGray] = nivel_gris;
		}
	}
	return imagenGray;
}

unsigned char *getMem(uint32_t width, uint32_t height)
{
	unsigned char* img = (unsigned char*)malloc(width*height*sizeof(unsigned char));
	if( img == NULL )
	{
		perror("Error al asignar memoria");
		exit(EXIT_FAILURE);
	}
	return img;
}

void filtroPB(unsigned char *imagenGray,unsigned char *imG uint32_t width, uint32_t height)
{
	/**
	 * Investigar como se generan los coeficientes para un filtro Gaussiano
	 * */
	unsigned char mascara [DIMASK*DIMASK] = {
		1, 1, 1,
		1, 1, 1,
		1, 1, 1
	}
	
	
}
