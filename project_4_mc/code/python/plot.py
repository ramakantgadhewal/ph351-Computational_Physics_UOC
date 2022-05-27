import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import os

data_path = f"build/data/"
init_s = np.loadtxt(data_path+f"init_spin.dat")

def prepareS(s):
    _s = np.zeros(s.shape)
    for i in range(len(s)):
        for j in range(len(s)):
            if s[i,j]>0: _s[i,j] = 1
            else: _s[i,j] = 0
    return _s

fig = plt.figure()
ax = fig.add_subplot()
s = []
s.append([ax.imshow(prepareS(init_s), animated=True, cmap="gray")])
for i in range(100, 10000, 100):
    im = ax.imshow(prepareS(np.loadtxt(data_path+f"spin_{i}.dat")), animated=True, cmap="gray")
    s.append([im])
ani = animation.ArtistAnimation(fig, s, interval=20, blit=True,
                                repeat_delay=1000)
ax.set_title('Evolved Spins')
ani.save(data_path+"ising.gif")