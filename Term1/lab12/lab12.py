from math import *

fx = lambda x: log(x*x*x + 3 * x*x + x + 0.1) * sin(18 * x)

def Simpson(a, b, n, D, file_out):
    xj = lambda j, h: a + j * h

    for w in range(n + 1):
        N = 2 ** (w + 1)
        hw = (b - a) / N

        D[w][0] = 0
        for i in range(N // 2 - 1 + 1): 
            D[w][0] += hw / 3.0 * (fx(xj(2 * i, hw)) + 4 * fx(xj(2 * i + 1, hw)) + fx(xj(2 * i + 2, hw)))
        
    for w in range(1, n + 1):
        for k in range(1, w + 1):
            k4 = 4 ** k
            D[w][k] = (k4 * D[w][k - 1] - D[w - 1][k - 1]) / (k4 - 1)
    
    print("-------------------Simpson-------------------\n        D[w][0]     \t      D[w][w]", file=file_out)
    for i in range(n + 1):
        print(D[i][0], D[i][i], sep="\t", file=file_out)
    
    print("\n\n                 D[w][k]", file=file_out)
    for i in range(n + 1):
        for j in range(i + 1):
            print(D[i][j], end=" ", file=file_out)
        print(file=file_out)


def Milne(a, b, n, D, file_out):
    xj = lambda j, h: a + j * h

    for w in range(n + 1):
        N = 2 ** (w + 2)
        hw = (b - a) / N

        D[w][0] = 0
        for i in range(N // 4 - 1 + 1): 
            D[w][0] += 4.0 * hw / 90.0 * (
                7 * fx(xj(4 * i, hw)) +
                32 * fx(xj(4 * i + 1, hw)) +
                12 * fx(xj(4 * i + 2, hw)) +
                32 * fx(xj(4 * i + 3, hw)) +
                7 * fx(xj(4 * i + 4, hw))
            )
    
    for w in range(1, n + 1):
        for k in range(1, w + 1):
            k4 = 4 ** k
            D[w][k] = (k4 * D[w][k - 1] - D[w - 1][k - 1]) / (k4 - 1)
    
    print("-------------------Milne-------------------\n        D[w][0]     \t      D[w][w]", file=file_out)
    for i in range(n + 1):
        print(D[i][0], D[i][i], sep="\t", file=file_out)
    
    print("\n\n                 D[w][k]", file=file_out)
    for i in range(n + 1):
        for j in range(i + 1):
            print(D[i][j], end=" ", file=file_out)
        print(file=file_out)


def main():
    b = 1.0
    a = 0.0
    zn = 8
    D = [[0] * (zn + 1) for _ in range(zn + 1)]
    with open("simpson.dat", "w") as simpson_out:
        Simpson(a, b, zn, D.copy(), simpson_out)
    with open("milne.dat", "w") as milne_out:
        Milne(a, b, zn, D.copy(), milne_out)


if __name__ == '__main__':
    main()