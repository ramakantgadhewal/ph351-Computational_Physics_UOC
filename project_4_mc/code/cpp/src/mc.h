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

static const int L{200}, size{L*L};
static const float J{1}, B{0.5};

int time;

float T{1};

// rng setup to randomly initiate spin matrix
static std::random_device rd;
static std::mt19937 rng(rd());
static std::uniform_int_distribution<int> uni(0, 1);
static std::uniform_int_distribution<int> big_uni(0, mc::L-1);

Eigen::ArrayXXf initSpin();

std::vector<float> neighbours(int, int, Eigen::ArrayXXf); 

float getEnergy(Eigen::ArrayXXf);

Eigen::ArrayXXf metropolis(Eigen::ArrayXXf);

}

#endif
