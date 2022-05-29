#ifndef _MC_H_
#define _MC_H_

#include <iostream>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <random>
#include <vector>
#include "../../../../universal_code/cpp/src/Eigen/Core"

namespace mc
{

// Monte Carlo Sweeps
static const float N{40};
static const float J{1}, B{0};

int time, L, size{L*L};

float T, mean_moment, mean_energy, mean_moment_squared, mean_energy_squared;

// rng setup to randomly initiate spin matrix
static std::random_device rd;
static std::mt19937 rng(rd());
// distribution that will be used during the run of the program
std::uniform_int_distribution<int> uni(0, 1);

Eigen::ArrayXXi initSpin();

std::vector<int> neighbours(int, int, Eigen::ArrayXXi); 

float getEnergy(Eigen::ArrayXXi);

float getMagneticMoment(Eigen::ArrayXXi);

Eigen::ArrayXXi metropolis(Eigen::ArrayXXi, int);

}

#endif
