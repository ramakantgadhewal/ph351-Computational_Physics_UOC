import numpy as np
import matplotlib.pyplot as plt
import os
import sys
sys.path.insert(0,'../')
from universal_code.python.saveFig import saveFig

CMAP = 'plasma'

def _plot(D):
    data_path = f"data_{D}d/"
    energy = np.loadtxt(data_path+f"energy_data_{D}d.dat")
    potential = np.loadtxt(data_path+f"potential_{D}d.dat")
    source = np.loadtxt(data_path+f"source_{D}d.dat")
    
    if D==1:
        field = np.loadtxt(data_path+f"field_{D}d.dat")
        print("Energy assymptote: ", energy[-1])
        x = np.linspace(0,1,100)
        
        _, ax1 = plt.subplots()
        ax1.plot(energy, label='Numerical Solution')
        ax1.axhline(-0.64286, linestyle='--', color='r', label='Analytical Solution')
        ax1.set_xlabel("Steps")
        ax1.set_ylabel("Energy")
        ax1.legend()
        saveFig(fig_id="energy_1d_plot", destination="data_1d/")
        
        _, ax2 = plt.subplots()
        ax2.plot(x, field, label='Numerical Solution')
        ax2.set_xlabel("x")
        ax2.set_ylabel("Electric Field")
        saveFig(fig_id="field_1d_plot", destination="data_1d/")
        
        _, ax3 = plt.subplots()
        ax3.plot(x, potential, label='Numerical Solution')
        ax3.plot(x, x*(1-x**3), '--', color='r', label='Analytical Solution')
        ax3.set_xlabel("x")
        ax3.set_ylabel("Potential")
        ax3.legend()
        saveFig(fig_id="potential_1d_plot", destination="data_1d/")
        
        _, ax4 = plt.subplots()
        ax4.plot(x, source)
        ax4.set_xlabel("x")
        ax4.set_ylabel("Source")
        saveFig(fig_id="source_1d_plot", destination="data_1d/")
    
    elif D==2:
        fieldx = np.loadtxt(data_path+f"fieldx_{D}d.dat")
        fieldy = np.loadtxt(data_path+f"fieldy_{D}d.dat")
        
        print("Energy assymptote: ", energy[-1])
        _, ax1 = plt.subplots()
        ax1.plot(energy)
        ax1.set_xlabel("Steps")
        ax1.set_ylabel("Energy")
        saveFig(fig_id="energy_2d_plot", destination="data_2d/")
        
        fig2, ax2 = plt.subplots()
        plot2 = ax2.pcolormesh(fieldx, cmap=CMAP)
        ax2.set_xlabel("x")
        ax2.set_ylabel("y")
        fig2.colorbar(plot2)
        saveFig(fig_id="fieldx_2d_plot", destination="data_2d/")
        
        fig3, ax3 = plt.subplots()
        plot3 = ax3.pcolormesh(fieldy, cmap=CMAP)
        ax3.set_xlabel("x")
        ax3.set_ylabel("y")
        fig3.colorbar(plot3)
        saveFig(fig_id="fieldy_2d_plot", destination="data_2d/")
        
        fig4, ax4 = plt.subplots()
        plot4 = ax4.pcolormesh(potential, cmap=CMAP)
        ax4.set_xlabel("x")
        ax4.set_ylabel("y")
        fig4.colorbar(plot4)
        saveFig(fig_id="potential_2d_plot", destination="data_2d/")
        
        fig5, ax5 = plt.subplots()
        plot5 = ax5.pcolormesh(source, cmap=CMAP)
        ax5.set_xlabel("x")
        ax5.set_ylabel("y")
        fig5.colorbar(plot5)
        saveFig(fig_id="source_2d_plot", destination="data_2d/")
        
        fig6, ax6 = plt.subplots()
        x = np.linspace(-5, 5, 119)
        y = np.linspace(-5, 5, 119)
        color = 2 * np.log(np.hypot(fieldx, fieldy))
        plot6 = ax6.streamplot(x, y, fieldx, fieldy, color=color, cmap=CMAP,\
            linewidth=2, density=3, arrowstyle='->', arrowsize=1.5)
        ax6.set_xlabel("x")
        ax6.set_ylabel("y")
        cbar = fig6.colorbar(plot6.lines, ax=ax6)
        saveFig(fig_id="field_streamplot", destination="data_2d/")

def main():
    # 1D Case
    _plot(1)
    print()
    # 2D Case
    _plot(2)
    
if __name__=="__main__":
    main()