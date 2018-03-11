#include <stdio.h>
#include <stdlib.h>
#include "libinsertion_sort.h"
#include "libarray_fun.h"

int main(void)
{
	int n,i;
	int *A;
	printf("Escribe el valor de n=");
	scanf("%d",&n);
	fflush(stdin);
	A=(int*)malloc(n*sizeof(int));
	printf("Escribe los numeros:\n");
	for(i = 0 ; i < n ; i++)
	{
		printf("#%d--> ",i+1);
		scanf("%d",A+i);
		fflush(stdin);
	}
	printa(A,n);
	insertion_sort(A,n);
	printf("\n\n");
	printa(A,n);
	return 0;
}
