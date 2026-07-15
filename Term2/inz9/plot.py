import numpy as np
import matplotlib.pyplot as plt

NX = 40
NY = 40
N = (NX + 1) * (NY + 1)
IT_VALUES = [100, 200, 500, 1000, 2000]

x = np.arange(0, 41)
y = np.arange(0, 41)

def plot(name, title):
	plt.figure()
	data = np.loadtxt("plots/" + name + '.txt').reshape((NX + 1, NY + 1))
	plt.pcolor(x, y, np.transpose(data), vmin=np.nanmin(data), vmax=np.nanmax(data), cmap="bwr", shading='auto')
	plt.colorbar()
	plt.title(title)
	plt.savefig("plots/" + name + '.png')

for it in IT_VALUES:
	plot('t_' + str(it), '$T(x,y)$ ($it = ' + str(it) + '$)')
	plot('dt_' + str(it), r'$\nabla^2T(x,y)$ ($it = ' + str(it) + '$)')
	
	# plt.figure()
	# t = np.loadtxt('t_' + str(it) + '.txt').reshape((NX + 1, NY + 1)).transpose()
	# plt.pcolor(x, y, np.transpose(t), vmin=np.nanmin(t), vmax=np.nanmax(t), shading='auto')
	# plt.colorbar()
	# plt.title('$T(x,y)$ ($it = ' + str(it) + '$)')
	# plt.savefig('t_' + str(it) + '.png')
	
	# plt.figure()
	# dt = np.loadtxt('dt_' + str(it) + '.txt').reshape((NX + 1, NY + 1)).transpose()
	# plt.pcolor(x, y, np.transpose(dt), vmin=np.nanmin(dt), vmax=np.nanmax(dt), shading='auto')
	# plt.colorbar()
	# plt.title(r'$\nabla^2T(x,y)$ ($it = ' + str(it) + '$)')
	# plt.savefig('dt_' + str(it) + '.png')
