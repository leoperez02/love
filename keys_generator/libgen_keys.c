/*
 * libgen_keys.c
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
* File: libgen_keys.c
* Autor: Leo Pérez Bravo
* Date: 11.03.2018 14:21:23 Sun May 07 14:07:30 CDT 2017
* Description: 
* Este programa genera todas las combinaciones para un password númerico
* de n-dígitos y las imprime en pantalla, una por linea
*		
* This program generates all the combinations for a n-digits numeric
* password and prints one per line
*/

#include "libgen_keys.h"

/**
 * 
 * name: gen_keys
 * @param size first_digit
 * @return void
 * 
 * Genera las claves numéricas de longitud SIZE 
 * Si first_digit es distinto de NULL, se usa como primer elemento de
 * las claves y se generan todas las claves de longitud SIZE-1 
 * concatenadas al first_digit
 */
void gen_keys(int size, int first_digit)
{
	if(size < 2)
	{
		perror("Longitud de clave no permitida\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		char* password;
		SIZE = size;
		password=(char*)malloc(sizeof(char)*SIZE);
		if(!first_digit)
		{
			gen_keys_rec(0,password,SIZE);	
		}
		else
		{
			password[0]=(char)first_digit;
			gen_keys_rec(1,password,SIZE-1);
		}
	}
}

/**
* gen_keys_rec()
* args: 
*		int index: índice actual del dígito en la cadena de password
*		char* password: la cadena del password
*		int size: el tamaño de clave para generar combinaciones
*/
void gen_keys_rec(int index,char* password,int size)
{
	register int i;
	/* Caso base: size = 1 */
	if(size == 1)
	{
		password[SIZE-1]='9';
		for(i = 0 ; i < DIGITS ; i++)
		{
			printf("%s\n",password);
			password[SIZE-1] -= 1;
		}
	}
	else
	{
		password[index]='9';
		for(i = 0 ; i < DIGITS ; i++)
		{
			gen_keys_rec(index+1,password,size-1);
			password[index] -= 1;
		}
	}
}
