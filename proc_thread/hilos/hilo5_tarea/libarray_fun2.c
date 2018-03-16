/*
 * array_fun.c
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
 * @file array_fun.c
 * @brief funciones auxiliares para trabajar con arreglos 
 */
 
#include "libarray_fun2.h"

int* init_array(int n)
{
	int* mem;
	mem = (int*)malloc(sizeof(int) * n);
	if(!mem)
    {
		perror("Error al asignar memoria\n");
		exit(EXIT_FAILURE);
    }
	return mem;
}

void llena_array(int* array, int n, int max_r)
{
	register int i;
	for(i = 0 ; i < n ; i++)
	{
		array[i] = rand() % max_r ;
	}
}

void print_array(int* array,int n, int row_size)
{
	register int i;
	for(i = 0 ; i < n ; i++)
	{
		if (i % row_size == 0)
		{
			printf("\n");
		}
		printf("%6d ",array[i]);
	}
	printf("\n");
}

void printa(int* array, int n)
{
	register int i;
	for(i = 0 ; i < n ; i++)
	{
		printf("%d ",array[i]);
	}
	printf("\n");
}

int get_mayor(int* datos,int n)
{
	register int i;
	int mayor;
	mayor = datos[0];
	for(i = 1 ; i < n ; i++)
	{
		if(datos[i] > mayor)
		{
			mayor = datos[i];
		}
	}
	return mayor;
}

int get_menor(int* datos,int n)
{
	register int i;
	int menor;
	menor = datos[0];
	for(i = 1 ; i < n ; i++)
	{
		if(datos[i] < menor)
		{
			menor = datos[i];
		}
	}
	return menor;
}

int get_promedio(int* datos,int n)
{
	register int i;
	int promedio;
	promedio = 0;
	for(i = 0 ; i < n ; i++)
	{
		promedio += datos[i];
	}
	return promedio/=n;
}
