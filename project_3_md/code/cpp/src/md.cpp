#include "md.h"

int main()
{
	Eigen::ArrayXf q = Eigen::ArrayXf::Zero(N);	// Generalized Position

	std::cout << acceleration(q) << std::endl;

	return 0;
}