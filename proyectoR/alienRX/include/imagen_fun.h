#include <pthread.h>
#include "imagen.h"
#include "img_fun.h"

#define DIMASK 3
#define NUM_H 4

void get_bordes (char *fileO, char *fileD);
void *filtroPB(void *arg);

/**
 * variables globales
 */ 
unsigned char *imagenO;
unsigned char *imagenP;
uint32_t width;
uint32_t heigth;
