#include "../../../../universal_code/cpp/src/Eigen/Core"
#include <iostream>

int main()
{
	// Initialize Parameters
	const int k = 0;
	const int b = 0;
	const int e = 1;
	const int g = 0;
	const float dt = 0.1;
	const int N = 100;
	const int L = 1000;

	Eigen::ArrayXf temp = Eigen::ArrayXf::LinSpaced(51, 0, 8);


	std::cout << temp << std::endl;

	return 0;
}