import numpy as np
import matplotlib.pyplot as plt
import os
import sys
sys.path.insert(0,'../')
from universal_code.python.saveFig import saveFig

CMAP = 'plasma'
MAXT = 100
N = 50

def plot():
    data_path = f"data/"
    pos = np.loadtxt(data_path+f"position.dat").T
    k = np.loadtxt(data_path+f"kinetic.dat")
    u = np.loadtxt(data_path+f"potential.dat")
    x = np.linspace(0, 100, pos.shape[0])
    m = pos.mean(axis=1)
    ci = 1.95 * np.std(pos)/np.sqrt(len(x))

    fig1, ax1 = plt.subplots()
    ax1.plot(x, m)
    ax1.fill_between(x, (m - ci), (m + ci), color='b', alpha=.1)
    plt.show()

    fig2, ax2 = plt.subplots()
    ax2.plot(x, k)
    ax2.plot(x, u)
    plt.show()
    
def main():
    plot()
    return 0
    
if __name__=="__main__":
    main()