#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libvector_fun.h"
#include "defs.h"

void proceso_hijo(int,int*);
void proceso_padre(int [NUM_PROC][2]);
int dot_prod(vector *A, vector *B);
