#include "img_fun.h"

unsigned char *reservarMemoria(uint32_t width,uint32_t heigth)
{
	unsigned char *imagen;
    imagen = (unsigned char *) malloc (width*heigth*sizeof(unsigned char));
	if(imagen == NULL)
	{
		perror("Error al asignar memoria a la imagen en gris\n");
		exit(EXIT_FAILURE);
    }
	return imagen;
}

void brilloImagen(unsigned char *imagenGray,uint32_t width, uint32_t height)
{
	register int x,y;
	int indice,brillo;
	for( y = 0; y < height; y++ )
	{
		for( x = 0 ; x < width ; x++)
		{
			indice = (y*width + x );
			brillo = imagenGray[indice]+100;
			imagenGray[indice] = (brillo > 255 ) ? 255 : brillo;
				
		}
	}
}

void GrayToRGB(unsigned char *imagenRGB,unsigned char *imagenGray,uint32_t width, uint32_t height)
{
	register int x,y;
	int indiceRGB,indiceGray;
	unsigned char nivelGris;
	for( y = 0; y < height; y++ )
	{
		for( x = 0 ; x < width ; x++)
		{
			indiceGray = (y*width + x);
			indiceRGB = indiceGray*3;
			nivelGris = imagenGray[indiceGray];
			imagenRGB[indiceRGB] = nivelGris;
			imagenRGB[indiceRGB+1] = nivelGris;
			imagenRGB[indiceRGB+2] = nivelGris;
			
		}
	}		
}

unsigned char * RGBToGray(unsigned char *imagenRGB,uint32_t width , uint32_t height)
{
	register int x,y;
	int indiceRGB,indiceGray;
    unsigned char nivelGris;
    unsigned char *imagenGray;
	imagenGray = reservarMemoria(width,height);

	for( y = 0; y < height; y++ )
	{
		for( x = 0 ; x < width ; x++)
		{
			indiceGray = (y*width + x);
            indiceRGB = indiceGray*3;
            // nivelGris = ((imagen[indice] + imagen[indice+1] + imagen[indice+2]) / 3);
            //3 componentes de control de rgb
			//imagen[indice];//para acceder a un pixel dentro de mi imagen
			nivelGris = ((imagenRGB[indiceRGB]*11 + imagenRGB[indiceRGB+1]*59 + imagenRGB[indiceRGB+2]*30) / 100);
			imagenGray[indiceGray] = nivelGris;	
		}
	}
	return imagenGray;
}

