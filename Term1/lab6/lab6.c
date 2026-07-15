#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Dyrektywy zakladajace, ze te trzy pliki sa skopiowane do aktualnego katalogu. */
// #include "nrutil.h"
//#include "nrutil.c" // To mozna usunac, jesli plik jest dodany w poleceniu kompilacji.

/* Dyrektywy dla Taurusa (nie wymagaja kopiowania plikow, ale Taurus musi dzialac...) */
#include "/home/NR/numerical_recipes.c/nrutil.h"
#include "/home/NR/numerical_recipes.c/nrutil.c"
#include "/home/NR/numerical_recipes.c/tred2.c"
#include "/home/NR/numerical_recipes.c/tqli.c"
#include "/home/NR/numerical_recipes.c/pythag.c"


float Dot(int n, float *v1, float *v2)
{
	float sum = 0.f;
	for (int i = 1; i <= n; i++)
		sum += v1[i] * v2[i];
	return sum;
}

void MulMatVec(int n, float **M, float *x, float *outx)
{
	for (int i = 1; i <= n; i++)
		outx[i] = Dot(n, M[i], x);
}

const int n = 7;

int main(void)
{
	float **A, **W;
	float *d, *e, *x0, *xi, *la;

	//	Alokacja macierzy
	A = matrix(1, n, 1, n);
	W = matrix(1, n, 1, n);

	d = vector(1, n);
	e = vector(1, n);
	
	x0 = vector(1, n);
	xi = vector(1, n);
	la = vector(1, n);

	// 	Wypelnienie macierzy A oraz wektorow d, e
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			A[i][j] = W[i][j] = sqrt(i + j);

	// P^-1 * H * P = T czyli P <- T teraz
	tred2(A, n, d, e);

	// Diagonalizowanie T
	// tqli(d, e, n, Y);
	tqli(d, e, n, A);

	// iteracyjnie wyznaczamy wartosci wlasne

	for (int k = 1; k <= n; k++)
	{
		for (int l = 1; l <= n; l++)
			x0[l] = 1.f;

		for (int i = 1; i <= 8; i++)
		{
			MulMatVec(n, W, x0, xi);
			la[k] = Dot(n, xi, x0) / Dot(n, x0, x0);

			float len = sqrt(Dot(n, xi, xi));
			for (int j = 1; j <= n; j++)
				x0[j] = xi[j] / len;
		}

		// redukcja Hotellinga
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				W[i][j] -= x0[i] * x0[j] * la[k];
	}


	// wypisanie macierzy:
	FILE *fp;
	fp = fopen("dane.dat", "w");
	fprintf(fp, "---Wartości własne.---\n---Metoda NR:---\n");
	for(int i = 1; i <= n; i++)
		fprintf(fp, "%g\n", d[i]);
	fprintf(fp, "---Metoda potegowa:---\n");
	for(int i = 1; i <= n; i++)
		fprintf(fp, "%g\n", la[i]);
	fclose(fp);

	//	Zwolnienie pamieci
	free_matrix(A, 1, n, 1, n);
	free_matrix(W, 1, n, 1, n);

	free_vector(d, 1, n);
	free_vector(e, 1, n);

	free_vector(x0, 1, n);
	free_vector(xi, 1, n);
	free_vector(la, 1, n);
	
	return 0;
}