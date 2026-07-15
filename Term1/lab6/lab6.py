N = 5
ITMax = 30

def licz_r(a, b, n, xj):
    b[n] = 0
    for k in range(n - 1, -1, -1):
        b[k] = a[k + 1] + xj * b[k + 1]
    return a[0] + xj * b[0]


wa = [240.0, -196.0, -92.0, 33.0, 14.0, 1.0]
wb = [0.0 for _ in range(N + 1)]
wc = [0.0 for _ in range(N + 1)]

with open("Wyniki.dat", "w") as w:
    w.write("--------------wartosc startowa x0 = 0 ----------------------------------------\n" \
               "--------------Współczynniki wielomianu a[n]: ---------------------------------\n\n")
    for i, ca in enumerate(wa, 1):
        w.write(f"a[{i}] = {ca:>4.0f}\n")
    w.write("\n")


    for L in range(1, N+1):
        n = N - L + 1
        w.write(f"--------------aktualny stopien wielomianu n=N-L+1={n} --------------------------\n\n")
        x0 = 0.0

        for i in range(1, ITMax + 1):
            Rj = licz_r(wa, wb, n, x0)
            Rjp = licz_r(wb, wc, n - 1, x0)

            x1 = x0 - Rj / Rjp

            w.write(f"L={L}\tit={i}\t\tx1={x1:>11.6f}\t\tR0={Rj:>11.6f}\t\tR0'={Rjp:>11.6f}\n")
            
            if abs(x1 - x0) < 1e-7:
                break
            x0 = x1
        
        for i, bv in enumerate(wb):
            wa[i] = bv

        w.write("------------------------------------------------------------------------------\n\n")


