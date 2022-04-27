#include "md.h"

int main()
{
	// Set Initial Values
	md::v_init << 5,1,5,6,2;
	md::q_init << 3,4,1,5,2;

	auto [pos, vel, accel] = md::system(md::q_init, md::v_init);

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

	return 0;
}