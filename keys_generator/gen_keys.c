/**
* File: gen_keys.c
* Autor: Leo Pérez Bravo
* Date: Sun May 07 14:07:30 CDT 2017
* Description: 
*		Este programa genera todas las combinaciones para un password númerico
* 		de n-dígitos.
*		
*		This program generates all the combinations for a n-digits numeric
*		password. 
*/
#include <stdio.h>
#include <stdlib.h>

/* DIGITS: el número de opciones 0,1,2 ... 9 */
#define DIGITS 10

/* gen_keys_rec() : función para generar claves de manera recursiva */
void gen_keys_rec(int index,char* password, int size);

/* SIZE: tamaño del password */
int SIZE;

/**
* MAIN: el tamaño del password se pasa como primer argumento.
*		Opcionalmente se puede pasar un segundo argumento para indicar con que
*		dígito empieza la clave 
*/
int main(int argc,char** argv)
{
	if(argc < 2)
	{
		perror("Longitud de clave no permitida\n");
		return 1;
	}
	else
	{
		char* password=(char*)malloc(sizeof(char)*SIZE);
		SIZE = atoi(argv[1]);
		if(argc < 3)
		{
			gen_keys_rec(0,password,SIZE);	
		}
		else
		{
			password[0]=argv[2][0];
			gen_keys_rec(1,password,SIZE-1);
		}
	}
	return 0;
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
