#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "libvector_fun.h"
#include "defs.h"

void* funcion_hilo(void* arg);
int dot_prod(vector *A_aux, vector *B_aux);
