#include "mc.h"

int main()
{

    // Constant Definitions
    mc::spin = Eigen::ArrayXXf::Zero(mc::L, mc::L);
    mc::hamiltonian = Eigen::ArrayXXf::Zero(mc::L, mc::L);

    mc::initSpin();
    std::cout << mc::spin << std::endl;

    mc::initHamiltonian();
    std::cout << mc::hamiltonian << std::endl;

    return 0;

}