#include "../../../../universal_code/cpp/src/Eigen/Core"
#include <iostream>

using namespace Eigen;

float_t mean(ArrayXf A)
{
	float_t m = 0;
	for(size_t i=0; i<A.size(); i++)
	{
		m += A(i);
	}
	m /= A.size();
	return m;
}

int main()
{
	// Initialize Parameters
	const uint8_t k = 0;
	const uint8_t b = 0;
	const uint8_t alpha = 1;
	const uint8_t g = 0;

	const float_t dt = 0.1;
	const uint8_t time = 150;
	const float_t steps = time/dt;

	const uint8_t N = 100;
	const uint16_t L = 1000;

	// Initialize Arrays
	ArrayXf temp = ArrayXf::LinSpaced(51, 0, 8);
	ArrayXf T = ArrayXf::Zero(50);
	ArrayXf m = ArrayXf::Ones(N);
	ArrayXf u = ArrayXf::Zero(N);
	ArrayXf K = ArrayXf::Zero(L);
	ArrayXf E = ArrayXf::Zero(50);
	ArrayXf U = ArrayXf::Zero(L);
	ArrayXf q = ArrayXf::Zero(N);	// Generalized Position
	ArrayXf a = ArrayXf::Zero(N);	// Generalized acceleration

	for(size_t i=0; i<a.size(); i++)
	{
		if(i==0)
		{	
			a(i) = k/m(i) * (q(i+1) - 2*q(i) + q(q.size()-1)) + g/m(i) * \
				(std::pow((q(i+1)-q(i)), 3) - std::pow((q(i)-q(q.size()-1)), 3)) - alpha/m(i) * \
				q(i) - b/m(i) * std::pow(q(i), 3);
		}
		else if(i==q.size()-1)
		{
			a(i) = k/m(i) * (q(0) - 2*q(i) + q(i-1)) + g/m(i) * \
				(std::pow((q(0)-q(i)), 3) - std::pow((q(i)-q(i-1)), 3)) - alpha/m(i) * \
				q(i) - b/m(i) * std::pow(q(i), 3);
		}
		else
		{
			a(i) = k/m(i) * (q(i+1) - 2*q(i) + q(i-1)) + g/m(i) * \
				(std::pow((q(i+1)-q(i)), 3) - std::pow((q(i)-q(i-1)), 3)) - alpha/m(i) * \
				q(i) - b/m(i) * std::pow(q(i), 3);
		}
	}

	std::cout << a << std::endl;

	return 0;
}