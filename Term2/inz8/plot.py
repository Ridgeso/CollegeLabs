import numpy as np
import matplotlib.pyplot as plt

plots = "plots/"

nx = 400
ny = 90
delta = 0.1

x = np.linspace(0, nx * delta, nx + 1)
y = np.linspace(0, ny * delta, ny + 1)

for vs in ['vx', 'vy']:
    plt.figure()

    v = np.loadtxt(plots + vs + '.txt').reshape((401, 91))
    plt.pcolor(x, y, np.transpose(v), vmin=np.nanmin(v), vmax=np.nanmax(v), shading='auto')
    plt.colorbar()

    plt.title('$'+ vs +'(x,y)$')

    plt.savefig(plots + vs + '.png')

plt.figure()

t = np.loadtxt(plots + 'gridT.txt')
y1 = np.loadtxt(plots + 'c0.txt')
y2 = np.loadtxt(plots + 'c0.1.txt')

plt.plot(t, y1, label='$c$, $D=0$')
plt.plot(t, y2, label='$c$, $D=0.1$')

plt.legend()
plt.title('$c(t_n)$')
plt.savefig(plots + 'ct.png')
plt.figure()

y3 = np.loadtxt(plots + 'xSr0.txt')
y4 = np.loadtxt(plots + 'xSr0.1.txt')

plt.plot(t, y3, label='$x_sr$, $D=0$')
plt.plot(t, y4, label='$x_sr$, $D=0.1$')

plt.legend()
plt.title('$x_sr(t_n)$')

plt.savefig(plots + 'sr.png')

for D in [0, 0.1]:
    for k in [1, 2, 3, 4, 5]:

        plt.figure()

        u = np.loadtxt(plots + 'zad5_it' + str(k) + '_' + str(D) + '.txt').reshape((401, 91)).transpose()
        if D == 0:
            plt.pcolor(x, y, u, vmin=0, vmax=20, shading='auto')
        else:
            plt.pcolor(x, y, u, vmin=np.nanmin(u), vmax=np.nanmax(u), shading='auto')
        plt.colorbar()

        plt.title('$u(x,y)$ ($D = ' + str(D) + '$) ($k = ' + str(k) + '$)')

        plt.savefig(plots + 'u_' + str(D) + '_' + str(k) + '.png')