/* 

MAKE SURE TO COMPILE USING -O2 OPTIMIZATIONS 

*/

#include "md.h"

std::tuple<float, float> md::mean_total_energy_pp(Eigen::ArrayXf vinit, float target, float system_T)
{
    Eigen::ArrayXf target_vinit = vinit * std::sqrt(target / system_T);
    auto [target_pos, target_vel, target_accel] = md::system(md::q_init, target_vinit);
    Eigen::ArrayXf target_U = md::potentialEnergy(md::masses, target_pos);
    Eigen::ArrayXf target_K = md::kineticEnergy(md::masses, target_vel);
    Eigen::ArrayXf target_total_energy = target_U + target_K;
    float target_T = 2 * md::mean(target_K)/md::N;
    float mean_energy_pp = md::mean(target_total_energy)/md::N;

    return std::make_tuple(target_T, mean_energy_pp);
};

float md::mean(Eigen::ArrayXf A) { return A.mean(); };

float md::acceleration(int i, Eigen::ArrayXf q_i)
{
    float a;

	if(i==0)
	{	
		a = md::k/md::masses(i) * (q_i(i+1) - 2*q_i(i) + q_i(q_i.size()-1)) + md::g/md::masses(i) * \
			(std::pow((q_i(i+1)-q_i(i)), 3) - std::pow((q_i(i)-q_i(q_i.size()-1)), 3)) - md::alpha/md::masses(i) * \
			q_i(i) - md::b/md::masses(i) * std::pow(q_i(i), 3);
	}
	else if(i==N-1)
	{
		a = md::k/md::masses(i) * (q_i(0) - 2*q_i(i) + q_i(i-1)) + md::g/md::masses(i) * \
			(std::pow((q_i(0)-q_i(i)), 3) - std::pow((q_i(i)-q_i(i-1)), 3)) - md::alpha/md::masses(i) * \
			q_i(i) - md::b/md::masses(i) * std::pow(q_i(i), 3);
	}
	else
	{
		a = md::k/md::masses(i) * (q_i(i+1) - 2*q_i(i) + q_i(i-1)) + md::g/md::masses(i) * \
			(std::pow((q_i(i+1)-q_i(i)), 3) - std::pow((q_i(i)-q_i(i-1)), 3)) - md::alpha/md::masses(i) * \
			q_i(i) - md::b/md::masses(i) * std::pow(q_i(i), 3);
	}

    return a;
};

std::tuple<Eigen::ArrayXXf, Eigen::ArrayXXf, Eigen::ArrayXXf> md::system(Eigen::ArrayXf qinit, Eigen::ArrayXf vinit)
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
				q(i, t) = qinit(i);
				A(i, t) = acceleration(i, q.col(t));
			}
			else
			{
				q(i, t)= q(i, t-1) + V(i, t-1) * dt + 0.5 * A(i, t-1) * std::pow(dt, 2);
			}
		}
		for(size_t i=0; i<N; i++)
		{
			A(i, t) = acceleration(i, q.col(t));
		}
		for(size_t i=0; i<N; i++)
		{
			if(t==0)
			{
				V(i, t) = vinit(i);
			}
			else
			{
				V(i, t) = V(i, t-1) + 0.5 * (A(i, t-1) + A(i, t)) * dt;
			}
		}
	}

	return std::make_tuple(q, V, A);
};

Eigen::ArrayXf md::kineticEnergy(Eigen::ArrayXf m, Eigen::ArrayXXf V)
{
	Eigen::ArrayXf e(steps);

	for(size_t t=0; t<steps; t++)
	{
		e(t) = (0.5*m*V.col(t).pow(2)).sum();
	}

	return e;
};

Eigen::ArrayXf md::potentialEnergy(Eigen::ArrayXf m, Eigen::ArrayXXf Q)
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
		
		U(t) = 0.5 * md::k * sum_1 + 0.25 * md::g * sum_2 + 0.5 * md::alpha * sum_3 + 0.25 * md::b * sum_4;
	}

	return U;
};

int main()
{
    // Initialize Generator
    std::default_random_engine generator;

    // Initialize Distribution
    std::uniform_real_distribution<float> dist(-md::L, md::L);
    auto uniform = [&] (int) {return dist(generator);}; // Lambda that returns a value from dist()

	// Initial Velocity
    Eigen::ArrayXf v_init = Eigen::ArrayXf::NullaryExpr(md::N, uniform);
	// Initial Positions are all 0 and masses 1

    auto [pos, vel, accel] = md::system(md::q_init, v_init);

    Eigen::ArrayXf U = md::potentialEnergy(md::masses, pos);
    Eigen::ArrayXf K = md::kineticEnergy(md::masses, vel);
    Eigen::ArrayXf total_energy = U + K;
    float system_T = 2 * md::mean(K)/md::N;	// Calculate Temperature from Kinetic Energy

    Eigen::ArrayXf array_T(md::t_samples);	// Array to save simulated Temperatures
    Eigen::ArrayXf array_mepp(md::t_samples);	// Array to save simulated Mean Energies Per Particle
    
    int counter = 0;
    for(auto i: Eigen::ArrayXf::LinSpaced(md::t_samples, system_T, md::T))
    {
        auto [temp_T, temp_mepp] = md::mean_total_energy_pp(v_init, i, system_T);
        array_T(counter) = temp_T;
        array_mepp(counter) = temp_mepp;
		if(counter%10==0) std::cout << counter << std::endl;
        counter++;
    }

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

    std::ofstream total{ "data/total.dat" };
    for(size_t t=0; t < md::steps; t++)
    {
        total << total_energy(t) << std::endl;
    }
    total.close();

	std::ofstream mepp{ "data/mepp.dat" };
    for(size_t i=0; i < md::t_samples; i++)
    {
        mepp << array_mepp(i) << std::endl;
    }
    mepp.close();

	std::ofstream sim_temp{ "data/sim_temp.dat" };
    for(size_t i=0; i < md::t_samples; i++)
    {
        sim_temp << array_T(i) << std::endl;
    }
    sim_temp.close();

	return 0;
};