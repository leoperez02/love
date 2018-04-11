#include<stdio.h>
#include<stdlib.h>
#include"imagen.h"

void rgb_to_gray(unsigned char *img, uint32_t width, uint32_t height);

int main(void)
{
	bmpInfoHeader bmpinfo;
	unsigned char *imagen;
	
	imagen = abrirBMP("hoja.bmp", &bmpinfo);
	displayInfo(&bmpinfo);

	rgb_to_gray(imagen, bmpinfo.width, bmpinfo.height );
	
	guardarBMP("hoja_gris_1.bmp",&bmpinfo,imagen);
	
	free(imagen);
	
	return 0;
}

void rgb_to_gray(unsigned char *imagen, uint32_t width, uint32_t height)
{
	register int x,y;
	int index;
	int nivel_gris;
	
	for( y = 0 ; y < height ; y++)
	{
		for( x = 0 ; x < width ; x++)
		{
			index = (y * width + x) * 3;
			nivel_gris = imagen[index] + imagen[index+1] + imagen[index+2];
			nivel_gris /= 3;
			imagen[index] = nivel_gris;
			imagen[index+1] = nivel_gris;
			imagen[index+2] = nivel_gris;
		}
	}
}
