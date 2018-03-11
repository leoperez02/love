/*
 * main_gen_keys.c
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
* File: main_gen_keys.c
* Autor: Leo Pérez Bravo
* Date: 11.03.2018 14:21:23 Sun May 07 14:07:30 CDT 2017
* Description: 
* Este programa genera todas las combinaciones para un password númerico
* de n-dígitos y las imprime en pantalla, una por linea
*		
* This program generates all the combinations for a n-digits numeric
* password and prints one per line
*/

#include <stdio.h>
#include "libgen_keys.h"

/**
* MAIN: el tamaño del password se pasa como primer argumento.
*		Opcionalmente se puede pasar un segundo argumento para indicar con que
*		dígito empieza la clave 
*/
int main(int argc,char** argv)
{
	if(argc < 2)
	{
		perror("Falta la longitud de la clave\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		int n;
		n = atoi(argv[1]);
		if(argc < 3)
		{
			gen_keys(n,0);	
		}
		else
		{
			char first = argv[2][0];
			gen_keys(n,(int)first);
		}
	}
	
	return 0;
}
