#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Dyrektywy zakladajace, ze te trzy pliki sa skopiowane do aktualnego katalogu. */
// #include "nrutil.h"
//#include "nrutil.c" // To mozna usunac, jesli plik jest dodany w poleceniu kompilacji.
//#include "gaussj.c" // To tez mozna usunac, jesli plik jest dodany w poleceniu kompilacji.

/* Dyrektywy dla Taurusa (nie wymagaja kopiowania plikow, ale Taurus musi dzialac...) */
#include "/home/NR/numerical_recipes.c/nrutil.h"
#include "/home/NR/numerical_recipes.c/nrutil.c"
#include "/home/NR/numerical_recipes.c/tred2.c"
#include "/home/NR/numerical_recipes.c/tqli.c"
#include "/home/NR/numerical_recipes.c/pythag.c"

const int nx = 20;
const int ny = 20;
const int m = 10;
const float t = -0.021;
const int n = nx * ny;

int main(void)
{
	float **H, **Y, **X;
	float *d, *e;
	int *indx;
	//	Alokacja macierzy
	H = matrix(1, n, 1, n);
	Y = matrix(1, n, 1, n);
	X = matrix(1, n, 1, n);
	
	d = vector(1, n);
	e = vector(1, n);
	indx = ivector(1, n);

	// 	Wypelnienie macierzy H oraz wektorow d, e
	for(int i = 1; i <= nx; i++)
	{
		d[i] = e[i] = 0.f;

		for(int j = 1; j <= ny; j++)
		{
			int l = j + (i - 1) * ny;

			for(int k = 1; k <= n; k++)
			{
				H[l][k] = 0.;
				Y[l][k] = l == k ? 1.f : 0.f;
			}
			if(i > 1)
				H[l][l - ny] = t; //dla i=1 nie ma sasiada z lewej strony
			if(i < nx)
				H[l][l + ny] = t; //dla i=nx nie ma sasiada z prawej strony
			H[l][l] = -4 * t;
			if(j > 1)
				H[l][l - 1] = t; //dla j=1 nie ma sasiada ponizej siatki
			if(j < ny)
				H[l][l + 1] = t; //dla j=ny nie ma sasiada powyzej siatki
		}
	}

	// P^-1 * H * P = T czyli P <- T teraz
	tred2(H, n, d, e);

	// Diagonalizowanie T
	tqli(d, e, n, Y);

	// X = P * Y
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			float sum = 0.f;
			for (int k = 1; k <= n; k++)
				sum += H[i][k] * Y[k][j];
			X[i][j] = sum;
		}
	}

	
	// sortowanie
	for(int l = 1; l <= n; l++)
		indx[l] = l;

	for(int l = 1; l <= n - 1; l++)
	{
		for(int k = n; k >= l + 1; k--)
		{
			float e1 = d[k - 1];
			float e2 = d[k];
			float l1 = indx[k - 1];
			float l2 = indx[k];
			if(e2 < e1){ //wymieniamy energie i indeksy wektorów miejscami
				d[k] = e1;
				d[k - 1] = e2;
				indx[k] = l1;
				indx[k - 1] = l2;
			}
		}
	}
	
	// wypisanie macierzy:
	FILE *fp;
	fp = fopen("dane.dat", "w");
	for(int i = 1; i <= nx; i++)
	{
		for(int j = 1; j <= ny; j++)
		{
			int l = j + (i - 1) * ny;
			fprintf(fp, "%6d %6d ", i, j);
			for(int k = 1; k <= m; k++)
				fprintf(fp, " %12.6f ", X[l][indx[k]]);
			fprintf(fp, "\n");
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

	//	Zwolnienie pamieci
	free_matrix(H, 1, n, 1, n);
	free_matrix(Y, 1, n, 1, n);
	free_matrix(X, 1, n, 1, n);
	free_vector(d, 1, n);
	free_vector(e, 1, n);
	free_ivector(indx, 1, n);

	return 0;
}