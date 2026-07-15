#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "/home/NR/numerical_recipes.c/nrutil.h"
#include "/home/NR/numerical_recipes.c/nrutil.c"
#include "/home/NR/numerical_recipes.c/gaussj.c"
// #include "/home/NR/numerical_recipes.c/ludcmp.c"
// #include "/home/NR/numerical_recipes.c/lubksb.c"

float f1(float x) { return 1.f / (1.f + x * x); }
float f2(float x) { return cosf(2.f * x); }

void wyzM(float *wx,float *wy, float *m, int n, float alfa, float beta)
{
	float **A, **d;
	//	Alokacja macierzy
	A = matrix(1, n, 1, n);
	d = matrix(1, n, 1, 1);

	// 	Wypelnienie macierzy M i wektora b
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			A[i][j] = 0.0;

	A[1][1] = 1.f; A[1][2] = 0.f;
	A[n][n] = 1.f;
	d[1][1] = alfa;
	d[n][1] = beta;
	 
	for (int i = 2; i <= n - 1; i++)
	{
		float miui = 1.f;
		float hi = wx[i] - wx[i - 1];
		float hip = wx[i + 1] - wx[i];
		float di = 6.f / (hi + hip) * ((wy[i + 1] - wy[i]) / hip - (wy[i] - wy[i - 1]) / hi);
		float lambdai = hip / (hi + hip);

		A[i][i] = 2.f;
		A[i][i - 1] = miui;
		A[i][i + 1] = lambdai;
	
		d[i][1] = di;
	}

	//	Rozwiazanie ukladu rownan Am = d - wywolanie procedury:
	gaussj(A, n, d, 1);

	for (int i = 1; i <= n; i++)
		m[i] = d[i][1];

	free_matrix(A, 1, n, 1, n);
	free_matrix(d, 1, n, 1, 1);
}

float wyzSx(float *wx,float *wy, float *m, int n, float x)
{
	float sx;

	for (int i = 2; i <= n; i++)
	{
		float hi = wx[i] - wx[i - 1];
		float Ai = (wy[i] - wy[i - 1]) / hi - hi / 6.f * (m[i] - m[i - 1]);
		float Bi = wy[i - 1] - m[i - 1] * hi * hi / 6.f;

		sx = m[i - 1] * (wx[i] - x) * (wx[i] - x)* (wx[i] - x) / (6.f * hi);
		sx += m[i] * (x - wx[i - 1]) * (x - wx[i - 1])* (x - wx[i - 1]) / (6.f * hi);
		sx += Ai * (x - wx[i - 1]) + Bi;
	}

	return sx;
}


int main(void)
{
	// const int n = 10;
	const int nl[] = { 5, 8, 21 };
	const float xmin = -5.f, xmax = 5.f;

	float* wx, * wy1, * wy2, * m;
	FILE* out1 = fopen("f1.dat", "w");
	FILE* out2 = fopen("f2.dat", "w");
	FILE* pochodneOut = fopen("pochodne.dat", "w");

	for (int ni = 0; ni < sizeof(nl)/sizeof(nl[0]); ni++)
	{
		int n = nl[ni];

		//	Alokacja Zmiennych
		wx = vector(1, n);
		wy1 = vector(1, n);
		wy2 = vector(1, n);
		m = vector(1, n);

		// Wypelnianie
		float h = (xmax - xmin) / (n - 1.f);
		for (int i = 1; i <= n; i++)
		{
			wx[i] = xmin + (i - 1) * h;
			wy1[i] = f1(wx[i]);
			wy2[i] = f2(wx[i]);
		}

		// Zadanie
		wyzM(wx, wy1, m, n, 0.f, 0.f);
		wyzM(wx, wy2, m, n, 0.f, 0.f);

		// fprintf(out1, "n=%d\n\n", n);
		// fprintf(out2, "n=%d\n\n", n);
		for (float x = xmin; x <= xmax + 0.005; x += 0.01)
		{
			float sx1 = wyzSx(wx, wy1, m, n, x);
			float sx2 = wyzSx(wx, wy2, m, n, x);

			fprintf(out1, "%g %g\n", x, sx1);
			fprintf(out2, "%g %g\n", x, sx2);
		}
		fprintf(out1, "\n");
		fprintf(out2, "\n");

		//	Zwolnienie pamieci
		free_vector(wx, 1, n);
		free_vector(wy1, 1, n);
		free_vector(wy2, 1, n);
		free_vector(m, 1, n);
	}

	{
		const float deltax = 0.01;
		int n = 10;
		
		wx = vector(1, n);
		wy1 = vector(1, n);
		wy2 = vector(1, n);
		m = vector(1, n);

		float h = (xmax - xmin) / (n - 1.f);
		for (int i = 1; i <= n; i++)
		{
			wx[i] = xmin + (i - 1) * h;
			wy1[i] = f1(wx[i]);
			wy2[i] = (f1(wx[i] - deltax) - 2 * f1(wx[i]) + f1(wx[i] + deltax)) / (deltax * deltax);
		}

		wyzM(wx, wy1, m, n, 0.f, 0.f);
		
		for (int i = 1; i <= n; i++)
		{
			fprintf(pochodneOut, "%g %g %g\n", wx[i], m[i], wy2[i]);
		}

		free_vector(wx, 1, n);
		free_vector(wy1, 1, n);
		free_vector(wy2, 1, n);
		free_vector(m, 1, n);
	}

	fclose(out1);
	fclose(out2);
	fclose(pochodneOut);

	return 0;
}