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
    probability = np.loadtxt(data_path+f'P.dat')
    mean_x = np.loadtxt(data_path+f'mean_x.dat')
    var = np.loadtxt(data_path+'variance.dat')
    initial_condition = np.loadtxt(data_path+'init.dat')
    potential = np.loadtxt(data_path+'V.dat')

    x = np.linspace(0,N,N)
    X, T = np.meshgrid(x, range(MAXT), indexing='ij')
    fig1, ax1 = plt.subplots(figsize=(12,8))
    plot1 = ax1.pcolormesh(T, X, probability, cmap=CMAP, shading='auto', label='Numerical Solution')
    ax1.set_xlabel("t")
    ax1.set_ylabel("site")
    fig1.colorbar(plot1)
    ax1.set_title("Time Evolution of Probability")
    saveFig(fig_id="time_evol_plot", destination="data/")

    _, ax2 = plt.subplots()
    ax2.plot(x, potential)
    ax2.set_title('Potential')
    ax2.set_xlabel('x')
    ax2.set_ylabel('V')
    saveFig(fig_id='Potenial', destination="data/")

    _, ax3 = plt.subplots()
    ax3.plot(x,initial_condition)
    ax3.set_title('Initial Wavefunction')
    ax3.set_xlabel('x')
    ax3.set_ylabel('$\psi_{0}(x)$')
    saveFig(fig_id='Initial_wavefunction', destination="data/")

    _, ax4 = plt.subplots()
    ax4.plot(range(100), mean_x)
    ax4.set_ylabel(r'$\langle x \rangle$')
    ax4.set_xlabel('t')
    ax4.set_title('Mean value of position')
    saveFig(fig_id='mean_value_x', destination="data/")

    _, ax5 = plt.subplots()
    ax5.plot(range(100), var)
    ax5.set_xlabel('t')
    ax5.set_ylabel('$\Delta$x')
    ax5.set_title('Uncertainty of position')
    saveFig(fig_id='uncertainty_of_x', destination="data/")
    
def main():
    plot()
    return 0
    
if __name__=="__main__":
    main()