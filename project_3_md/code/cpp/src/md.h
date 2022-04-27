#pragma once

#include "../../../../universal_code/cpp/src/Eigen/Core"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <tuple>

namespace md
{

// Initialize Parameters
const int8_t k = 0;
const int b = 0;
const int alpha = 1;
const int g = 0;

const float dt = 0.5;
const long max_time = 4;
const long steps = (long) max_time/dt;

const long N = 5;
const long L = 10;

// Initialize Arrays
Eigen::ArrayXf temp = Eigen::ArrayXf::LinSpaced(51, 0, 8);
Eigen::ArrayXf T = Eigen::ArrayXf::Zero(50);
Eigen::ArrayXf m = Eigen::ArrayXf::Ones(N);
Eigen::ArrayXf u = Eigen::ArrayXf::Zero(N);
Eigen::ArrayXf K = Eigen::ArrayXf::Zero(L);
Eigen::ArrayXf E = Eigen::ArrayXf::Zero(50);
Eigen::ArrayXf U = Eigen::ArrayXf::Zero(L);
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

Eigen::ArrayXf acceleration(Eigen::ArrayXf q_i)
{
    Eigen::ArrayXf a = Eigen::ArrayXf::Zero(q_i.size());	// Generalized acceleration

    for(size_t i=0; i<q_i.size(); i++)
	{
		if(i==0)
		{	
			a(i) = k/m(i) * (q_i(i+1) - 2*q_i(i) + q_i(q_i.size()-1)) + g/m(i) * \
				(std::pow((q_i(i+1)-q_i(i)), 3) - std::pow((q_i(i)-q_i(q_i.size()-1)), 3)) - alpha/m(i) * \
				q_i(i) - b/m(i) * std::pow(q_i(i), 3);
		}
		else if(i==q_i.size()-1)
		{
			a(i) = k/m(i) * (q_i(0) - 2*q_i(i) + q_i(i-1)) + g/m(i) * \
				(std::pow((q_i(0)-q_i(i)), 3) - std::pow((q_i(i)-q_i(i-1)), 3)) - alpha/m(i) * \
				q_i(i) - b/m(i) * std::pow(q_i(i), 3);
		}
		else
		{
			a(i) = k/m(i) * (q_i(i+1) - 2*q_i(i) + q_i(i-1)) + g/m(i) * \
				(std::pow((q_i(i+1)-q_i(i)), 3) - std::pow((q_i(i)-q_i(i-1)), 3)) - alpha/m(i) * \
				q_i(i) - b/m(i) * std::pow(q_i(i), 3);
		}
	}

    return a;
};

std::tuple<Eigen::ArrayXXf, Eigen::ArrayXXf, Eigen::ArrayXXf> system(Eigen::ArrayXf q_init, Eigen::ArrayXf v_init)
{
	Eigen::ArrayXXf q = Eigen::ArrayXXf::Zero(N, steps);
	Eigen::ArrayXXf A = Eigen::ArrayXXf::Zero(N, steps);
	Eigen::ArrayXXf V = Eigen::ArrayXXf::Zero(N, steps);
	V.col(0) = v_init;
	A.col(0) = acceleration(q_init);

	for(size_t t=0; t<steps; t++)
	{
		for(size_t i=0; i<N; i++)
		{
			if(t==0) q(i, t) = q_init(i);
			else
			{
				V(i, t) = V(i, t-1) + 0.5 * (A(i, t-1) + A(i, t)) * dt;
				q(i, t)= q(i, t-1) + V(i,t-1) * dt + 0.5 * A(i, t-1) * std::pow(dt, 2);
				A.col(i) = acceleration(q.col(i));
			}
		}
	}

	return std::make_tuple(q, V, A);
};

}