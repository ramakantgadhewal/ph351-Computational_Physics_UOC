import numpy as np
import matplotlib.pyplot as plt

data_path = f"build/data/"
s = np.loadtxt(data_path+f"spin.dat")
init_s = np.loadtxt(data_path+f"init_spin.dat")
_s = np.zeros(s.shape)

for i in range(len(s)):
    for j in range(len(s)):
        if init_s[i,j]>0: _s[i,j] = 1
        else: _s[i,j] = 0

plt.imshow(_s)
plt.title('Initial Spins')
plt.show()

for i in range(len(s)):
    for j in range(len(s)):
        if s[i,j]>0: _s[i,j] = 1
        else: _s[i,j] = 0

plt.imshow(_s)
plt.title('Evolved Spins')
plt.show()