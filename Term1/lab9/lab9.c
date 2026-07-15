#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "/home/NR/numerical_recipes.c/nrutil.h"
#include "/home/NR/numerical_recipes.c/nrutil.c"
#include "/home/NR/numerical_recipes.c/gaussj.c"
// #include "/home/NR/numerical_recipes.c/ludcmp.c"
// #include "/home/NR/numerical_recipes.c/lubksb.c"
#define frand() ((double)rand())/(RAND_MAX+1.0)
float Crand() { return (frand() - 0.5f) / 5.f; }

const int m = 50 + 1;
const float xmin = -4.f;
const float xmax = 4.f;
const float x0 = 2.f;
const float sigma = (xmax - xmin) / 16.f;
const int n = 201;

float aplha(float wx[n], float phi[m][n], int j);
float beta(float wx[n], float phi[m][n], int j);
float Fj(float phi[m][n], float wy[n], int mr, int phj, float x)
{
	for (int j = 0; j < mr; j++)
	{
		float sumC = 0;
		float sumS = 0;
		for (int i = 0; i < n; i++)
		{
			
		}
	}
}

int main(void)
{

	//	Alokacja Zmiennych
	float phi[m][n];
	float wx[n];

	FILE* Gram = fopen("Gram.dat", "w");

	// Wypelnianie
	float h = (xmax - xmin) / (n - 1);
	for (int i = 0; i < n; i++)
		wx[i] = xmin + i * h;

	for (int k = 0; k < n; k++)
		phi[0][k] = 1.f;
	for (int k = 0; k < n; k++)
		phi[1][k] = (wx[k] - aplha(wx, phi, 1 - 1)) * phi[0][k];

	for (int j = 2; j < m; j++)
	{
		float aplj = aplha(wx, phi, j - 1);
		float betj = beta(wx, phi, j - 1);
		for (int k = 0; k < n; k++)
		{
			phi[j][k] = (wx[k] - aplj) * phi[j - 1][k] - betj * phi[j - 2][k];
		}
	}


	for (int k = 0; k < n; k++)
	{
		fprintf(Gram, "%g ", wx[k]);
		for (int j = 0; j < 7; j++)
			fprintf(Gram, "%g ", phi[j][k] / phi[j][0]);
		fprintf(Gram, "\n");
	}

	fclose(Gram);

	return 0;
}


float aplha(float wx[n], float phi[m][n], int j)
{
	float sumUp = 0.f;
	float sumDown = 0.f;
	for (int i = 0; i < n; i++)
	{
		float p = phi[j][i] * phi[j][i];
		sumUp += wx[i] * p;
		sumDown += p;
	}

	return sumUp / sumDown;
}

float beta(float wx[n], float phi[m][n], int j)
{
	float sumUp = 0.f;
	float sumDown = 0.f;
	for (int i = 0; i < n; i++)
	{
		sumUp += wx[i] * phi[j - 1][i] * phi[j][i];
		sumDown += phi[j - 1][i] * phi[j - 1][i];
	}

	return sumUp / sumDown;
}