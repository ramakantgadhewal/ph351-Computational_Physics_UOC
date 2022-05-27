#include "mc.h"

void mc::initSpin()
{
    // Generate Spin Matrix
    for( int i=0; i<mc::L; i++ )
    {
        for( int j=0; j<mc::L; j++ )
        {
            int value = mc::uni(mc::rng);
            if( value >= 0 ) mc::spin(i, j) = 1;
            else mc::spin(i, j) = -1;
        }
    }    

}

std::vector<float> mc::neighbours(int i, int j)
{
    int u, d, r, l;
    u = j+1 == mc::L ? 0 : j+1;
    d = j-1 == -1 ? mc::L-1 : j-1;
    r = i+1 == mc::L ? 0 : i+1;
    l = i-1 == -1 ? mc::L-1 : i-1;

    float *s = mc::spin.data();
    std::vector<float> _tmp(4);
    _tmp[0] = s[i+u*mc::L];
    _tmp[1] = s[i+d*mc::L];
    _tmp[2] = s[r+j*mc::L];
    _tmp[3] = s[l+j*mc::L];

    return _tmp;
}

void mc::initHamiltonian()
{
    for( int i=0; i<mc::L; i++ )
    {
        for( int j=0; j<mc::L; j++ )
        {
            std::vector<float> _neighbours = mc::neighbours(i, j);
            mc::hamiltonian(i, j) = - mc::J * ( 
                                      mc::spin(i, j) * _neighbours[0]
                                    + mc::spin(i, j) * _neighbours[1]
                                    + mc::spin(i, j) * _neighbours[2]
                                    + mc::spin(i, j) * _neighbours[3]
                                    ) - mc::B * mc::spin.sum();
        }
    }
}
