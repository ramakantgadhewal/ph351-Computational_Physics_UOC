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
    pos = np.loadtxt(data_path+f'position.dat').T
    x = np.arange(0, pos.shape[0])
    m = pos.mean(axis=1)
    ci = 1.95 * np.std(pos)/np.sqrt(len(pos))

    fig, ax = plt.subplots()
    ax.plot(x, m)
    ax.fill_between(x, (m - ci), (m + ci), color='b', alpha=.1)
    plt.show()
    
def main():
    plot()
    return 0
    
if __name__=="__main__":
    main()