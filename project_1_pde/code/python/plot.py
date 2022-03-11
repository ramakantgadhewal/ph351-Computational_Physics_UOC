import numpy as np
import matplotlib.pyplot as plt
import os

def main():
    # 1D Case
    data_path = "../cpp/data/"
    energy = np.loadtxt(data_path+"energy_data_1d.dat")
    field = np.loadtxt(data_path+"field_1d.dat")
    potential = np.loadtxt(data_path+"potential_1d.dat")
    source = np.loadtxt(data_path+"source_1d.dat")
    
    plt.plot(field)
    plt.show()

if __name__=="__main__":
    main()