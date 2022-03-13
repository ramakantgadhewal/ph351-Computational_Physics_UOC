#include "../../../../universal_code/cpp/src/FuncTools.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
#include <filesystem>

int main()
{
    // Initialize Grid Variables
    const int reps = 2000;
    constexpr double xmin{-5}, xmax{5};
    constexpr double ymin{-5}, ymax{5};
    constexpr int N = 120;
    constexpr int M = 120;
    constexpr double h = (xmax-xmin)/N;
    functools::Matrix<double> field_x = functools::zeros_2d<double>(N, M);
    functools::Matrix<double> field_y = functools::zeros_2d<double>(N, M);
    functools::Matrix<double> S = functools::zeros_2d<double>(N, M);
    std::vector<double> E = functools::zeros_1d<double>(reps);

    std::vector<double> x = functools::linspace<double>(xmin, xmax, N);
    std::vector<double> y = functools::linspace<double>(ymin, ymax, M);

    functools::Matrix<double> phi = functools::ones_2d<double>(N, M);

    // Initial Conditions for the Source
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            S[S.Index(i,j)] = std::sin(std::pow(x[i],2)+std::pow(y[j],2));
        }
    }

    // Boundary Conditions
    for(int i=0; i<phi.NumColumns(); i++)
    {
        for(int j=0; j<phi.NumRows(); j++)
        {
            if(i==0) phi[phi.Index(i,j)] = 0;
            else if(i==phi.NumColumns()-1) phi[phi.Index(i,j)] = 0;
            else if(j==0) phi[phi.Index(i,j)] = 0;
            else if(j==phi.NumRows()-1) phi[phi.Index(i,j)] = 0;
        }
    }

    // Declaration of helper variables
    double s1;
    double s2;
    int helper_i;
    int helper_j;

    for(int k=0; k<reps; k++)
    {
        s1=0;
        s2=0;
        
        for(int i=1; i<N-1; i++)
        {
            for(int j=1; j<M-1; j++)
            {
                phi[phi.Index(i,j)] = 0.25*(phi[phi.Index(i+1,j)]
                    +phi[phi.Index(i-1,j)]+phi[phi.Index(i,j+1)]
                    +phi[phi.Index(i,j-1)]+std::pow(h,2)*S[S.Index(i,j)]);
                helper_i = i;
                helper_j = j;
            }
        }

        for(int w=1; w<N; w++)
        {
            for(int l=1; l<M; l++)
            {
                s1 += std::pow((phi[phi.Index(w,l)]-phi[phi.Index(w-1,l)]),2)
                    +std::pow((phi[phi.Index(w,l)]-phi[phi.Index(w,l-1)]),2);
            }
        }

        for(int t=1; t<N-1; t++)
        {
            for(int r=1; r<M-1; r++)
            {
                s2 += phi[phi.Index(t,r)]*S[S.Index(helper_i,helper_j)];
            }
        }

        E[k]=0.5*s1-std::pow(h,2)*s2;
    }

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            if(i==N-1) field_x[field_x.Index(i,j)] = -(phi[phi.Index(i,j)]-phi[phi.Index(i-1,j)])/h;
            else if(i==0)
            {
                field_x[field_x.Index(i,j)] = -(phi[phi.Index(i+1,j)]-phi[phi.Index(i,j)])/h;
                field_y[field_y.Index(i,j)] = -(phi[phi.Index(i,j+1)]-phi[phi.Index(i,j)])/h;
            }
            else field_x[field_x.Index(i,j)] = -(phi[phi.Index(i+1,j)]-phi[phi.Index(i-1,j)])/(2*h);

            if(j==M-1) field_y[field_y.Index(i,j)] = -(phi[phi.Index(i,j)]-phi[phi.Index(i,j-1)])/h;
            else field_y[field_y.Index(i,j)] = -(phi[phi.Index(i,j+1)]-phi[phi.Index(i,j-1)])/(2*h);
        }
    }

    // for(int i=0; i<N; i++)
    // {
    //     for(int j=0; j<M; j++)
    //     {
    //         if(j==M-1) field_y[field_y.Index(i,j)] = -(phi[phi.Index(i,j)]-phi[phi.Index(i,j-1)])/h;
    //         else if(i==0) field_y[field_y.Index(i,j)] = -(phi[phi.Index(i,j+1)]-phi[phi.Index(i,j)])/h;
    //         else field_y[field_y.Index(i,j)] = -(phi[phi.Index(i,j+1)]-phi[phi.Index(i,j-1)])/(2*h);
    //     }
    // }

    // Create data directory to save results for plotting later
    namespace fs = std::filesystem;
    fs::path p=fs::current_path();
    fs::create_directory(p+="/data_2d");

    std::ofstream energy{"data_2d/energy_data_2d.dat"};
    for(int i=0; i<E.size(); i++)
    {
        energy << E[i] << std::endl;
    }
    energy.close();

    std::ofstream pot{"data_2d/potential_2d.dat"};
    for(int i=0; i<phi.NumColumns(); i++)
    {
        pot << std::endl;
        for(int j=0; j<phi.NumRows(); j++)
        {
            pot << phi[phi.Index(i,j)] << " ";
        }
    }
    pot.close();

    std::ofstream Fieldx{"data_2d/fieldx_2d.dat"};
    for(int i=1; i<field_x.NumColumns(); i++)
    {
        Fieldx << std::endl;
        for(int j=1; j<field_x.NumRows(); j++)
        {
            Fieldx << field_x[field_x.Index(i,j)] << " ";
        }
    }
    Fieldx.close();

    std::ofstream Fieldy{"data_2d/fieldy_2d.dat"};
    for(int i=1; i<field_y.NumColumns(); i++)
    {
        Fieldy << std::endl;
        for(int j=1; j<field_y.NumRows(); j++)
        {
            Fieldy << field_y[field_y.Index(i,j)] << " ";
        }
    }
    Fieldy.close();

    std::ofstream Source{"data_2d/source_2d.dat"};
    for(int i=0; i<S.NumColumns(); i++)
    {
        Source << std::endl;
        for(int j=0; j<S.NumRows(); j++)
        {
            Source << S[S.Index(i,j)] << " ";
        }
    }
    Source.close();

    return 0;
}