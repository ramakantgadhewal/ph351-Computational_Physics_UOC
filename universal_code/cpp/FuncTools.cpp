#include "FuncTools.h"

template<typename T>
std::vector<T> linspace(double min, double max, int n)
{
    std::vector<T> result;
    // vector iterator
    int iterator = 0;

    for (int i = 0; i <= n-2; i++)	
    {
        T temp = min + i*(max-min)/(floor((T)n) - 1);
        result.insert(result.begin() + iterator, temp);
        iterator += 1;
    }

    result.insert(result.begin() + iterator, max);
    return result;
}