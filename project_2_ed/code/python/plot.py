import numpy as np
import matplotlib.pyplot as plt
import os
import sys
sys.path.insert(0,'../')
from universal_code.python.saveFig import saveFig

CMAP = 'plasma'
MAXT = 100
N = 100

def plot():
    data_path = f"data/"
    yreal = np.loadtxt(data_path+f"YR.dat")
    yimaginary = np.loadtxt(data_path+f"YI.dat")
    
    probability = np.abs(yreal)**2+np.abs(yimaginary)**2
    X, T = np.meshgrid(np.linspace(-1,1,N), range(MAXT), indexing='ij')
    
    fig1, ax1 = plt.subplots(figsize=(12,8))
    plot1 = ax1.pcolormesh(T, X, probability, cmap=CMAP, label='Numerical Solution')
    ax1.set_xlabel("t")
    ax1.set_ylabel("n")
    fig1.colorbar(plot1)
    ax1.set_title("Time Evolution of Probability")
    saveFig(fig_id="time_evol_plot", destination="data/")
    
def main():
    plot()
    return 0
    
if __name__=="__main__":
    main()