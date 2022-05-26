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
