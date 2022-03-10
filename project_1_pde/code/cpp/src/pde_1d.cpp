#include <iostream>
#include <cmath>
#include <vector>
#include <array>
using namespace std;

const double PI = M_PI;

template<class T>
vector<T> linspace(double min, double max, int n)
{
    vector<T> result;
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

template<class T>
vector<T> zeros_1d(int n)
{
    vector<T> result;
    // vector iterator
    int iterator = 0;

    for (int i = 0; i <= n-1; i++)	
    {
        T temp = 0;
        result.insert(result.begin() + iterator, temp);
        iterator += 1;
    }

    return result;
}

template<class T>
vector<T> ones_1d(int n)
{
    vector<T> result;
    // vector iterator
    int iterator = 0;

    for (int i = 0; i <= n-1; i++)	
    {
        T temp = 1;
        result.insert(result.begin() + iterator, temp);
        iterator += 1;
    }

    return result;
}

int main()
{
    // Initialize Field Variables
    const int u = 200;
    const int N = 50;
    const double xmin = 0.;
    const double xmax = 1.;
    vector<double> x = linspace<double>(xmin, xmax, N);
    vector<double> E = ones_1d<double>(u);
    vector<double> field = zeros_1d<double>(N);

    double h = double (xmax-xmin)/N;
    vector<double> S = zeros_1d<double>(N);
    vector<double> f = zeros_1d<double>(N);
    
    // Initialize Source
    for(int i=0; i<S.size(); i++)
    {
        S[i] = sin(2*PI*x[i]);
    }

    // Set boundary conditions
    f[0]=0;
    f[N-1]=0;

    // Iteration Variables
    double s1=0;
    double s2=0;

    for(int k=0; k<u; k++)
    {
        for(int i=1; i<N-1; i++)
        {
            f[i] = 0.5*(f[i+1]+f[i-1]+pow(h,2)*S[i]);
        }
        for(int j=1; j<N; j++)
        {
            s1 += pow(f[j]-f[j-1], 2);
        }
        for(int t=1; t<N-1; t++)
        {
            s2 += S[t]*f[t];
        }

    }

    for(int i=0; i<N; i++)
    {
        switch(i)
        {
            case N-1: field[i] = -(f[i]-f[i-1])/h;
            case 0: field[i] = -(f[i+1]-f[i])/h;
            default: field[i] = -(f[i+1]-f[i-1])/(2*h);
        }

    }

    // for(int i=0; i<N; i++)
    // {
    //     cout << field[i] << endl;
    // }

    cout << endl;
    return 0;
}