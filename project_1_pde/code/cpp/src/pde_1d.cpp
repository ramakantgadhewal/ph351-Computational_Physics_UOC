#include "../../../../universal_code/cpp/src/FuncTools.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;

double PI = M_PI;

int main()
{
    // Initialize Field Variables
    const int u = 10000;
    const int N = 100;
    const double xmin = 0.;
    const double xmax = 1.;
    vector<double> x = functools::linspace<double>(xmin, xmax, N);
    vector<double> E = functools::ones_1d<double>(u);
    vector<double> field = functools::zeros_1d<double>(N);

    double h = double (xmax-xmin)/N;
    vector<double> S = functools::zeros_1d<double>(N);
    vector<double> phi = functools::zeros_1d<double>(N);
    
    // Initialize Source
    for(int i=0; i<S.size(); i++)
    {
        S[i] = 12*pow(x[i],2);
    }

    // Set boundary conditions
    phi[0]=0;
    phi.back()=0;

    // Iteration Variables
    double s1;
    double s2;

    // Calculation of phi and Energy
    for(int k=0; k<u; k++)
    {
        s1 = 0;
        s2 = 0;
        for(int i=1; i<N-1; i++) phi[i] = 0.5*(phi[i+1]+phi[i-1]+pow(h,2)*S[i]);

        for(int j=1; j<N; j++) 
        {
            s1 += pow(phi[j]-phi[j-1], 2);
            if(j!=N)
            {
                s2 += S[j]*phi[j];
            }
        }

        E[k] = s1/(2*h)-h*s2;
    }

    // Calculation of the field
    for(int i=0; i<N; i++)
    {
        switch(i)
        {
            case N-1: field[i] = -(phi[i]-phi[i-1])/h; break;
            case 0: field[i] = -(phi[i+1]-phi[i])/h; break;
            default: field[i] = -(phi[i+1]-phi[i-1])/(2*h); break;
        }
    }

    // Create data directory to save results for plotting later
    namespace fs = std::filesystem;
    fs::path p=fs::current_path();
    fs::create_directory(p+="/data_1d");

    ofstream energy{"data_1d/energy_data_1d.dat"};
    for(int i=0; i<E.size(); i++)
    {
        energy << E[i] << endl;
    }
    energy.close();

    ofstream pot{"data_1d/potential_1d.dat"};
    for(int i=0; i<phi.size(); i++)
    {
        pot << phi[i] << endl;
    }
    pot.close();

    ofstream Field{"data_1d/field_1d.dat"};
    for(int i=0; i<field.size(); i++)
    {
        Field << field[i] << endl;
    }
    Field.close();

    ofstream Source{"data_1d/source_1d.dat"};
    for(int i=0; i<S.size(); i++)
    {
        Source << S[i] << endl;
    }
    Source.close();
    
    return 0;
}