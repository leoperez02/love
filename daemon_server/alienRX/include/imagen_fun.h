/*
 * imagen_fun.h
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
