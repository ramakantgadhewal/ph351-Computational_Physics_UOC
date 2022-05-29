import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import os
import glob
import sys
sys.path.insert(0,'../')
from universal_code.python.saveFig import saveFig

lrange = list(range(5,11))
temp = np.linspace(1, 10, 50)
data_path = f"data/"
data_subpaths = [f"data/data_{i}" for i in lrange]

def prepareS(s):
    _s = np.zeros(s.shape)
    for i in range(len(s)):
        for j in range(len(s)):
            if s[i,j]>0: _s[i,j] = 1
            else: _s[i,j] = 0
    return _s

fig, ax = plt.subplots()
for i, (subpath, l) in enumerate((zip(data_subpaths, lrange))):
    energy = glob.glob(subpath+"/energy_[!squared]*.dat")
    energy_squared = glob.glob(subpath+"/energy_*.dat")
    energy_squared = list(set(energy_squared).symmetric_difference(set(energy)))
    magnetic_moment = glob.glob(subpath+"/magnetic_moment_[!squared]*.dat")
    magnetic_moment_squared = glob.glob(subpath+"/magnetic_moment_*.dat")
    magnetic_moment_squared = list(set(magnetic_moment_squared).symmetric_difference(set(magnetic_moment)))
    e = np.loadtxt(energy[0])
    e2 = np.loadtxt(energy_squared[0])
    m = np.loadtxt(magnetic_moment[0])
    m2 = np.loadtxt(magnetic_moment_squared[0])
    c = 1/temp[i]**2*(e2-e)
    chi = 1/temp[i]**2*(m2-m)
    ax.scatter(temp, e, label=f"L={l}", alpha=0.6)
ax.legend()
plt.show()
    # fig = plt.figure()
    # ax = fig.add_subplot()
    # s = []
    # s.append([ax.imshow(prepareS(init_s), animated=True, cmap="gray")])
    # for i in range(100, 10000, 100):
    #     im = ax.imshow(prepareS(np.loadtxt(data_path+f"spin_{i}.dat")), animated=True, cmap="gray")
    #     s.append([im])
    # ani = animation.ArtistAnimation(fig, s, interval=20, blit=True,
    #                                 repeat_delay=1000)
    # ax.set_title('Evolved Spins')
    # PROJECT_ROOT_DIR = data_path
    # IMAGES_PATH = os.path.join(PROJECT_ROOT_DIR, "images")
    # os.makedirs(IMAGES_PATH, exist_ok=True)
    # path = os.path.join(IMAGES_PATH, "ising_animation" + "." + "gif")
    # print("Saving figure", "ising_animation")
    # ani.save(path)