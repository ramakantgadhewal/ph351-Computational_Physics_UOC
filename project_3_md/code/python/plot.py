import numpy as np
import matplotlib.pyplot as plt
import os
import sys
import pandas as pd
sys.path.insert(0,'../')
from universal_code.python.saveFig import saveFig

def plot():
    data_path = f"data/"
    pos = np.loadtxt(data_path+f"position.dat").T
    vel = np.loadtxt(data_path+f"velocity.dat").T
    k = np.loadtxt(data_path+f"kinetic.dat")
    u = np.loadtxt(data_path+f"potential.dat")
    total = np.loadtxt(data_path+f"total.dat")
    mepp = np.loadtxt(data_path+f"mepp.dat")
    simT = np.loadtxt(data_path+f"sim_temp.dat")
    x = np.linspace(0, 1000, pos.shape[0])
    m = vel.mean(axis=1)
    ci_pos = 1.96 * np.std(pos)/np.sqrt(len(x))

    fig1, ax1 = plt.subplots()
    ax1.plot(x, m)
    ax1.fill_between(x, (m - ci_pos), (m + ci_pos), alpha=.5, color='b')
    plt.show()

    w = 500
    k_roll_ts = pd.Series(k)
    k_roll_ts_mean = k_roll_ts.rolling(window=w).mean()
    ci_k = 1.96 * k_roll_ts.rolling(window=w).std()/np.sqrt(len(k_roll_ts_mean))

    u_roll_ts = pd.Series(u)
    u_roll_ts_mean = u_roll_ts.rolling(window=w).mean()
    ci_u = 1.96 * u_roll_ts.rolling(window=w).std()/np.sqrt(len(u_roll_ts_mean))

    t_roll_ts = pd.Series(total)
    t_roll_ts_mean = t_roll_ts.rolling(window=w).mean()
    ci_t = 1.96 * t_roll_ts.rolling(window=w).std()/np.sqrt(len(t_roll_ts_mean))

    fig2, ax2 = plt.subplots()
    ax2.plot(k, color='royalblue', alpha=.5, label='Kinetic Energy')
    ax2.plot(u, color='indigo', alpha=.5, label='Potential Energy')
    ax2.plot(k_roll_ts_mean, color='darkorange', label='Kinetic Energy Mean')
    ax2.plot(u_roll_ts_mean, color='crimson', label='Potential Energy Mean')
    ax2.set_xlabel('t')
    ax2.set_ylabel('Energy')
    ax2.legend()
    ax2.grid(linestyle='--', alpha=.3)
    saveFig(fig_id="energy_ts", destination=data_path, fig_extension="png")

    fig3, ax3 = plt.subplots()
    ax3.plot(total, label='Total Energy', alpha=.9)
    ax3.plot(t_roll_ts_mean, label='Total Energy Mean')
    ax3.legend()
    ax3.grid(linestyle='--', alpha=.3)
    saveFig(fig_id="total_energy_ts", destination=data_path, fig_extension="png")

    fig4, ax4 = plt.subplots()
    ax4.scatter(simT, mepp)
    saveFig(fig_id="temp_mepp", destination=data_path, fig_extension="png")
    
def main():
    plot()
    return 0
    
if __name__=="__main__":
    main()