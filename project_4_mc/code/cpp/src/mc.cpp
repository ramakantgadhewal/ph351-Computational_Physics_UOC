#include "mc.h"

Eigen::ArrayXXf mc::initSpin()
{
    Eigen::ArrayXXf s(mc::L, mc::L);

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

std::vector<float> mc::neighbours(int i, int j, Eigen::ArrayXXf S)
{
    // initialize direction indices
    int u, d, r, l;
    u = j+1 == mc::L ? 0 : j+1;
    d = j-1 == -1 ? mc::L-1 : j-1;
    r = i+1 == mc::L ? 0 : i+1;
    l = i-1 == -1 ? mc::L-1 : i-1;

    float *s = S.data();
    std::vector<float> _tmp(4);
    _tmp[0] = s[i+u*mc::L];
    _tmp[1] = s[i+d*mc::L];
    _tmp[2] = s[r+j*mc::L];
    _tmp[3] = s[l+j*mc::L];

    return _tmp;
}

void mc::getEnergy(Eigen::ArrayXXf spin)
{
    float first_term{0}, second_term{0};

    for( int i=0; i<mc::L; i++ )
    {
        for( int j=0; j<mc::L; j++ )
        {
            std::vector<float> _neighbours = mc::neighbours(i, j, spin);
            first_term -= mc::J * ( spin(i, j) * _neighbours[0]
                                  + spin(i, j) * _neighbours[1]
                                  + spin(i, j) * _neighbours[2]
                                  + spin(i, j) * _neighbours[3] );
        }
    }

    second_term = - mc::B * mc::spin.sum();
    mc::energy = first_term + second_term;
}

Eigen::ArrayXXf mc::metropolis(Eigen::ArrayXXf spin)
{
    int _i, _j;

    float _r;
    float beta = float(1)/float(mc::T);

    Eigen::ArrayXXf s = spin;
    Eigen::ArrayXXf st;

    for( int t=0; t<mc::time; t++ )
    {
        st = s;
        _i = big_uni(mc::rng);
        _j = big_uni(mc::rng);
        st(_i, _j) = -st(_i, _j);
        std::vector<float> _neighbours = mc::neighbours(_i, _j, st);
    
        float f = _neighbours[0] + _neighbours[1] + _neighbours[2] + _neighbours[3];
        float exponent = - 2 * beta * s(_i, _j) * ( mc::J * f + mc::B );
        _r = std::exp( exponent );

        if( _r > 1 )
        {
            s = st;
        }
        else if( _r < 1 )
        {
            std::uniform_real_distribution<float> unif(0, 1);
            float eta = unif(mc::rng);
            if( _r > eta )
            {
                s = st;
            }
        }
    }

    return s;
}

int main()
{
    namespace fs = std::filesystem;
    fs::path p = fs::current_path();
    fs::create_directory(p+="/data");

    Eigen::ArrayXXf S_init = mc::initSpin();

    std::ofstream init_spin{ "data/init_spin.dat" };
    for(size_t i=0; i < mc::L; i++)
	{
		for(size_t j=0; j < mc::L; j++)
        {
            init_spin << S_init(i, j) << " ";
        }
        init_spin << "\n";
    }
    init_spin.close();

    Eigen::ArrayXXf S = mc::metropolis(S_init);

    std::ofstream spin{ "data/spin.dat" };
    for(size_t i=0; i < mc::L; i++)
	{
		for(size_t j=0; j < mc::L; j++)
        {
            spin << S(i, j) << " ";
        }
        spin << "\n";
    }
    spin.close();

    return 0;
}
