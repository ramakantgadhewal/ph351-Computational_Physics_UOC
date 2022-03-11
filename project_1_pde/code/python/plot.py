import numpy as np
import matplotlib.pyplot as plt
import os
import sys
sys.path.insert(0,'../../../')
from universal_code.src.python.saveFig import saveFig

def main():
    # 1D Case
    data_path = "../cpp/data/"
    energy = np.loadtxt(data_path+"energy_data_1d.dat")
    field = np.loadtxt(data_path+"field_1d.dat")
    potential = np.loadtxt(data_path+"potential_1d.dat")
    source = np.loadtxt(data_path+"source_1d.dat")
    
    _, ax1 = plt.subplots()
    ax1.plot(energy)
    ax1.set_xlabel("Steps")
    ax1.set_ylabel("Energy")
    # plt.title("Energy of the system")
    saveFig(fig_id="energy_1d_plot", destination="data/")
    
    _, ax2 = plt.subplots()
    ax2.plot(field)
    ax2.set_xlabel("N")
    ax2.set_ylabel("Electric Field")
    # plt.title("Energy of the system")
    saveFig(fig_id="field_1d_plot", destination="data/")
    
    _, ax3 = plt.subplots()
    ax3.plot(potential)
    ax3.set_xlabel("N")
    ax3.set_ylabel("Potential")
    # plt.title("Energy of the system")
    saveFig(fig_id="potential_1d_plot", destination="data/")
    
    _, ax4 = plt.subplots()
    ax4.plot(source)
    ax4.set_xlabel("N")
    ax4.set_ylabel("Source")
    # plt.title("Energy of the system")
    saveFig(fig_id="source_1d_plot", destination="data/")
    
if __name__=="__main__":
    main()