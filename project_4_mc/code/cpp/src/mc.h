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

static const int L{16}, J{1}, B{1}, size{L*L};

// Spin matrix containing all the spin values of each lattice site
inline Eigen::ArrayXXf spin;
inline Eigen::ArrayXXf neighbouring_spins;

// rng setup to randomly initiate spin matrix
static std::random_device rd;
static std::mt19937 rng(rd());
static std::uniform_int_distribution<int> uni(-1, 1);

// Hamiltonian of the Ising Model
inline Eigen::ArrayXXf hamiltonian;

void initSpin();

std::vector<float> neighbours(int, int); 

void initHamiltonian();

}

#endif
