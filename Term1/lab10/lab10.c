#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "/home/NR/numerical_recipes.c/nrutil.h"
#include "/home/NR/numerical_recipes.c/nrutil.c"
#include "/home/NR/numerical_recipes.c/gaussj.c"
// #include "/home/NR/numerical_recipes.c/ludcmp.c"
// #include "/home/NR/numerical_recipes.c/lubksb.c"

double drand(double min , double max);
float f(float x, float y) { return sinf(x) * sinf(y) - expf(-powf(x + M_PI / 2.f, 2.f) - powf(y - M_PI / 2.f, 2.f)); }


int main(void)
{
	const int N = 200;
	float x0 = 5.f, y0 = 5.f;
	const float xmin = -10.f, xmax = 10.f;
	const float ymin = -10.f, ymax = 10.f;

	//	Alokacja Zmiennych
	FILE* w0F = fopen("w0.dat", "w");
	FILE* TF = fopen("T.dat", "w");
	struct { float x, y; } w[N];

	// Zadanie
	for (int i = 0; i < N; i++)
	{
		w[i].x = x0;
		w[i].y = y0;
	}

	for (float t = 0.f; t <= 20.f; t += 1.f)
	{
		float Temp = 10.f / powf(2.f, t);

		for (int k = 0; k < 100; k ++)
		{
			for (int i = 0; i < N; i++)
			{
				float dx = w[i].x + drand(-1.f, 1.f);
				float dy = w[i].y + drand(-1.f, 1.f);
				if (dx < xmin) dx = xmin;
				else if (xmax < dx) dx = xmax;
				if (dy < ymin) dy = ymin;
				else if (ymax < dy) dy = ymax;

				float dfw = f(dx, dy);
				float fw = f(w[i].x, w[i].y);
				if (dfw < fw)
				{
					w[i].x = dx;
					w[i].y = dy;
					continue;
				}

				
				float dw = expf(-(dfw - fw) / Temp);
				if (drand(0, 1) < dw)
				{
					w[i].x = dx;
					w[i].y = dy;
				}
				
			}
			fprintf(w0F, "%g\n", f(w[0].x, w[0].y));
		}

		if (t == 0.f || t == 7.f || t == 20.f)
		{
			for (int i = 0; i < N; i++)
				fprintf(TF, "%g %g\n", w[i].x, w[i].y);
			fprintf(TF, "\n\n");
		}
	}

	int s = 0;
	for (int i = 1; i < N; i++)
		if (f(w[i].x, w[i].y) < f(w[s].x, w[s].y))
			s = i;
	printf("MINIMUM: %g\n", f(w[s].x, w[s].y));

	// Dealokacja
	fclose(w0F);
	fclose(TF);

	return 0;
}

double drand(double min , double max)
{
	double r = (double)rand() / RAND_MAX;
	r = r * ( max - min ) + min;
	return r;
}