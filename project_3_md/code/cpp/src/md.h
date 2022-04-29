#pragma once

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
const int b = 0;
const int alpha = 0;
const int g = 0;

const float dt = 0.1;
const long max_time = 100;
const long steps = (long) max_time/dt;

const long N = 5;	// Number of particles

Eigen::ArrayXf masses(N);	// Masses of the particles
Eigen::ArrayXf q_init(N);	// Initial Generalized Position
Eigen::ArrayXf v_init(N);	// Initial Generalized Velocity

float mean(Eigen::ArrayXf A)
{
	float m = 0;
	for(size_t i=0; i<A.size(); i++)
	{
		m += A(i);
	}
	m /= A.size();
	return m;
};

float acceleration(int i, Eigen::ArrayXf q_i)
{
    float a;

	if(i==0)
	{	
		a = k/masses(i) * (q_i(i+1) - 2*q_i(i) + q_i(q_i.size()-1)) + g/masses(i) * \
			(std::pow((q_i(i+1)-q_i(i)), 3) - std::pow((q_i(i)-q_i(q_i.size()-1)), 3)) - alpha/masses(i) * \
			q_i(i) - b/masses(i) * std::pow(q_i(i), 3);
	}
	else if(i==q_i.size()-1)
	{
		a = k/masses(i) * (q_i(0) - 2*q_i(i) + q_i(i-1)) + g/masses(i) * \
			(std::pow((q_i(0)-q_i(i)), 3) - std::pow((q_i(i)-q_i(i-1)), 3)) - alpha/masses(i) * \
			q_i(i) - b/masses(i) * std::pow(q_i(i), 3);
	}
	else
	{
		a = k/masses(i) * (q_i(i+1) - 2*q_i(i) + q_i(i-1)) + g/masses(i) * \
			(std::pow((q_i(i+1)-q_i(i)), 3) - std::pow((q_i(i)-q_i(i-1)), 3)) - alpha/masses(i) * \
			q_i(i) - b/masses(i) * std::pow(q_i(i), 3);
	}

    return a;
};

std::tuple<Eigen::ArrayXXf, Eigen::ArrayXXf, Eigen::ArrayXXf> system(Eigen::ArrayXf q_init, Eigen::ArrayXf v_init)
{
	Eigen::ArrayXXf q = Eigen::ArrayXXf::Zero(N, steps);	// Generalized Position
	Eigen::ArrayXXf A = Eigen::ArrayXXf::Zero(N, steps);	// Generalized acceleration
	Eigen::ArrayXXf V = Eigen::ArrayXXf::Zero(N, steps);	// Generalized Velocity

	for(size_t t=0; t<steps; t++)
	{
		for(size_t i=0; i<N; i++)
		{
			if(t==0)
			{
				q(i, t) = q_init(i);
				V(i, t) = v_init(i);
				A(i, t) = acceleration(i, q.col(t));
			}
			else
			{
				V(i, t) = V(i, t-1) + 0.5 * (A(i, t-1) + A(i, t)) * dt;
				q(i, t)= q(i, t-1) + V(i, t-1) * dt + 0.5 * A(i, t-1) * std::pow(dt, 2);
				A(i, t) = acceleration(i, q.col(t));
			}
		}
	}

	return std::make_tuple(q, V, A);
};

Eigen::ArrayXf kineticEnergy(Eigen::ArrayXf m, Eigen::ArrayXXf V)
{
	Eigen::ArrayXf e(steps);

	for(size_t t=0; t<steps; t++)
	{
		e(t) = (0.5*m*V.col(t).pow(2)).sum();
	}

	return e;
};

Eigen::ArrayXf potentialEnergy(Eigen::ArrayXf m, Eigen::ArrayXXf Q)
{
	float sum_1, sum_2, sum_3, sum_4;
	Eigen::ArrayXf U(steps);
	
	for(size_t t=0; t<steps; t++)
	{
		sum_1 = 0;
		sum_2 = 0;
		sum_3 = 0;
		sum_4 = 0;
		for(size_t i=0; i<N; i++)
		{
			if(i==N-1)
			{
				sum_1 += std::pow((Q(0, t)-Q(i, t)), 2);
				sum_2 += std::pow((Q(0, t)-Q(i, t)), 4);
				sum_3 += std::pow(Q(i, t), 2);
				sum_4 += std::pow(Q(i, t), 4);
			}
			else
			{
				sum_1 += std::pow((Q(i+1, t)-Q(i, t)), 2);
				sum_2 += std::pow((Q(i+1, t)-Q(i, t)), 4);
				sum_3 += std::pow(Q(i, t), 2);
				sum_4 += std::pow(Q(i, t), 4);
			}
		}
		
		U(t) = 0.5 * k * sum_1 + 0.25 * g * sum_2 + 0.5 * alpha * sum_3 + 0.25 * b * sum_4;
	}

	return U;
}

}