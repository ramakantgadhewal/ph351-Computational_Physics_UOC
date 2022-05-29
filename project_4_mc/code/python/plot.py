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

E = []
E2 = []
M = []
M2 = []
C = []
CHI = []
for i, (subpath, l) in enumerate((zip(data_subpaths, lrange))):
    energy = glob.glob(subpath+"/energy_[!squared]*.dat")
    energy_squared = glob.glob(subpath+"/energy_*.dat")
    energy_squared = list(set(energy_squared).symmetric_difference(set(energy)))
    magnetic_moment = glob.glob(subpath+"/magnetic_moment_[!squared]*.dat")
    magnetic_moment_squared = glob.glob(subpath+"/magnetic_moment_*.dat")
    magnetic_moment_squared = list(set(magnetic_moment_squared).symmetric_difference(set(magnetic_moment)))
    E.append(np.loadtxt(energy[0]))
    E2.append(np.loadtxt(energy_squared[0]))
    M.append(np.loadtxt(magnetic_moment[0]))
    M2.append(np.loadtxt(magnetic_moment_squared[0]))
    C.append(1/temp[i]**2*(np.loadtxt(energy_squared[0])-np.loadtxt(energy[0])))
    CHI.append(1/temp[i]**2*(np.loadtxt(magnetic_moment_squared[0])-np.loadtxt(magnetic_moment[0])))
    
plots = [E, E2, M, M2, C, CHI]
names = ["energy", "energy_squared", "magnetic_moment", "magnetic_moment_squared", "specific_heat", "chi"]
ax_names = [r"$E/L^2$", r"$E^2/L^2$", r"$M/L^2$", r"$M^2/L^2$", r"C", r"$\chi$"]
for p, name, ax_name in zip(plots, names, ax_names):
    fig, ax = plt.subplots()
    for k, l in zip(p, lrange):
        ax.scatter(temp, k, label=f"L={l}", alpha=0.7)
        ax.set_xlabel("T")
        ax.set_ylabel(ax_name)
    ax.legend()
    PROJECT_ROOT_DIR = data_path
    IMAGES_PATH = os.path.join(PROJECT_ROOT_DIR, "images")
    os.makedirs(IMAGES_PATH, exist_ok=True)
    path = os.path.join(IMAGES_PATH, name + "." + "png")
    print("Saving figure", name)
    plt.savefig(path, format="png", dpi=300)
    
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