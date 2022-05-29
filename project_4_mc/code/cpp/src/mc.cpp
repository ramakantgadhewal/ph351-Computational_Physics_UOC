#include "mc.h"

Eigen::ArrayXXi mc::initSpin()
{
    Eigen::ArrayXXi s(mc::L, mc::L);

    for( int i=0; i<mc::L; i++ )
    {
        for( int j=0; j<mc::L; j++ )
        {
            bool value = mc::uni(mc::rng);
            if( value ) s(i, j) = 1;
            else s(i, j) = -1;
        }
    }

    return s;
}


std::vector<int> mc::neighbours(int i, int j, Eigen::ArrayXXi S)
{
    // initialize direction indices
    int u, d, r, l;
    u = j+1 == mc::L ? 0 : j+1;
    d = j-1 == -1 ? mc::L-1 : j-1;
    r = i+1 == mc::L ? 0 : i+1;
    l = i-1 == -1 ? mc::L-1 : i-1;

    int *s = S.data();
    std::vector<int> _tmp(4);
    _tmp[0] = s[i+u*mc::L];
    _tmp[1] = s[i+d*mc::L];
    _tmp[2] = s[r+j*mc::L];
    _tmp[3] = s[l+j*mc::L];

    return _tmp;
}

float mc::getEnergy(Eigen::ArrayXXi spin)
{
    float _e{0};

    for( int i=0; i<mc::L; i++ )
    {
        for( int j=0; j<mc::L; j++ )
        {
            std::vector<int> f = mc::neighbours(i, j, spin);
            _e -= mc::J * spin(i, j) * ( f[0] + f[1] + f[2] + f[3] ) - mc::B * spin(i, j);
        }
    }
    return _e;
}

float mc::getMagneticMoment(Eigen::ArrayXXi spin)
{
    return std::abs(spin.sum());
}

Eigen::ArrayXXi mc::metropolis(Eigen::ArrayXXi spin, int tend)
{
    int _i, _j;

    float _r;
    float beta = 1./float(mc::T);

    int relax_time = 1000;

    Eigen::ArrayXXi s = spin;
    Eigen::ArrayXf energy(relax_time);
    Eigen::ArrayXf moment(relax_time);
    Eigen::ArrayXf energy2(relax_time);
    Eigen::ArrayXf moment2(relax_time);

    std::uniform_int_distribution<int> big_uni(0, mc::L-1);
    std::uniform_real_distribution<float> unif(0, 1);
    int id = 0;
    for( int t=0; t<tend+relax_time; t++ )
    {
        // Monte Carlo Sweep
        for( unsigned int i=0; i<mc::N; i++ )
        {
            _i = big_uni(mc::rng);
            _j = big_uni(mc::rng);
            int point = s(_i, _j);

            std::vector<int> f = mc::neighbours(_i, _j, s);
            float exponent = - 2 * beta * s(_i, _j) * ( mc::J * ( f[0] + f[1] + f[2] + f[3] ) + mc::B );
            _r = std::exp(exponent);

            if( _r > 1 ) 
            {
                s(_i, _j) = -point;
            }
            else if( _r < 1 )
            {
                float eta = unif(mc::rng);
                if( _r > eta ) s(_i, _j) = -point;
            }
        }

        if( t>=tend )
        {
            energy(id) = mc::getEnergy(s);
            moment(id) = mc::getMagneticMoment(s);
            energy2(id) = mc::getEnergy(s) * mc::getEnergy(s);
            moment2(id) = mc::getMagneticMoment(s) * mc::getMagneticMoment(s);
            id++;
        }
    }

    mc::mean_energy = energy.sum() / relax_time;
    mc::mean_moment = moment.sum() / relax_time;
    mc::mean_energy_squared = energy2.sum() / relax_time;
    mc::mean_moment_squared = moment2.sum() / relax_time;
    return s;
}

int main()
{
    // initialize temperature array
    Eigen::VectorXf _temp = Eigen::VectorXf::LinSpaced(50, 1, 10);
    
    // Set System Parameters
    mc::time = 2000;

    // vector to store energy values and magnetic moment values
    Eigen::ArrayXf E(_temp.size());
    Eigen::ArrayXf E2(_temp.size());
    Eigen::ArrayXf M(_temp.size());
    Eigen::ArrayXf M2(_temp.size());

    // prepareation to save files
    namespace fs = std::filesystem;
    fs::path p = fs::current_path();
    std::string data_path("/data");
    fs::create_directory(p+=data_path); // create directory to save data
    for( int l=5; l<=10; l+=1 )
    {
        std::cout << "Grid size: " << l << std::endl;
        // set constants
        mc::L = l;
        mc::T = _temp(0);

        fs::path p = fs::current_path();
        p += data_path;
        std::string data_path_sub("data");
        data_path_sub.append("_");
        data_path_sub.append(std::to_string(l));
        fs::create_directory( p += "/" + data_path_sub );

        // Initialize lattice with random spin values
        Eigen::ArrayXXi S_init = mc::initSpin();

        // Save Initial Spin configuration
        std::string filename_init{ p.string() + "/init_spin" };
        filename_init.append("_T");
        filename_init.append(std::to_string(int(mc::T)));
        filename_init.append(".dat");
        std::ofstream init_spin{ filename_init };
        for(size_t i=0; i < mc::L; i++)
        {
            for(size_t j=0; j < mc::L; j++)
            {
                init_spin << S_init(i, j) << " ";
            }
            init_spin << "\n";
        }
        init_spin.close();

        int counter = 0;
        Eigen::ArrayXXi S(S_init.rows(), S_init.cols());
        for( auto const& n: _temp )
        {   
            mc::T = n;   
            if( counter == 0 ) S = mc::metropolis(S_init, mc::time);
            else S = mc::metropolis(S, mc::time);
            E(counter) = mc::mean_energy / ( l * l );
            E2(counter) = mc::mean_energy_squared / ( l * l );
            M(counter) = mc::mean_moment / ( l * l );
            M2(counter) = mc::mean_moment_squared / ( l * l );

            std::string filename_evolved{ p.string() + "/spin" };
            filename_evolved.append("_L");
            filename_evolved.append(std::to_string(l));
            filename_evolved.append("_T");
            filename_evolved.append(std::to_string(int(mc::T)));
            filename_evolved.append(".dat");
            std::ofstream spin{ filename_evolved };
            for(size_t i=0; i < mc::L; i++)
            {
                for(size_t j=0; j < mc::L; j++)
                {
                    spin << S(i, j) << " ";
                }
                spin << "\n";
            }
            spin.close();
            counter++;
        }

        std::string energy_filename{ p.string() + "/energy" };
        energy_filename.append("_L");
        energy_filename.append(std::to_string(l));
        energy_filename.append(".dat");
        std::ofstream energy{ energy_filename };
        for(size_t i=0; i < E.size(); i++)
        {
            energy << E(i) << std::endl;
        }
        energy.close();

        std::string energy_squared_filename{ p.string() + "/energy_squared" };
        energy_squared_filename.append("_L");
        energy_squared_filename.append(std::to_string(l));
        energy_squared_filename.append(".dat");
        std::ofstream energy_squared{ energy_squared_filename };
        for(size_t i=0; i < E.size(); i++)
        {
            energy_squared << E2(i) << std::endl;
        }
        energy_squared.close();

        std::string m_filename{ p.string() + "/magnetic_moment" };
        m_filename.append("_L");
        m_filename.append(std::to_string(l));
        m_filename.append(".dat");
        std::ofstream magnetic_moment{ m_filename };
        for(size_t i=0; i < E.size(); i++)
        {
            magnetic_moment << M(i) << std::endl;
        }
        magnetic_moment.close();

        std::string m2_filename{ p.string() + "/magnetic_moment_squared" };
        m2_filename.append("_L");
        m2_filename.append(std::to_string(l));
        m2_filename.append(".dat");
        std::ofstream magnetic_moment_squared{ m2_filename };
        for(size_t i=0; i < E.size(); i++)
        {
            magnetic_moment_squared << M2(i) << std::endl;
        }
        magnetic_moment_squared.close();
    }

    return 0;
}
