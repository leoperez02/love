#include <stdio.h>
#include <stdlib.h>
#include "merge_sort.h"

void printa(int*,int);

int main(void)
{
	int n;
	int* A;
	register int i;
	printf("Escribe el valor de n=");
	scanf("%d",&n);
	fflush(stdin);
	A=(int*)malloc(n*sizeof(int));
	printf("Escribe los numeros:\n");
	for( i=0;i<n;i++)
	{
		printf("#%d--> ",i+1);
		scanf("%d",A+i);
		fflush(stdin);
	}
	printa(A,n);
	A=merge_sort(A,n);
	printf("\n\n");
	printa(A,n);
	return 0;
}

void printa(int* A,int n)
{
	register int i;
	for( i=0;i<n;i++)
	{
		printf("%d, ",A[i]);
	}
	printf("\n");
}
