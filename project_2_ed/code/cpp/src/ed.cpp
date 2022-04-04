#include "ed.hpp"
#include <filesystem>
#include <fstream>

int main()
{
    // Declare and initialize problem variables
    const int sites = 10, time = 100;
    const double hopping = 1;

    std::vector<double> x = functools::linspace<double>(0,sites,sites);

    // Hamiltonian, Kinetic Energy, Potential Energy
    double H[sites*sites], K[sites*sites], V[sites*sites];
    int index;
    double norm = 0;

    // create array for orthogonal transformation matrix
    double z[sites*sites];
    // create array for diagonal elements
    double d[sites];
    // create array for subdiagonal elements
    double e[sites-1];
    e[0] = 1;
    // initial probability amplidute
    double c[sites];

    for(int i=0; i<sites; i++)
    {
        norm += std::exp(-2*std::pow(x[i],2));
        for(int j=0; j<sites; j++)
        {
            index = i+j*sites;
            K[index] = 0;
            V[index] = 0;
            if(i==j) V[index] = 0.5*std::pow(x[i],2);
            if(i==j+1) K[index] = -hopping;
            else if(j==i+1) K[index] = -hopping;
            else if(i==j-1) K[index] = -hopping;
            else if(j==i-1) K[index] = -hopping;
            H[index] = V[index]+K[index];
            std::cout << H[index] << " ";
        }
        std::cout << "\n";
        c[i] = std::exp(-std::pow(x[i],2))/std::sqrt(norm);
    }

    /* 
    tred2 will convert:
        d -> diagonal elements of H
        e -> subdiagonal elements of H
        z -> orthogonal transformation matrix
    */
    tred2(sites, H, d, e, z);

    // construct the tridiagonal matrix
    double a2[sites*sites];
    for(int i=0; i<sites; i++)
    {
        for(int j=0; j<sites; j++)
        {
            index = i+j*sites;
            if(i==j) a2[index] = d[i];
            else if(j==i-1) a2[index] = e[i];
            else if(j==i+1) a2[index] = e[j];
            else a2[index] = 0;
        }
    }

    /* 
    tql2 will convert (assuming ierr==0):
        d -> eigenvalues of H
        e -> destroyed
        z -> eigenvectors of H
    */
    int ierr = tql2(sites, d, e, z);

    double yr[sites*time];
    double yi[sites*time];

    for(int t=0; t<time; t++)
    {
        for(int k=0; k<sites; k++)
        {
            for(int i=0; i<sites; i++)
            {
                for(int m=0; m<sites; m++)
                {
                    yr[k+t*time] += c[i]*z[i+m*sites]*z[k+m*sites]*std::cos(d[m]*t);
                    yi[k+t*time] -= c[i]*z[i+m*sites]*z[k+m*sites]*std::sin(d[m]*t);
                }
            }
        }
    }

    std::cout << std::endl;

    namespace fs = std::filesystem;
    fs::path p=fs::current_path();
    fs::create_directory(p+="/data");

    std::ofstream YR{"data/YR.dat"};
    for(int k=0; k<sites; k++)
    {
        for(int t=0; t<time; t++)
        {
            YR << yr[k+t*time] << " ";
        }
        YR << "\n";
    }
    YR.close();

    std::ofstream YI{"data/YI.dat"};
    for(int k=0; k<sites; k++)
    {
        for(int t=0; t<time; t++)
        {
            YI << yi[k+t*time] << " ";
        }
        YI << "\n";
    }
    YI.close();
    return 0;
};