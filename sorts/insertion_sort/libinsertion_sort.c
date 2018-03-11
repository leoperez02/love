#include "libinsertion_sort.h"

void insertion_sort(int* A,int n)
{
	int llave,i,j;
	for(j = 1 ; j < n ; j++)
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
