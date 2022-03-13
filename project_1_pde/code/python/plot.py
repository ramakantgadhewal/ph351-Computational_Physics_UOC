import numpy as np
import matplotlib.pyplot as plt
import os
import sys
sys.path.insert(0,'../')
from universal_code.python.saveFig import saveFig

def _plot(D):
    data_path = f"data_{D}d/"
    energy = np.loadtxt(data_path+f"energy_data_{D}d.dat")
    potential = np.loadtxt(data_path+f"potential_{D}d.dat")
    source = np.loadtxt(data_path+f"source_{D}d.dat")
    
    if D==1:
        field = np.loadtxt(data_path+f"field_{D}d.dat")
        
        _, ax1 = plt.subplots()
        ax1.plot(energy)
        ax1.set_xlabel("Steps")
        ax1.set_ylabel("Energy")
        # plt.title("Energy of the system")
        saveFig(fig_id="energy_1d_plot", destination="data_1d/")
        
        _, ax2 = plt.subplots()
        ax2.plot(field)
        ax2.set_xlabel("N")
        ax2.set_ylabel("Electric Field")
        # plt.title("Energy of the system")
        saveFig(fig_id="field_1d_plot", destination="data_1d/")
        
        _, ax3 = plt.subplots()
        ax3.plot(potential)
        ax3.set_xlabel("N")
        ax3.set_ylabel("Potential")
        # plt.title("Energy of the system")
        saveFig(fig_id="potential_1d_plot", destination="data_1d/")
        
        _, ax4 = plt.subplots()
        ax4.plot(source)
        ax4.set_xlabel("N")
        ax4.set_ylabel("Source")
        # plt.title("Energy of the system")
        saveFig(fig_id="source_1d_plot", destination="data_1d/")
    
    elif D==2:
        fieldx = np.loadtxt(data_path+f"fieldx_{D}d.dat")
        fieldy = np.loadtxt(data_path+f"fieldy_{D}d.dat")
        
        _, ax1 = plt.subplots()
        ax1.plot(energy)
        ax1.set_xlabel("Steps")
        ax1.set_ylabel("Energy")
        ax1.set_title("Energy of the system")
        saveFig(fig_id="energy_2d_plot", destination="data_2d/")
        
        fig2, ax2 = plt.subplots()
        plot2 = ax2.pcolormesh(fieldx)
        ax2.set_xlabel("x")
        ax2.set_ylabel("y")
        ax2.set_title("ELectric Field - x component of the system")
        fig2.colorbar(plot2)
        saveFig(fig_id="fieldx_2d_plot", destination="data_2d/")
        
        fig3, ax3 = plt.subplots()
        plot3 = ax3.pcolormesh(fieldy)
        ax3.set_xlabel("x")
        ax3.set_ylabel("y")
        ax3.set_title("ELectric Field - y component of the system")
        fig3.colorbar(plot3)
        saveFig(fig_id="fieldy_2d_plot", destination="data_2d/")
        
        fig4, ax4 = plt.subplots()
        plot4 = ax4.pcolormesh(potential)
        ax4.set_xlabel("x")
        ax4.set_ylabel("y")
        ax4.set_title("Potential Energy of the system")
        fig4.colorbar(plot4)
        saveFig(fig_id="potential_2d_plot", destination="data_2d/")
        
        fig5, ax5 = plt.subplots()
        plot5 = ax5.pcolormesh(source)
        ax5.set_xlabel("x")
        ax5.set_ylabel("y")
        ax5.set_title("Source Field of the system")
        fig5.colorbar(plot5)
        saveFig(fig_id="source_2d_plot", destination="data_2d/")

def main():
    # 1D Case
    _plot(1)
    print()
    # 2D Case
    _plot(2)
    
if __name__=="__main__":
    main()