#include "../../../../universal_code/cpp/src/FuncTools.h"
#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;

double PI = M_PI;

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
    vector<double> potential = zeros_1d<double>(N);
    
    // Initialize Source
    for(int i=0; i<S.size(); i++)
    {
        S[i] = sin(2*PI*x[i]);
    }

    // Set boundary conditions
    potential[0]=0;
    potential[N-1]=0;

    // Iteration Variables
    double s1;
    double s2;

    for(int k=0; k<u; k++)
    {
        s1 = 0;
        s2 = 0;
        for(int i=1; i<N-1; i++) potential[i] = 0.5*(potential[i+1]+potential[i-1]+pow(h,2)*S[i]);
        for(int j=1; j<N; j++) s1 += pow(potential[j]-potential[j-1], 2);
        for(int t=1; t<N-1; t++) s2 += S[t]*potential[t];

        E[k] = s1/(2*h)-h*s2;
    }

    for(int i=0; i<N; i++)
    {
        switch(i)
        {
            case N-1: field[i] = -(potential[i]-potential[i-1])/h; break;
            case 0: field[i] = -(potential[i+1]-potential[i])/h; break;
            default: field[i] = -(potential[i+1]-potential[i-1])/(2*h); break;
        }
    }

    // Create data directory to save results
    namespace fs = std::filesystem;
    fs::path p=fs::current_path();
    fs::create_directory(p+="/data");

    ofstream energy{"data/energy_data_1d.dat"};
    for(int i=0; i<E.size(); i++)
    {
        energy << E[i] << endl;
    }
    energy.close();

    ofstream pot{"data/potential_1d.dat"};
    for(int i=0; i<potential.size(); i++)
    {
        pot << potential[i] << endl;
    }
    pot.close();

    ofstream Field{"data/field_1d.dat"};
    for(int i=0; i<field.size(); i++)
    {
        Field << field[i] << endl;
    }
    Field.close();

    ofstream Source{"data/source_1d.dat"};
    for(int i=0; i<S.size(); i++)
    {
        Source << S[i] << endl;
    }
    Source.close();
    
    return 0;
}