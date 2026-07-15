#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <filesystem>

#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>

using namespace std;

constexpr uint32_t NX = 40;
constexpr uint32_t NY = 40;
constexpr uint32_t N = (NX + 1) * (NY + 1);
constexpr double DELTA = 1.0;
constexpr double DT = 1.0;
constexpr double TA = 40.0;
constexpr double TB = 0.0;
constexpr double TC = 30.0;
constexpr double TD = 0.0;
constexpr double KB = 0.1;
constexpr double KD = 0.6;
constexpr array<uint32_t, 5> IT_VALUES = { 100, 200, 500, 1000, 2000 };
constexpr uint32_t IT_MAX = IT_VALUES[4];

constexpr double DD = DT / (2.0 * DELTA * DELTA);

inline uint32_t toL(uint32_t i, uint32_t j) { return i + j * (NX + 1); }
inline uint32_t toI(uint32_t l) { return l - (l / (NX + 1)) * (NX + 1); }

using mat = vector<array<double, N>>;
using vec = array<double, N>;

gsl_matrix* LU(mat& a, gsl_permutation* perm)
{
    gsl_matrix* LU = gsl_matrix_alloc(N, N);
    memcpy(LU->data, a.data(), N * N * sizeof(double));

    int signum;
    gsl_linalg_LU_decomp(LU, perm, &signum);

    return LU;
}

int32_t main()
{
    cout << "Main Program Begins" << endl;

    mat a{}, b{};
    a.reserve(N); b.reserve(N);
    vec c{}, prevT{};
    vec t = []()
    {
        vec t{};
        for (int32_t l = 0; l < N; l++)
        {
            uint32_t i = toI(l);
            t[l] =
                i == 0 ? TA :
                i == NX ? TC :
                0.0;
        }
        return t;
    }();

    cout << "Main Initialization" << endl;

    for (int32_t i = 0; i <= NX; i++)
    {
        for (int32_t j = 0; j <= NY; j++)
        {
            uint32_t l = toL(i, j);
            if (i == 0 || i == NX)
            {
                a[l][l] = 1.0;
                b[l][l] = 1.0;
                c[l] = 0.0;
            }
            else if (1 <= i && i < NX && j == NY)
            {
                a[l][l - NX - 1] = -1.0 / (KB * DELTA);
                a[l][l] = 1.0 + 1.0 / (KB * DELTA);
                for (int32_t lj = 0; lj < N; lj++)
                {
                    b[l][lj] = 0.0;
                }
                c[l] = TB;
            }
            else if (1 <= i && i < NX && j == 0)
            {
                a[l][l + NX + 1] = -1.0 / (KD * DELTA);
                a[l][l] = 1.0 + 1.0 / (KD * DELTA);
                for (int32_t lj = 0; lj < N; lj++)
                {
                    b[l][lj] = 0.0;
                }
                c[l] = TD;
            }
            else
            {
                a[l][l] = -2.0 * DT / (DELTA * DELTA) - 1.0;
                b[l][l] = 2.0 * DT / (DELTA * DELTA) - 1.0;
                a[l][l - NX - 1] = DD;
                a[l][l + NX + 1] = DD;
                a[l][l - 1] = DD;
                a[l][l + 1] = DD;
                b[l][l - NX - 1] = -DD;
                b[l][l + NX + 1] = -DD;
                b[l][l - 1] = -DD;
                b[l][l + 1] = -DD;
            }
        }
    }

    cout << "Starting Decomposition" << endl;

    gsl_permutation* perm = gsl_permutation_alloc(N);

    gsl_vector* gslT = gsl_vector_alloc(N);
    memcpy(gslT->data, t.data(), N * sizeof(double));
    
    gsl_matrix* gslB = gsl_matrix_alloc(N, N);
    memcpy(gslB->data, b.data(), N * N * sizeof(double));
    
    gsl_vector* gslC = gsl_vector_alloc(N);
    memcpy(gslC->data, c.data(), N * sizeof(double));
    
    gsl_vector* gslD = gsl_vector_alloc(N);

    gsl_matrix* lu = LU(a, perm);

    cout << "Ploting" << endl;

    filesystem::create_directory("plots");
    for (uint32_t it = 0; it <= IT_MAX; it++)
    {
        bool inIT = find(IT_VALUES.begin(), IT_VALUES.end(), it) != end(IT_VALUES);
        if (inIT)
            memcpy(prevT.data(), gslT->data, N * sizeof(double));

        // memcpy(gslD->data, gslC->data, (N) * sizeof(double));
        gsl_vector_set_zero(gslD);
        gsl_blas_dgemv(CblasNoTrans, 1.0, gslB, gslT, 1.0, gslD);
        gsl_blas_daxpy (1.0, gslC, gslD);

        gsl_linalg_LU_solve(lu, perm, gslD, gslT);

        if (inIT)
        {
            fstream fT = fstream(string("plots/t_") + to_string(it) + ".txt", ios::out);
            fstream fDt = fstream(string("plots/dt_") + to_string(it) + ".txt", ios::out);

            for (int32_t i = 0; i <= NX; i++)
            {
                for (int32_t j = 0; j <= NY; j++)
                {
                    fT << gsl_vector_get(gslT, toL(i, j)) << endl;
                    fDt << ((gsl_vector_get(gslT, toL(i, j)) - prevT[toL(i, j)]) / DT) << endl;
                }
            }
        }
    }

    gsl_matrix_free(lu);
    gsl_vector_free(gslD);
    gsl_vector_free(gslC);
    gsl_matrix_free(gslB);
    gsl_vector_free(gslT);
    gsl_permutation_free(perm);
}
