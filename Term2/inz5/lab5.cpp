#include <iostream>
#include <fstream>
#include <cmath>
#include <numbers>
#include <chrono>
using namespace std;
using namespace chrono;
using namespace numbers;

#define fi int_fast32_t
#define cef constexpr float
#define cei constexpr int32_t

cef pif = pi_v<float>;
cef delta = 0.2F;
cei nx = 128;
cei ny = 128;
cef xmax = delta * nx;
cef ymax = delta * ny;
cef TOL = 1e-8F;
constexpr int32_t kmax = 16;

float V[nx + 1][ny + 1] = { 0 };

float CountS(const int32_t k) noexcept
{
	const float pref = k * k * delta * delta / 2.F;
	const float denomSq = 1.F / (4.f * delta * delta * k * k);
	float S = 0;
	for (fi i = 0; i <= nx - k; i += k)
		for (fi j = 0; j <= ny - k; j += k)
		{
			float br1 = V[i + k][j] - V[i][j] + V[i + k][j + k] - V[i][j + k];
			br1 = br1 * br1 * denomSq;
			float br2 = V[i][j + k] - V[i][j] + V[i + k][j + k] - V[i + k][j];
			br2 = br2 * br2 * denomSq;
			S += pref * (br1 + br2);
		}
	return S;
}

void DenseV(const int32_t k) noexcept
{
	const int32_t hk = k / 2;
	for (fi i = 0; i <= nx - k; i += k)
	{
		for (fi j = 0; j <= ny - k; j += k)
		{
			V[i + hk][j + hk] = 0.25F * (V[i][j] + V[i + k][j] + V[i][j + k] + V[i + k][j + k]);
			if (i + k != nx)
				V[i + k][j + hk] = 0.5F * (V[i + k][j] + V[i + k][j + k]);
			if (j + k != ny)
				V[i + hk][j + k] = 0.5F * (V[i][j + k] + V[i + k][j + k]);
			if (j != 0)
				V[i + hk][j] = 0.5F * (V[i][j] + V[i + k][j]);
			if (i != 0)
				V[i][j + hk] = 0.5F * (V[i][j] + V[i][j + k]);
		}
	}
}

void Dyskretyzacja(const int32_t k)
{
	for (fi i = k; i <= nx - k; i += k)
		for (fi j = k; j <= ny - k; j += k)
			V[i][j] = 0.25F * (V[i + k][j] + V[i - k][j] + V[i][j + k] + V[i][j - k]);
}

int32_t main()
{
	ofstream Slog("Slog.txt");
	ofstream Contour("Contour.txt");
	auto timeStart = high_resolution_clock::now();
	
	for (fi x = 0; x <= nx; x++)
	{
		V[x][0] = sinf(2.F * pif * x * delta / xmax);
		V[x][ny] = -V[x][0];
	}
	for (fi y = 0; y <= ny; y++)
		V[0][y] = V[nx][y] = sinf(pif * y * delta / ymax);

	int32_t it = 1;
	float Sp = numeric_limits<float>::infinity();
	float S = numeric_limits<float>::max();

	for (int32_t k = kmax; k > 0; k /= 2)
	{
		do
		{
			Dyskretyzacja(k);
			Sp = S;
			S = CountS(k);
			Slog << k << ' ' << it << ' ' << S << endl;
			it++;
		} while (fabs((S - Sp) / Sp) >= TOL);

		for (int32_t i = 0; i <= nx; i += k)
		{
			for (int32_t j = 0; j <= ny; j += k)
				Contour << V[i][j] << " ";
			Contour << endl;
		}

		Contour << endl;

		if (k != 1)
			DenseV(k);
	}

	cout << "Ilosc iteracji: " << it << endl;

	auto timeEnd = high_resolution_clock::now();
	cout << duration_cast<milliseconds>(timeEnd - timeStart).count() << "ms" << endl;
	Slog.close();
	Contour.close();
	return 0;
}
