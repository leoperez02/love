/*
 * tareah.c
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
 * @file tareah.c
 * @brief Tarea de hilos para sistemas embedidos
 * Este programa crea un arreglo de N elementos y lo llena con valores
 * aleatorios entre 0 y 255 (8 bits). Obtiene el elemento mayor,
 * el menor, el promedio y ordena los elementos creando un hilo para 
 * cada tarea
 * 
 * */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "libvector_fun.h"

#define N 64

int main(void)
{
	
	pthread_t tid_mayor, tid_menor, tid_promedio, tid_sort;
	int *mayor, *menor, *promedio;
	vector *datos, *datos_sort;
		
	datos = init_vector(N);
	llena_vector(datos);
	print_vector(datos);
	
	/* Crear hilo con atributos default */
	
	pthread_create(&tid_mayor,    NULL, get_mayor,    (void*)datos);
	pthread_create(&tid_menor,    NULL, get_menor,    (void*)datos);
	pthread_create(&tid_promedio, NULL, get_promedio, (void*)datos);
	pthread_create(&tid_sort,     NULL, sort_vector,  (void*)datos);
	

	/* Recibir los datos luego de que hilo termina */
	
	pthread_join(tid_mayor,    (void**)&mayor     );
	pthread_join(tid_menor,    (void**)&menor     );
	pthread_join(tid_promedio, (void**)&promedio  );
	pthread_join(tid_sort,     (void**)&datos_sort);
	
	printf("El número MAYOR es %d\n", *mayor);
	printf("El número MENOR es %d\n", *menor);
	printf("El PROMEDIO es %d\n", *promedio);
	printf("El arreglo ordenado es");
	print_vector(datos_sort);
	
	/* Liberar memoria asignada a estructuras vector para arreglos */
	free_vector(datos);
	
	return 0;
}
