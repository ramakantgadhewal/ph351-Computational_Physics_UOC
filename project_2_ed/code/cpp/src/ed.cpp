#include "Eigen/Core"
#include "Eigen/Eigenvalues"
#include <iostream>
#include <cmath>
#include <filesystem>
#include <fstream>

// int oldmain();

int main()
{
    // Declare and initialize problem variables
    const int sites = 100, time = 100;
    const double hopping = 0.4;
    const Eigen::VectorXf x = Eigen::VectorXf::LinSpaced(sites,-1,1);
    Eigen::MatrixXf H(sites, sites);
    Eigen::MatrixXf T(sites, sites);
    Eigen::MatrixXf V(sites, sites);
    Eigen::VectorXf c(sites);

    H.setZero();
    T.setZero();
    V.setZero();

    for(int i=0; i<H.cols(); i++)
    {
        for(int j=0; j<H.cols(); j++)
        {
            if(i==j) V(i,j) = 0.5*std::pow(x[i],2);
            if(i==j-1) T(i,j) = -hopping;
            if(j==i-1) T(i,j) = -hopping;
            if(i==j+1) T(i,j) = -hopping;
            if(j==i+1) T(i,j) = -hopping;
            H(i,j) = T(i,j)+V(i,j);
            c(i) = std::exp(-std::pow(x(i),2));
        }
    }

    c.normalize(); 
    Eigen::EigenSolver<Eigen::MatrixXf> es(H);
    Eigen::MatrixXf eigvecs = es.eigenvectors().real();
    Eigen::VectorXf eigvals = es.eigenvalues().real();

    Eigen::MatrixXf yr = Eigen::MatrixXf::Zero(sites,time);
    Eigen::MatrixXf yi = Eigen::MatrixXf::Zero(sites,time);

    for(int t=0; t<time; t++)
    {
        for(int k=0; k<sites; k++)
        {
            for(int i=0; i<sites; i++)
            {
                for(int m=0; m<sites; m++)
                {
                    yr(k,t) += c(i)*eigvecs(i,m)*eigvecs(k,m)*std::cos(eigvals(m)*t);
                    yi(k,t) -= c(i)*eigvecs(i,m)*eigvecs(k,m)*std::sin(eigvals(m)*t);
                }
            }
        }
    }

    namespace fs = std::filesystem;
    fs::path p=fs::current_path();
    fs::create_directory(p+="/data");

    std::ofstream YR{"data/YR.dat"};
    for(int k=0; k<sites; k++)
    {
        for(int t=0; t<time; t++)
        {
            YR << yr(k,t) << " ";
        }
        YR << "\n";
    }
    YR.close();

    std::ofstream YI{"data/YI.dat"};
    for(int k=0; k<sites; k++)
    {
        for(int t=0; t<time; t++)
        {
            YI << yi(k,t) << " ";
        }
        YI << "\n";
    }
    YI.close();
    return 0;
};

// int oldmain()
// {
//     // Declare and initialize problem variables
//     const int sites = 10, time = 100;
//     const double hopping = 1;
//     // grid initialization
//     std::vector<double> x = functools::linspace<double>(0,sites,sites);
//     // Hamiltonian, Kinetic Energy, Potential Energy
//     double H[sites*sites], K[sites*sites], V[sites*sites];
//     int index;
//     double norm = 0;

//     // create array for orthogonal transformation matrix
//     double z[sites*sites];
//     // create array for diagonal elements
//     double d[sites];
//     // create array for subdiagonal elements
//     double e[sites-1];
//     e[0] = 1;
//     // initial probability amplidute
//     double c[sites];

//     for(int i=0; i<sites; i++)
//     {
//         for(int j=0; j<sites; j++)
//         {
//             index = i+j*sites;
//             K[index] = 0;
//             V[index] = 0;
//             if(i==j) V[index] = 0.5*std::pow(x[i],2);
//             if(i==j+1) K[index] = -hopping;
//             else if(j==i+1) K[index] = -hopping;
//             else if(i==j-1) K[index] = -hopping;
//             else if(j==i-1) K[index] = -hopping;
//             H[index] = V[index]+K[index];
//             std::cout << H[index] << " ";
//         }
//         std::cout << "\n";
//         norm += std::exp(-2*std::pow(x[i],2));
//     }

//     for(int i=0; i<sites; i++)
//     {
//         c[i] = std::exp(-std::pow(x[i],2))/std::sqrt(norm);
//     }
//     /* 
//     tred2 will convert:
//         d -> diagonal elements of H
//         e -> subdiagonal elements of H
//         z -> orthogonal transformation matrix
//     */
//     // tred2(sites, H, d, e, z);

//     // // construct the tridiagonal matrix
//     // double a2[sites*sites];
//     // for(int i=0; i<sites; i++)
//     // {
//     //     for(int j=0; j<sites; j++)
//     //     {
//     //         index = i+j*sites;
//     //         if(i==j) a2[index] = d[i];
//     //         else if(j==i-1) a2[index] = e[i];
//     //         else if(j==i+1) a2[index] = e[j];
//     //         else a2[index] = 0;
//     //     }
//     // }

//     /* 
//     tql2 will convert (assuming ierr==0):
//         d -> eigenvalues of H
//         e -> destroyed
//         z -> eigenvectors of H
//     */
//     int ierr = tql2(sites, d, e, z);

//     double yr[sites][time];
//     double yi[sites][time];

//     for(int t=0; t<time; t++)
//     {
//         for(int k=0; k<sites; k++)
//         {
//             for(int i=0; i<sites; i++)
//             {
//                 for(int m=0; m<sites; m++)
//                 {
//                     yr[k][t] += c[i]*z[i+m*sites]*z[k+m*sites]*std::cos(d[m]*t);
//                     yi[k][t] -= c[i]*z[i+m*sites]*z[k+m*sites]*std::sin(d[m]*t);
//                 }
//             }
//         }
//     }

//     std::cout << std::endl;

//     namespace fs = std::filesystem;
//     fs::path p=fs::current_path();
//     fs::create_directory(p+="/data");

//     std::ofstream YR{"data/YR.dat"};
//     for(int k=0; k<sites; k++)
//     {
//         for(int t=0; t<time; t++)
//         {
//             YR << yr[k][t] << " ";
//         }
//         YR << "\n";
//     }
//     YR.close();

//     std::ofstream YI{"data/YI.dat"};
//     for(int k=0; k<sites; k++)
//     {
//         for(int t=0; t<time; t++)
//         {
//             YI << yi[k][t] << " ";
//         }
//         YI << "\n";
//     }
//     YI.close();
//     return 0;
// };