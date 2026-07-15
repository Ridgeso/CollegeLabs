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
#include "mgmres.h"

using namespace std;
using namespace chrono;

// Constants
constexpr double delta = 0.1;
constexpr array<int32_t, 4> nx = { 4, 50, 100, 200 };
constexpr array<int32_t, 4> ny = { 4, 50, 100, 200 };
constexpr double V1 = 10, V3 = 10, V2 = -10, V4 = -10;

template <int32_t Ni>
constexpr int32_t N = (nx[Ni] + 1) * (ny[Ni] + 1);

constexpr int32_t itr_max = 500, mr = 500;
constexpr double tol_abs = 1e-8, tol_rel = 1e-8;

constexpr array<double, 3> epsilon1 = { 1.0, 2.0, 10.0 };
constexpr array<double, 4> epsilon2 = { 1.0, 1.0, 1.0 };
template <int32_t Ni, int32_t Ei>
inline const double epsilon(const int32_t i)
{
	return i > nx[Ni] / 2 ? epsilon1[Ei] : epsilon2[Ei];
}

static array<array<double, ny[2]>, nx[2]> PArr = { 0.0 };
double CalcP(const int32_t i, const int32_t j)
{
		constexpr double xmax = delta * nx[2], ymax = delta * ny[2];
		constexpr double sigma = xmax / 10.0;
		const double x = delta * i;
		const double y = delta * j;
	
		const double ysi = (y - 0.5 * ymax) * (y - 0.5 * ymax) / (sigma * sigma);
		const double xsi1 = (x - 0.25 * xmax) * (x - 0.25 * xmax) / (sigma * sigma);
		const double xsi2 = (x - 0.75 * xmax) * (x - 0.75 * xmax) / (sigma * sigma);
		const double p1 = std::exp(-xsi1 - ysi);
		const double p2 = -std::exp(-xsi2 - ysi);
		return p1 + p2;
}
template <bool Enable>
inline double GetP(const int32_t i, const int32_t j)
{
	if constexpr (!Enable)
		return 0.0;
	else
		return PArr[i][j];
}

template <int32_t Ni>
struct Data
{
	array<double, 5 * N<Ni>> a = { 0.0 };
	array<int32_t, 5 * N<Ni>> ja = { 0 };
	array<int32_t, N<Ni> +1> ia = { 0 };
	array<double, N<Ni>> b = { 0.0 };
	array<double, N<Ni>> V = { 0.0 };
};

template <typename T>
struct Heap
{
	Heap()
		: p(new T)
	{ }
	~Heap()
	{
		delete p;
	}
	T* operator->() { return p; }
	T* p;
};

template <typename T>
struct Stack
{
	Stack() = default;
	~Stack() = default;
	T* operator->() { return &p; }
	T p;
};

#define ONE_MB 1024 * 1024
template <typename T>
using Scope = typename conditional<(sizeof(T) >= ONE_MB), Heap<T>, Stack<T>>::type;

template <int32_t Ni, int32_t Ei, bool Enable>
void zadanie(const string& index)
{
	Scope<Data<Ni>> data{};

	cout << epsilon<Ni, Ei>(0) << " " << epsilon<Ni, Ei>(10000000) << endl;

	int32_t k = -1;
	for (int32_t l = 0; l < N<Ni>; l++)
	{
		const int32_t j = (int32_t)std::floor(l / (nx[Ni] + 1));
		const int32_t i = l - j * (nx[Ni] + 1);

		bool brzeg = false;
		double vb = 0.0;

		if (i == 0)
		{
			brzeg = true;
			vb = V1;
		}
		if (j == ny[Ni])
		{
			brzeg = true;
			vb = V2;
		}
		if (i == nx[Ni])
		{
			brzeg = true;
			vb = V3;
		}
		if (j == 0)
		{
			brzeg = true;
			vb = V4;
		}

		if (Enable)
			vb = 0.0;
		data->b[l] = brzeg ? vb : -GetP<Enable>(i, j);

		data->ia[l] = -1;
		if (l - nx[Ni] - 1 >= 0 && !brzeg)
		{
			k++;
			if (data->ia[l] < 0)
				data->ia[l] = k;
			data->a[k] = epsilon<Ni, Ei>(i) / (delta * delta);
			data->ja[k] = l - nx[Ni] - 1;
		}

		if (l - 1 >= 0 && !brzeg)
		{
			k++;
			if (data->ia[l] < 0)
				data->ia[l] = k;
			data->a[k] = epsilon<Ni, Ei>(i) / (delta * delta);
			data->ja[k] = l - 1;
		}

		k++;
		if (data->ia[l] < 0)
			data->ia[l] = k;
		if (!brzeg)
			data->a[k] = -(2 * epsilon<Ni, Ei>(i) + epsilon<Ni, Ei>(i + 1) + epsilon<Ni, Ei>(i + nx[Ni] + 1)) / (delta * delta);
		else
			data->a[k] = 1;
		data->ja[k] = l;

		if (l < N<Ni> && !brzeg)
		{
			k++;
			data->a[k] = epsilon<Ni, Ei>(i) / (delta * delta);
			data->ja[k] = l + 1;
		}

		if (l < N<Ni> - nx[Ni] - 1 && !brzeg)
		{
			k++;
			data->a[k] = epsilon<Ni, Ei>(i + nx[Ni] + 1) / (delta * delta);
			data->ja[k] = l + nx[Ni] + 1;
		}
	}
	int32_t nz_num = k + 1;
	data->ia[N<Ni>] = nz_num;

	if constexpr (Ni == 0)
	{
		fstream indexy("indexy.txt", ios::out);
		indexy << "# l\ti_l\tj_l\tb[l]" << endl;
		for (int32_t l = 0; l < N<Ni>; l++)
		{
			const int32_t j = (int32_t)std::floor(l / (nx[Ni] + 1));
			const int32_t i = l - j * (nx[Ni] + 1);
			indexy << l << '\t' << i << '\t' << j << '\t' << data->b[l] << endl;
		}
		indexy << endl << "# k\ta[k]" << endl;
		for (int32_t l = 0; l < 5 * N<Ni>; l++)
			indexy << l << '\t' << data->a[l] << endl;
		indexy.close();
	}
	else
	{
		pmgmres_ilu_cr(
			N<Ni>,
			nz_num,
			data->ia.data(),
			data->ja.data(),
			data->a.data(),
			data->V.data(),
			data->b.data(),
			itr_max,
			mr,
			tol_abs,
			tol_rel
		);

		fstream fields("fields" + index + ".txt", ios::out);
		fields << "nx, ny = " << nx[Ni] << " " << ny[Ni] << endl;

		for (int32_t l = 0; l < N<Ni>; l++)
		{
			const int32_t j = (int32_t)std::floor(l / (nx[Ni] + 1));
			const int32_t i = l - j * (nx[Ni] + 1);
			fields << i << '\t' << j << '\t' << data->V[l] << endl;
		}


		fields.close();
	}
}

int main()
{
	const auto Start = high_resolution_clock::now();

	zadanie<0, 0, false>("");

	zadanie<1, 0, false>("1");
	zadanie<2, 0, false>("2");
	zadanie<3, 0, false>("3");

	for (int32_t l = 0; l < N<2>; l++)
	{
		const int32_t j = (int32_t)std::floor(l / (nx[2] + 1));
		const int32_t i = l - j * (nx[2] + 1);
		PArr[i][j] = CalcP(i, j);
	}

	zadanie<2, 0, true>("4");
	zadanie<2, 1, true>("5");
	zadanie<2, 2, true>("6");

	const auto End = high_resolution_clock::now();

	cout << duration_cast<milliseconds>(End - Start).count() / 1000.0 << "s" << endl;

	return 0;
}
