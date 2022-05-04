#ifndef _MD_H_
#define _MD_H_

#include "../../../../universal_code/cpp/src/Eigen/Core"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <tuple>
#include <random>

namespace md
{

// Initialize Parameters
const int k = 3;
const int b = 7;
const int alpha = 2;
const int g = 5;

const float dt = 0.1;
const long max_time = 1000;
const long steps = (long) max_time/dt;

const long N = 100;	// Number of particles
const float T = 1;	// Target Temperature
const int t_samples = 100;	// Number of Temperature Samples

const float L = 0.1; // Range of distribution of velocities

Eigen::ArrayXf q_init = Eigen::ArrayXf::Zero(N);    // Initial Position
Eigen::ArrayXf masses = Eigen::ArrayXf::Ones(N);    // Masses of the particles

// Function Declarations

// Calculate Mean of 1D array
float mean(Eigen::ArrayXf); 

// Calculate the acceleration of a particle given its position
float acceleration(int, Eigen::ArrayXf);

// Calculate the position, velocity and acceleration of all the particles for a given max_time
std::tuple<Eigen::ArrayXXf, Eigen::ArrayXXf, Eigen::ArrayXXf> system(Eigen::ArrayXf, Eigen::ArrayXf);

// Calculate the Kinetic Energy of the system for max_time
Eigen::ArrayXf kineticEnergy(Eigen::ArrayXf, Eigen::ArrayXXf);

// Calculate the Potential Energy of the system for max_time
Eigen::ArrayXf potentialEnergy(Eigen::ArrayXXf);

// Calculate the Total Energy of the system for max_time
std::tuple<float, float> mean_total_energy_pp(Eigen::ArrayXf, float, float);

}

#endif