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

static const int L{100}, size{L*L}, time{10000};
static const float J{1}, B{0.5}, T{1};

// Spin matrix containing all the spin values of each lattice site
inline Eigen::ArrayXXf spin;

// Total energy of the Ising Model
float energy;

// rng setup to randomly initiate spin matrix
static std::random_device rd;
static std::mt19937 rng(rd());
static std::uniform_int_distribution<int> uni(0, 1);
static std::uniform_int_distribution<int> big_uni(0, mc::L-1);

Eigen::ArrayXXf initSpin();

std::vector<float> neighbours(int, int, Eigen::ArrayXXf); 

void getEnergy(Eigen::ArrayXXf);

Eigen::ArrayXXf metropolis(Eigen::ArrayXXf);

}

#endif
