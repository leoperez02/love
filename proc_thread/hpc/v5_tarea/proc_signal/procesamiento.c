#include "procesamiento.h"

void genera_seno(float seno[])
{
	register int n;
	float f,fs;
	f = 1000;
	fs = 45000;
	for(n = 0 ; n < MUESTRAS ; n++)
	{
		seno[n] = sinf(2*M_PI*f*n/fs);
	}
}

void genera_hamming(float h[])
{
	register int n;
	float f,fs;
	f = 1000;
	fs = 45000;
	for(n = 0 ; n < MUESTRAS ; n++)
	{
		h[n] = 0.54 - 0.46 * cosf( (2*M_PI*n) / ((MUESTRAS - 1)) );
	}
}

