#include "ed.hpp"

namespace Hamiltonian
{

template <class T>
class BoseHubbard: public functools::Matrix<T>
{
private:
public:
    BoseHubbard( int hilbert_dim );
};

}