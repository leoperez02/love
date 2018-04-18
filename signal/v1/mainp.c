#include <stdio.h>
#include <stdlib.h>
#include "imagen.h"

unsigned char *rgb_to_gray(unsigned char *img, uint32_t width, uint32_t height);
void gray_to_rgb(unsigned char *imagenGray, unsigned char *imagenRGB, uint32_t width, uint32_t height);
void brilloImagen(unsigned char *imagenGray, uint32_t width, uint32_t height);

int main(void)
{
	bmpInfoHeader bmpinfo;
	unsigned char *imagenRGB, *imagenGray;
	
	imagenRGB = abrirBMP("hoja.bmp", &bmpinfo);
	displayInfo(&bmpinfo);

	imagenGray = rgb_to_gray(imagenRGB, bmpinfo.width, bmpinfo.height );
	
	brilloImagen(imagenGray, bmpinfo.width, bmpinfo.height);
		
	gray_to_rgb(imagenGray,imagenRGB,bmpinfo.width, bmpinfo.height);
	
	guardarBMP("hoja_gris_1.bmp",&bmpinfo,imagenRGB);
	
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
			
			brillo = imagenGray[indexGray] + 90;
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
	
	imagenGray = (unsigned char*)malloc(width*height*sizeof(unsigned char));
	
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
