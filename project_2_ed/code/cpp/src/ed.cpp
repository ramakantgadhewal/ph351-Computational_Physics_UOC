#include "ed.hpp"
#include <filesystem>
#include <fstream>
#include <array>

int main()
{
    // Declare and initialize problem variables
    const int size = 5, sites = 10;
    const int time = 100;

    double a[size*size]{
        1,0,0,0,0,
        0,2,0,0,1,
        0,0,1,3,2,
        0,0,3,1,0,
        0,1,2,0,1
    };
    // create array for orthogonal transformation matrix
    double z[size*size];
    // create array for diagonal elements
    double d[size];
    // create array for subdiagonal elements
    double e[size-1];
    e[0] = 1;
    // initial probability amplidute
    double c[size];

    /* 
    tred2 will convert:
        d -> diagonal elements of a
        e -> subdiagonal elements of a
        z -> orthogonal transformation matrix
    */
    tred2(size, a, d, e, z);

    // construct the tridiagonal matrix
    double a2[size*size];
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(i==j) 
            { 
                a2[i*size+j] = d[i];
            }
            else if(j==i-1)
            {
                a2[i*size+j] = e[i];
            }
            else if(j==i+1)
            {
                a2[i*size+j] = e[j];
            }
            else a2[i*size+j] = 0;
        }
    }

    /* 
    tql2 will convert (assuming ierr==0):
        d -> eigenvalues of a
        e -> destroyed
        z -> eigenvectors of a
    */
    int ierr = tql2(size, d, e, z);

    double yr[sites*time];
    double *yi = yr;

    for(int k=0; k<sites; k++)
    {
        for(int t=0; t<time; t++)
        {
            for(int i=0; i<size; i++)
            {
                for(int m=0; m<size; m++)
                {
                    yr[k*sites+t] += c[i]*z[i*size+m]*z[k*size+m]*std::cos(d[m]*t);
                    yi[k*sites+t] -= c[i]*z[i*size+m]*z[k*size+m]*std::sin(d[m]*t);
                }
            }
        }
    }

    std::array<double, sites*time> temp1;
    std::array<double, sites*time> temp2;

    for(int m=0; m<sites*time; m++)
    {
        temp1[m] = yr[m];
        temp2[m] = yi[m];
    }

    if(temp1==temp2){
        std::cout << "Real and Imaginary parts are Equal.\n";
    }

    namespace fs = std::filesystem;
    fs::path p=fs::current_path();
    fs::create_directory(p+="/data");

    std::ofstream YR{"data/YR.dat"};
    for(int k=0; k<sites; k++)
    {
        for(int t=0; t<time; t++)
        {
            YR << yr[k*sites+t] << " ";
        }
        YR << "\n";
    }
    YR.close();

    std::ofstream YI{"data/YI.dat"};
    for(int k=0; k<sites; k++)
    {
        for(int t=0; t<time; t++)
        {
            YI << yi[k*sites+t] << " ";
        }
        YI << "\n";
    }
    YI.close();
    return 0;
};