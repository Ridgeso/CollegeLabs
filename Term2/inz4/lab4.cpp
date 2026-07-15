#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <execution>
#include <algorithm>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

#define cd constexpr double

// Constants
constexpr int32_t nx = 151;
constexpr int32_t ny = 101;
cd epsilon = 1.0;
cd delta = 0.1;
cd V1 = 10;
cd V2 = 0;
cd xmax = delta * nx;
cd ymax = delta * ny;
cd sigmax = 0.1 * xmax;
cd sigmay = 0.1 * ymax;
cd WG[] = { 0.6, 1.0 };
cd WL[] = { 1.0, 1.4, 1.8, 1.9 };
cd V0 = 0;
cd TOL = 1e-8;

static double p[nx][ny];
void CalcP()
{
	for (int_fast32_t i = 0; i < nx; i++)
	{
		const double x = i * delta;
		for (int_fast32_t j = 0; j < ny; j++)
		{
			const double y = j * delta;

			const double eq = -pow((y - 0.5 * ymax) / sigmay, 2.0);
			const double eq1 = -pow((x - 0.35 * xmax) / sigmax, 2.0);
			const double eq2 = -pow((x - 0.65 * xmax) / sigmax, 2.0);
			p[i][j] = exp(eq1 + eq) + -exp(eq2 + eq);
		}
	}
}

double CalcS(const double V[nx][ny])
{
	double S = 0;
	for (int_fast32_t i = 0; i < nx - 1; i++)
	{
		for (int_fast32_t j = 0; j < ny - 1; j++)
		{
			double eq1 = 0.5 * (pow((V[i + 1][j] - V[i][j]) / delta, 2));
			double eq2 = 0.5 * (pow((V[i][j + 1] - V[i][j]) / delta, 2));
			S += delta * delta * (eq1 + eq2 - p[i][j] * V[i][j]);
		}
	}
	return S;
}

bool Stop(const double Sl, const double S)
{
	return fabs((S - Sl) / Sl) < TOL;
}

struct RelData
{
	vector<double> S;
	double V[nx][ny] = { { V0 } };
	double Vs[nx][ny] = { { V0 } };
	double err[nx][ny] = { { 0 } };
};

void RelaksacjaGlobalna(int32_t wgI, RelData& data)
{
	data.S.reserve(25000);
	data.S.push_back(0);

	for (int_fast32_t i = 0; i < nx; i++)
	{
		data.V[i][0] = V1;
		data.Vs[i][0] = V1;
	}
	
	while (true)
	{
		for (int_fast32_t i = 1; i < nx - 1; i++)
		{
			for (int_fast32_t j = 1; j < ny - 1; j++)
			{
				double cashed = data.Vs[i + 1][j]
					+ data.Vs[i - 1][j]
					+ data.Vs[i][j + 1]
					+ data.Vs[i][j - 1];
				data.V[i][j] = 0.25 * (cashed + delta * delta * p[i][j] / epsilon);
			}
		}
		for (int_fast32_t j = 1; j < ny - 1; j++)
		{
			data.V[0][j] = data.V[1][j];
			data.V[nx - 1][j] = data.V[nx - 2][j];
		}
		for (int_fast32_t i = 0; i < nx; i++)
			for (int_fast32_t j = 0; j < ny; j++)
				data.Vs[i][j] = (1 - WG[wgI]) * data.Vs[i][j] + WG[wgI] * data.V[i][j];
		data.S.push_back(CalcS(data.Vs));
		if (Stop(data.S[data.S.size() - 2], data.S[data.S.size() - 1]))
			break;
	}

	for (int_fast32_t i = 1; i < nx - 1; i++)
		for (int_fast32_t j = 1; j < ny - 1; j++)
			data.err[i][j] =
			(data.V[i + 1][j] - 2.0 * data.V[i][j] + data.V[i - 1][j]) / (delta * delta)
			+ (data.V[i][j + 1] - 2.0 * data.V[i][j] + data.V[i][j - 1]) / (delta * delta)
			+ p[i][j] / epsilon;
}

vector<double> RelaksacjaLokalna(int32_t wlI)
{
	vector<double> S;
	S.reserve(1000);
	S.push_back(0);

	double V[nx][ny] = { { V0 } };
	for (int_fast32_t i = 0; i < nx; i++)
		V[i][0] = V1;
	
	while (true)
	{
		for (int_fast32_t i = 1; i < nx - 1; i++)
		{
			for (int_fast32_t j = 1; j < ny - 1; j++)
			{
				double cashed = V[i + 1][j]
					+ V[i - 1][j]
					+ V[i][j + 1]
					+ V[i][j - 1];
				V[i][j] = (1.0 - WL[wlI]) * V[i][j] + WL[wlI] * 0.25 * (cashed + delta * delta * p[i][j] / epsilon);
			}
		}
		for (int_fast32_t j = 1; j < ny - 1; j++)
		{
			V[0][j] = V[1][j];
			V[nx - 1][j] = V[nx - 2][j];
		}
		S.push_back(CalcS(V));
		if (Stop(S[S.size() - 2], S[S.size() - 1]))
			break;
	}
	return S;
}

int main()
{
	auto globClock = high_resolution_clock::now();

	const vector<int32_t> rlIt = { 0, 1, 2, 3 };
	CalcP();

	{
		static RelData globData[2];

		const auto clock = high_resolution_clock::now();
		for_each(execution::par, rlIt.begin(), rlIt.end() - 2, [](int32_t i)
		{
			RelaksacjaGlobalna(i, globData[i]);
		});
		const auto clockEnd = high_resolution_clock::now();
		cout << "Glob: " << duration_cast<milliseconds>(clockEnd - clock).count() / 1000 << endl;

		fstream globIter("globIter.txt", ios::out);
		fstream globPot("globPot.txt", ios::out);
		fstream globErr("globErr.txt", ios::out);
		for (const auto& data : globData)
		{
			for (const auto d : data.S)
				globIter << d << " ";
			globIter << endl;

			for (int_fast32_t i = 0; i < nx; i++)
			{
				for (int_fast32_t j = 0; j < ny; j++)
				{
					globPot << data.V[i][j] << " ";
					globErr << data.err[i][j] << " ";
				}
				globPot << endl;
				globErr << endl;
			}
			globPot << endl;
			globErr << endl;
		}
		globIter.close();
		globPot.close();
		globErr.close();
	}

	{
		vector<double> Ses[4];

		const auto clock = high_resolution_clock::now();
		for_each(execution::par, rlIt.begin(), rlIt.end(), [&Ses](int32_t i)
		{
			Ses[i] = RelaksacjaLokalna(i);
		});
		const auto clockEnd = high_resolution_clock::now();
		cout << "Loc: " << duration_cast<milliseconds>(clockEnd - clock).count() / 1000 << endl;
	
		fstream locIter("locIter.txt", ios::out);
		for (const auto& S : Ses)
		{
			for (const auto d : S)
				locIter << d << " ";
			locIter << endl;
		}
		locIter.close();
	}

	auto elapesTime = high_resolution_clock::now() - globClock;
	cout << "Elapes Time: " << duration_cast<milliseconds>(elapesTime).count() / 1000 << endl;
	return 0;
}