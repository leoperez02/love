/*
 * main_vector_fun.c
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
 * @file main_vector_fun
 * @brief Test de biblioteca libvector_fun.h
 * Se prueban las funciones básicas para trabajar con la estructura vector
 * 
 **/
#include <stdio.h>  
#include "libvector_fun.h"

#define SIZE 32
#define MAX_R 4096

int main(void)
{
	vector *vec;
	int *mayor, *menor, *promedio;
	
	/* Inicialización de un vector */
	vec = init_vector(SIZE);
	
	/* Llenado aleatorio de datos */
	llena_vector(vec);
	
	/* Impresion del arreglo en una linea */
	/*
	printf("Vector en una sola linea:\n");
	printa(array, SIZE, 8);
	*/
	
	/* Impresion del arreglo en bloques de n elementos */
	printf("Vector en bloques de 16 elementos:");
	print_vector(vec);
	
	/* Test de funciones para hallar el mayor y menor del vector */
	mayor    = (int*) get_mayor((void*)vec);
	menor    = (int*) get_menor((void*)vec);
	promedio = (int*) get_promedio((void*)vec);
	
	printf("Elemento MAYOR = %d\n",*mayor);
	printf("Elemento MENOR = %d\n",*menor);
	printf("PROMEDIO = %d\n",*promedio);
	printf("Vector ordenado: ");
	print_vector(sort_vector(vec));
	
	/* Liberar memoria de la estructura*/
	free_vector(vec);
	
	return 0;
}
