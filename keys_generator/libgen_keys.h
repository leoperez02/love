/*
 * libgen_keys.h
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

/**
* File: libgen_keys.h
* Autor: Leo Pérez Bravo
* Date: 11.03.2018 14:21:23 Sun May 07 14:07:30 CDT 2017
* Description: archivo de cabecera para lib_gen_keys
* 
*/

#include <stdio.h>
#include <stdlib.h>

/* DIGITS: el número de opciones 0,1,2 ... 9 */
#define DIGITS 10

/* gen_keys_rec() : función para generar claves de manera recursiva */
void gen_keys_rec(int index,char* password, int size);

/* gen_keys() : función para generar claves */
void gen_keys(int size, int first_digit);

/* SIZE: tamaño del password */
int SIZE;
