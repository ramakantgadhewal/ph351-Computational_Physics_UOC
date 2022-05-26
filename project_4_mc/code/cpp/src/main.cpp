#include "mc.h"

int main()
{

    // Constant Definitions
    mc::spin = Eigen::ArrayXXf(mc::L, mc::L);
    mc::hamiltonian = Eigen::ArrayXXf(mc::L, mc::L);

    mc::initSpin();
    std::cout << mc::spin << std::endl;

    return 0;

}