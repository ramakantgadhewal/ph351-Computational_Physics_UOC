#include "md.h"

int main()
{
	// Set Initial Values
	md::v_init = Eigen::ArrayXf::Random(md::N);
	md::q_init = Eigen::ArrayXf::Zero(md::N);
	md::masses = Eigen::ArrayXf::Ones(md::N);

	auto [pos, vel, accel] = md::system(md::q_init, md::v_init);
	Eigen::ArrayXf U = md::potentialEnergy(md::masses, pos);
    Eigen::ArrayXf K = md::kineticEnergy(md::masses, vel);

	/* --------------------------------------------------------- */

	// Save files for plotting
    namespace fs = std::filesystem;
    fs::path p = fs::current_path();
    fs::create_directory(p+="/data");

    std::ofstream position{ "data/position.dat" };
    for(size_t i=0; i < md::N; i++)
	{
		for(size_t t=0; t < md::steps; t++)
        {
            position << pos(i, t) << " ";
        }
        position << "\n";
    }
    position.close();

	std::ofstream velocity{ "data/velocity.dat" };
    for(size_t i=0; i < md::N; i++)
	{
		for(size_t t=0; t < md::steps; t++)
        {
            velocity << vel(i, t) << " ";
        }
        velocity << "\n";
    }
    velocity.close();

	std::ofstream acceleration{ "data/acceleration.dat" };
    for(size_t i=0; i < md::N; i++)
	{
		for(size_t t=0; t < md::steps; t++)
        {
            acceleration << accel(i, t) << " ";
        }
        acceleration << "\n";
    }
    acceleration.close();

    std::ofstream kinetic{ "data/kinetic.dat" };
    for(size_t t=0; t < md::steps; t++)
    {
        kinetic << K(t) << std::endl;
    }
    kinetic.close();

    std::ofstream potential{ "data/potential.dat" };
    for(size_t t=0; t < md::steps; t++)
    {
        potential << U(t) << std::endl;
    }
    potential.close();

	return 0;
}