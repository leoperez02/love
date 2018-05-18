#include <stdlib.h>
#include "imagen.h"
#include <math.h>
unsigned char * RGBToGray(unsigned char *imagenRGB,uint32_t width , uint32_t height);
void GrayToRGB(unsigned char *imagenRGB,unsigned char *imagenGray,uint32_t width, uint32_t height);
void brilloImagen(unsigned char *imagenGray,uint32_t width, uint32_t height);
unsigned char *reservarMemoria(uint32_t width,uint32_t heigth);
