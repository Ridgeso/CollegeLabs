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
#include <filesystem>
#include <cstring>
#include <numbers>

using namespace std;
using namespace chrono;

constexpr int32_t nx = 400;
constexpr int32_t ny = 90;
constexpr int32_t I1 = 200;
constexpr int32_t I2 = 210;
constexpr int32_t J1 = 50;
constexpr double delta = 0.01;
constexpr double sigma = 10 * delta;
constexpr double xa = 0.45;
constexpr double ya = 0.45;
constexpr int32_t IT_MAX = 10000;

inline const double x(const int32_t i) { return i * delta; }
inline const double y(const int32_t j) { return j * delta; }

const double u(const double x, const double y)
{
	return exp(
		-((x - xa) * (x - xa) + (y - ya) * (y - ya)) / (2.0 * sigma * sigma)
	) / (2.0 * numbers::pi * sigma * sigma);
}

int main()
{
	const auto Start = high_resolution_clock::now();
    
    filesystem::create_directory("plots");

	array<array<double, ny + 1>, nx + 1> psi = { 0 };

	fstream psiData("psi.dat", ios::in);
	for (int32_t ind = 0; ind < (nx + 1) * (ny + 1); ind++)
	{
		int32_t i, j;
		double pv;
		psiData >> i >> j >> pv;
		psi[i][j] = pv;
	}
	psiData.close();

    vector<array<double, ny + 1>> vx;
	vector<array<double, ny + 1>> vy;
    vx.reserve(nx + 1);
    vy.reserve(nx + 1);

    for (int32_t i = 1; i < nx; i++)
    {
        for (int32_t j = 1; j < ny; j++)
        {
            vx[i][j] = (psi[i][j + 1] - psi[i][j - 1]) / (2.0 * delta);
            vy[i][j] = -(psi[i + 1][j] - psi[i - 1][j]) / (2.0 * delta);
        }
    }

    for (int32_t i = I1; i <= I2; i++)
    {
        for (int32_t j = 0; j <= J1; j++)
        {
            vx[i][j] = 0.0;
            vy[i][j] = 0.0;
        }
    }

    for (int32_t i = 1; i < nx; i++)
    {
        vx[i][0] = 0.0;
        vy[i][ny] = 0.0;
    }

    for (int32_t j = 0; j <= ny; j++)
    {
        vx[0][j] = vx[1][j];
        vx[nx][j] = vx[nx - 1][j];
    }

    fstream f_vx("plots/vx.txt", ios::out);
    fstream f_vy("plots/vy.txt", ios::out);

    for (int32_t i = 0; i <= nx; i++)
    {
        for (int32_t j = 0; j <= ny; j++)
        {
            f_vx << vx[i][j] << ' ';
            f_vy << vy[i][j] << ' ';
        }
        f_vx << endl;
        f_vy << endl;
    }

    double vMax = 0;
    for (int32_t i = 0; i <= nx; i++)
    {
        for (int32_t j = 0; j <= ny; j++)
        {
            double vMag = sqrt(vx[i][j] * vx[i][j] + vy[i][j] * vy[i][j]);
            if (vMag > vMax)
                vMax = vMag;
        }
    }

    const double dt = delta / (4 * vMax);
    cout << "Vmax = " << vMax << " | dt = " << dt << endl;

    auto t = [dt](const int32_t it) { return dt * it; };
    const double tmax = t(IT_MAX);

    fstream f_grid_t("plots/gridT.txt", ios::out);
    for (int32_t it = 0; it < IT_MAX; it++)
        f_grid_t << t(it) << endl;

    array<array<double, ny + 1>, nx + 1> u0= { 0 };
    array<array<double, ny + 1>, nx + 1> u1= { 0 };

    constexpr double ds[] = { 0, 0.1 };
    for (double d : ds)
    {
        cout << "\nCalculating for D = " << d << endl;
        fstream fc(string("plots/c") + (d == 0 ? "0" : "0.1") + ".txt", ios::out);
        fstream fxSr(string("plots/xSr") + (d == 0 ? "0" : "0.1") + ".txt", ios::out);

        for (int32_t i = 0; i <= nx; i++)
        {
            for (int32_t j = 0; j <= ny; j++)
            {
                double uij = u(x(i), y(j));
                u0[i][j] = uij;
                u1[i][j] = uij;
            }
        }
        
        const double prefix = 1.0 / (1.0 + (2.0 * d * dt) / (delta * delta));
        for (int32_t it = 1; it <= IT_MAX; it++)
        {
            printf("\r%d", it);
            memcpy(&u1, &u0, sizeof(u0));

            for (int32_t k = 1; k <= 20; k++)
            {
                for (int32_t i = 0; i <= nx; i++)
                {
                    for (int32_t j = 1; j <= ny; j++)
                    {
                        if (I1 <= i && i <= I2 && 0 <= j && j <= J1)
                            continue;
                        constexpr double twodel = 2 * delta;
                        double eq0, eq1, eq2, eq3, eq4, eq5;
                        if (i == 0)
                        {
                            eq0 = (u0[i + 1][j] - u0[nx][j]) / twodel;
                            eq1 = (u1[i + 1][j] - u1[nx][j]) / twodel;
                            eq2 = (u0[i][j + 1] - u0[i][j - 1]) / twodel;
                            eq3 = (u1[i][j + 1] - u1[i][j - 1]) / twodel;
                            eq4 = (u0[i + 1][j] + u0[nx][j] + u0[i][j + 1] + u0[i][j - 1] - 4.0 * u0[i][j]) / (delta * delta);
                            eq5 = (u1[i + 1][j] + u1[nx][j] + u1[i][j + 1] + u1[i][j - 1]) / (delta * delta);
                        }
                        else if (i == nx)
                        {
                            eq0 = (u0[0][j] - u0[i - 1][j]) / twodel;
                            eq1 = (u1[0][j] - u1[i - 1][j]) / twodel;
                            eq2 = (u0[i][j + 1] - u0[i][j - 1]) / twodel;
                            eq3 = (u1[i][j + 1] - u1[i][j - 1]) / twodel;
                            eq4 = (u0[0][j] + u0[i - 1][j] + u0[i][j + 1] + u0[i][j - 1] - 4.0 * u0[i][j]) / (delta * delta);
                            eq5 = (u1[0][j] + u1[i - 1][j] + u1[i][j + 1] + u1[i][j - 1]) / (delta * delta);
                        }
                        else
                        {
                            eq0 = (u0[i + 1][j] - u0[i - 1][j]) / twodel;
                            eq1 = (u1[i + 1][j] - u1[i - 1][j]) / twodel;
                            eq2 = (u0[i][j + 1] - u0[i][j - 1]) / twodel;
                            eq3 = (u1[i][j + 1] - u1[i][j - 1]) / twodel;
                            eq4 = (u0[i + 1][j] + u0[i - 1][j] + u0[i][j + 1] + u0[i][j - 1] - 4.0 * u0[i][j]) / (delta * delta);
                            eq5 = (u1[i + 1][j] + u1[i - 1][j] + u1[i][j + 1] + u1[i][j - 1]) / (delta * delta);
                        }
                        u1[i][j] = prefix
                            * (u0[i][j]
                            - dt * vx[i][j] / 2.0 * (eq0 + eq1)
                            - dt * vy[i][j] / 2.0 * (eq2 + eq3)
                            + dt * d / 2.0 * (eq4 + eq5));
                    }
                }
            }
            memcpy(&u0, &u1, sizeof(u1));

            double cTemp = 0;
            for (int32_t i = 0; i <= nx; i++)
                for (int32_t j = 0; j <= ny; j++)
                    cTemp += u0[i][j] * delta * delta;
            fc << cTemp << endl;

            double xSrTemp = 0.0;
            for (int32_t i = 0; i <= nx; i++)
                for (int32_t j = 0; j <= ny; j++)
                    xSrTemp += x(i) * u0[i][j] * delta * delta;
            fxSr << xSrTemp << endl;

            for (int32_t k = 1; k <= 5; k++)
            {
		        if (abs(t(it) - (double)k * tmax / 5.0) < 1e-6)
                {
		            fstream f_u(string("plots/zad5_it") + to_string(k) + "_" + (d == 0.0 ? "0" : "0.1") + ".txt", ios::out);
                    for (int32_t i = 0; i <= nx; i++)
                    {
                        for (int32_t j = 0; j <= ny; j++)
                            f_u << u0[i][j] << " ";
                        f_u << endl;
                    }
                }
            }
        }
    }

	const auto End = high_resolution_clock::now();
	cout << endl << duration_cast<milliseconds>(End - Start).count() / 1000.0 << "s" << endl;

	return 0;
}
