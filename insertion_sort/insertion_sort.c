#include<stdio.h>
#include<stdlib.h>

void insertion_sort(int*,int);
void printa(int*,int);

void insertion_sort(int* A,int n)
{
	int llave,i;
	for(int j=1;j<n;j++)
	{
		llave=A[j];
		i=j-1;
		while(llave<A[i] && i>=0)
		{
			A[i+1]=A[i];
			i-=1;
		}
		A[i+1]=llave;
	}
}

int main(void)
{
	int n;
	printf("Escribe el valor de n=");
	scanf("%d",&n);
	fflush(stdin);
	int* A=(int*)malloc(n*sizeof(int));
	printf("Escribe los numeros:\n");
	for(int i=0;i<n;i++)
	{
		printf("#%d--> ",i+1);
		scanf("%d",A+i);
		fflush(stdin);
	}
	printa(A,n);
	insertion_sort(A,n);
	printf("\n\n");
	printa(A,n);
	return 1;
}

void printa(int* A,int n)
{
	for(int i=0;i<n;i++)
		printf("%d, ",A[i]);
}