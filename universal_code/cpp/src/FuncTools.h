#pragma once
#include <vector>
#include <cmath>

template<typename T>
std::vector<T> linspace(double min, double max, int n)
{
    std::vector<T> result;
    // vector iterator
    int iterator = 0;

    for (int i = 0; i <= n-2; i++)	
    {
        T temp = min + i*(max-min)/(std::floor((T)n) - 1);
        result.insert(result.begin() + iterator, temp);
        iterator += 1;
    }

    result.insert(result.begin() + iterator, max);
    return result;
};

template<typename T>
std::vector<T> zeros_1d(int n)
{
    std::vector<T> result;
    // vector iterator
    int iterator = 0;

    for (int i = 0; i <= n-1; i++)	
    {
        T temp = 0;
        result.insert(result.begin() + iterator, temp);
        iterator += 1;
    }

    return result;
};

template<typename T>
std::vector<T> ones_1d(int n)
{
    std::vector<T> result;
    // vector iterator
    int iterator = 0;

    for (int i = 0; i <= n-1; i++)	
    {
        T temp = 1;
        result.insert(result.begin() + iterator, temp);
        iterator += 1;
    }

    return result;
};
