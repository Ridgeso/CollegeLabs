#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "/home/NR/numerical_recipes.c/nrutil.h"
#include "/home/NR/numerical_recipes.c/nrutil.c"
#include "/home/NR/numerical_recipes.c/four1.c"

const float T = 1.0f;
const float tmax = 3 * T;
const float sigma = T / 20;
const float w = 2 * M_PI / T;
float delta() { return (float)rand() / RAND_MAX - 0.5f; }
float f0func(float t) { return sinf(1.0f * w * t) + sinf(2.0f * w * t) + sinf(3.0f * w * t); }
float gaus(float t) { return 1.0f / (sigma * sqrtf(2.0f * M_PI)) * expf(- t * t / (2.0f * sigma * sigma)); }

int main(void)
{
	const int k[] = { 8, 10, 12 };

	//	Alokacja Zmiennych
	FILE* FF8  = fopen("k8.dat", "w");
	FILE* FF10 = fopen("k10.dat", "w");
	FILE* FF12 = fopen("k12.dat", "w");
	FILE* FFF;

	for (int ki = 0; ki < 3; ki++)
	{
		if (ki == 0) FFF = FF8;
		else if (ki == 1) FFF = FF10;
		else if (ki == 2) FFF = FF12;

		int N = pow(2, k[ki]);
		float dt = tmax / N;

		// Alokacja
		float* f0 = vector(1, 2 * N);
		float* f0copy = vector(1, 2 * N);
		float* f = vector(1, 2 * N);
		float* g1 = vector(1, 2 * N);
		float* g2 = vector(1, 2 * N);

		// Zadanie dla N = 2^k
		for (int i = 1; i <= N; i++)
		{
			float ti = dt * (i - 1.0f);

			f0[2 * i - 1] = f0func(ti) + delta();
			f0[2 * i] = 0;
			f0copy[2 * i - 1] = f0[2 * i - 1];
			f0copy[2 * i] = f0[2 * i];

			g1[2 * i - 1] = g2[2 * i - 1] = gaus(ti);
			g1[2 * i] = g2[2 * i] = 0;
		}

		four1(f0, N, 1);
		four1(g1, N, 1);
		four1(g2, N, -1);

		for (int i = 1; i <= N; i++)
		{
			float a1 = f0[2 * i - 1];
			float b1 = f0[2 * i];

			float a2 = g1[2 * i - 1] + g2[2 * i - 1];
			float b2 = g1[2 * i] + g2[2 * i];

			f[2 * i - 1] = a1 * a2 - b1 * b2;
			f[2 * i] = a1 * b2 + a2 * b1;
		}

		four1(f, N, -1);

		float maxMod = f[1];
		for (int i = 2; i <= N; i++)
			if (maxMod < fabs(f[2 * i - 1]))
				maxMod = fabs(f[2 * i - 1]);


		// Wypisywanie
		for (int i = 1; i <= N; i++)
		{
			float ti = dt * (i - 1.0f);
			fprintf(FFF, "%g %g\n", ti, f0copy[2 * i - 1]);
			// fprintf(FFF, "%g %g\n", ti, f0[2 * i - 1]);
		}
		fprintf(FFF, "\n\n");
		for (int i = 1; i <= N; i++)
		{
			float ti = dt * (i - 1.0f);
			fprintf(FFF, "%g %g\n", ti, f[2 * i - 1] * 2.5f / maxMod);
			// fprintf(FFF, "%g %g\n", ti, f[2 * i - 1]);
		}

		// Dealokacja
		free_vector(f0, 1, 2 * N);
		free_vector(f0copy, 1, 2 * N);
		free_vector(f, 1, 2 * N);
		free_vector(g1, 1, 2 * N);
		free_vector(g2, 1, 2 * N);
	}

	// Dealokacja
	fclose(FF8);
	fclose(FF10);
	fclose(FF12);

	return 0;
}
