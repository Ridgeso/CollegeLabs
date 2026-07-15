from math import exp as exp, cos as cos, pi as pi

N = [5, 10, 15, 20]
x_range = [-5.0, 5.0]
f = lambda x: exp(-pow(x, 2.0))


def lagrange(xes, yes, x):
    W = 0.0
    for j, y in enumerate(yes):
        s = 1.0
        for k, xk in enumerate(xes):
            if k == j:
                continue
            s *= (x - xk) / (xes[j] - xk)
        W += y * s
    return W

def opt_lag(m, n):
    return ((x_range[1] - x_range[0]) * cos(pi * (2 * m + 1) / (2 * n + 2)) + (x_range[1] + x_range[0])) / 2.0


with open("zad_1.dat", "w") as output1:
    with open("zad_2.dat", "w") as output2:
        for n in N:
            h = (x_range[1] - x_range[0]) / n
            xm1 = [x_range[0] + h * i for i in range(n + 1)]
            ym1 = [f(x) for x in xm1]
            
            xm2 = [opt_lag(m, n) for m in range(n + 1)]
            ym2 = [f(x) for x in xm2]
            
            point_count = 200
            point_step = (x_range[1] - x_range[0]) / point_count
            
            Wn1 = [lagrange(xm1, ym1, x_range[0] + x * point_step) for x in range(point_count)]
            Wn2 = [lagrange(xm2, ym2, x_range[0] + x * point_step) for x in range(point_count)]


            for x, (w1, w2) in enumerate(zip(Wn1, Wn2)):
                xc = x_range[0] + x * point_step
                output1.write(f"{xc} {w1}\n")
                output2.write(f"{xc} {w2}\n")
            
            output1.write("\n\n")
            output2.write("\n\n")
