#include <iostream>
#include <type_traits>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <array>
#include <execution>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

// Constants
constexpr double delta = 0.01;
constexpr double ro = 1;
constexpr double miu = 1;
constexpr int32_t nx = 200;
constexpr int32_t ny = 200;
constexpr int32_t I1 = 50;
constexpr int32_t J1 = 55;
constexpr int32_t IT_MAX = 2000;

using arr = array<array<double, ny + 1>, nx + 1>;

constexpr double yJ1 = delta * J1;
constexpr double yny = delta * ny;

inline double Omega(const int32_t it)
{
	return it < 2000 ? 0 : 1;
}

constexpr inline double getQwy(const double qwe)
{
	return qwe
		* (yny * yny * yny
			- yJ1 * yJ1 * yJ1
			- 3 * yJ1 * yny * yny
			+ 3 * yJ1 * yJ1 * yny)
		/ (yny * yny * yny);
}
constexpr array<double, 3> Qwe = { -1000, -4000, 4000 };
constexpr array<double, 3> Qwy = { getQwy(Qwe[0]), getQwy(Qwe[1]), getQwy(Qwe[2])};

template <typename T> struct Heap
{
	T* p;
	
	Heap() : p(new T) {}
	~Heap() { delete p; }
	inline T& operator*() { return *p; };
	typename T::value_type& operator[](const int32_t ind) { return (*p)[ind]; }
};

template <typename T> struct Stack
{
	T p;

	Stack() = default;
	~Stack() = default;
	inline T& operator*() noexcept { return p; };
	typename T::value_type& operator[](const int32_t ind) { return p[ind]; }
};

#define ONE_MB 1024 * 128
template <typename T> using DynScope = typename conditional<(sizeof(T) >= ONE_MB), Heap<T>, Stack<T>>::type;

const bool isWB(const int32_t i, const int32_t j)
{
	return i <= I1 && j <= J1;
}

void WBpsi(int32_t Qi, arr& psi)
{
	for (int32_t j = J1; j <= ny; j++)
	{
		const double y = delta * j;
		psi[0][j] = Qwe[Qi] / (2 * miu) * (y * y * y / 3 - y * y * 0.5 * (yJ1 + yny) + y * yJ1 * yny);
	}
	for (int32_t j = 0; j <= ny; j++)
	{
		const double y = delta * j;
		psi[nx][j] = Qwy[Qi] / (2 * miu) * (y * y * y / 3 - y * y * 0.5 * yny) + (Qwe[Qi] * yJ1 * yJ1 * (-yJ1 + 3 * yny)) / (12 * miu);
	}
	for (int32_t i = 1; i <= nx - 1; i++)
		psi[i][ny] = psi[0][ny];

	for (int32_t i = I1 + 1; i <= nx - 1; i++)
		psi[i][0] = psi[0][J1];
	
	for (int32_t j = 1; j <= J1; j++)
		psi[I1][j] = psi[0][J1];
	
	for (int32_t i = 1; i <= I1; i++)
		psi[i][J1] = psi[0][J1];
}

void WBzeta(int32_t Qi, arr& zeta, const arr& psi)
{
	for (int32_t j = J1; j <= ny; j++)
	{
		const double y = delta * j;
		zeta[0][j] = Qwe[Qi] / (2 * miu) * (2 * y - yJ1 - yny);
	}

	for (int32_t j = 0; j <= ny; j++)
	{
		const double y = delta * j;
		zeta[nx][j] = Qwy[Qi] / (2 * miu) * (2 * y - yny);
	}

	for (int32_t i = 1; i <= nx - 1; i++)
		zeta[i][ny] = 2 / (delta * delta) * (psi[i][ny - 1] - psi[i][ny]);
	
	for (int32_t i = I1 + 1; i <= nx - 1; i++)
		zeta[i][0] = 2 / (delta * delta) * (psi[i][1] - psi[i][0]);

	for (int32_t j = 1; j <= J1 - 1; j++)
		zeta[I1][j] = 2 / (delta * delta) * (psi[I1 + 1][j] - psi[I1][j]);
	
	for (int32_t i = 1; i <= I1 - 1; i++)
		zeta[i][J1] = 2 / (delta * delta) * (psi[i][J1 + 1] - psi[i][J1]);

	zeta[I1][J1] = 0.5 * (zeta[I1 - 1][J1] + zeta[I1][J1 - 1]);
}

void zadanie(const int32_t Qi)
{
	DynScope<arr> psi{};
	DynScope<arr> zeta{};

	fstream debug("debug" + to_string(Qi) + ".dat", ios::out);

	// WB psi
	WBpsi(Qi, *psi);

	// Algorytm
	for (int32_t it = 0; it < IT_MAX; it++)
	{
		for (int32_t i = 1; i <= nx - 1; i++)
			for (int32_t j = 1; j <= ny - 1; j++)
			{
				if (!isWB(i, j))
				{
					psi[i][j] = 0.25 * (psi[i + 1][j] + psi[i - 1][j] + psi[i][j + 1] + psi[i][j - 1] - delta * delta * zeta[i][j]);

					// if (isnan(psi[i][j]))
					// {
					// 	debug << it << ": " << i << " " << j << " psi: " << zeta[i][j] << endl;
					// 	exit(0);
					// }
	
					const double zetaP1 = 0.25 * (zeta[i + 1][j] + zeta[i - 1][j] + zeta[i][j + 1] + zeta[i][j - 1]);
					const double zetaP2 = Omega(it) * ro / (16 * miu);
					const double zetaP3 = (psi[i][j + 1] - psi[i][j - 1]) * (zeta[i + 1][j] - zeta[i - 1][j]);
					const double zetaP4 = (psi[i + 1][j] - psi[i - 1][j]) * (zeta[i][j + 1] - zeta[i][j - 1]);
					zeta[i][j] = zetaP1 - zetaP2 * (zetaP3 - zetaP4);
				}
			}

		// Modyfikacja WB
		WBzeta(Qi, *zeta, *psi);

		// Kontrola bledu
		constexpr int32_t J2 = J1 + 2;
		double Gamma = 0;
		for (int32_t i = 1; i <= nx - 1; i++)
		{
			Gamma += (psi[i + 1][J2]
				+ psi[i - 1][J2]
				+ psi[i][J2 + 1]
				+ psi[i][J2 - 1]
				- 4 * psi[i][J2]
				- delta * delta * zeta[i][J2]);
		}
	}

	debug.close();
	fstream data;

	if (Qi == 0)
		data = fstream("wyn.dat", ios::out);
	else if (Qi == 1)
		data = fstream("wyn_Qm4000.dat", ios::out);
	else
		data = fstream("wyn_Q4000.dat", ios::out);

	for (int32_t i = 1; i <= nx - 1; i++)
	{
		for (int32_t j = 1; j <= ny - 1; j++)
		{
			double u = (psi[i][j + 1] - psi[i][j - 1]) / (2 * delta);
			double v = -(psi[i + 1][j] - psi[i - 1][j]) / (2 * delta);
			if (!isWB(i, j))
				data << i * delta << ' ' << j * delta << ' ' << psi[i][j] << ' ' << zeta[i][j] << ' ' << u << ' ' << v << endl;
			else
				data << i * delta << ' ' << j * delta << ' ' << psi[0][J1] << ' ' << zeta[0][J1] << ' ' << 0 << ' ' << 0 << endl;
		}
		data << endl;
	}

	data.close();
}

int main()
{
	const auto Start = high_resolution_clock::now();

	thread t1(zadanie, 0);
	thread t2(zadanie, 1);
	thread t3(zadanie, 2);

	t1.join();
	t2.join();
	t3.join();

	const auto End = high_resolution_clock::now();

	cout << duration_cast<milliseconds>(End - Start).count() / 1000.0 << "s" << endl;

	return 0;
}
