#include "Eigen/Core"
#include "Eigen/Eigenvalues"
#include <iostream>
#include <cmath>
#include <filesystem>
#include <fstream>

int main()
{
    // Declare and initialize problem variables
    const int sites = 50, time = 100;
    const double hopping = 1;
    const Eigen::ArrayXf x = Eigen::ArrayXf::LinSpaced(sites,-1,1);
    Eigen::MatrixXf H(sites, sites);
    Eigen::MatrixXf T(sites, sites);
    Eigen::MatrixXf V(sites, sites);
    Eigen::ArrayXf c(sites);

    // Set all elements to 0
    H.setZero();
    T.setZero();
    V.setZero();

    for(int i=0; i<H.cols(); i++)
    {
        for(int j=0; j<H.cols(); j++)
        {
            if(i==j) V(i,j) = 0.5*std::pow(x(i),2);
            if(i==j-1) T(i,j) = -hopping;
            if(j==i-1) T(i,j) = -hopping;
            if(i==j+1) T(i,j) = -hopping;
            if(j==i+1) T(i,j) = -hopping;
            H(i,j) = T(i,j)+V(i,j);
            c(i) = std::exp(-std::pow(x(i), 2));
        }
    }
    
    // Normalize initial coefficients
    c.matrix().normalize();

    // Derive eigenvectors and eigenvalues from Hamiltonian
    Eigen::EigenSolver<Eigen::MatrixXf> es(H);
    Eigen::MatrixXf eigvecs = es.eigenvectors().real();
    Eigen::VectorXf eigvals = es.eigenvalues().real();

    Eigen::ArrayXXf yr(sites, time);
    Eigen::ArrayXXf yi(sites, time);
    float sum_mr{0}, sum_mi{0};

    for (int k = 0; k < sites; k++)
    {
        for (int t = 0; t < time; t++)
        {
            sum_mr = 0;
            sum_mi = 0;
            for (int i = 0; i < eigvecs.cols(); i++)
            {
                for (int m = 0; m < eigvecs.rows(); m++)
                {
                    float temp = eigvals(m) * t;
                    sum_mr += c(i) * eigvecs(i, m) * eigvecs(k, m) * std::cos(temp);
                    sum_mi += c(i) * eigvecs(i, m) * eigvecs(k, m) * std::sin(temp);
                }
            }
            yr(k, t) = sum_mr;
            yi(k, t) = -sum_mi;
        }
    }

    Eigen::ArrayXXf P = yr.abs().pow(2) + yi.abs().pow(2);

    // Arrays with _ in front are helper arrays
    Eigen::ArrayXXf _mean_x(sites, time);
    // Column wise operation, multiply every column with x
    _mean_x = P.colwise() * x;
    // every element of mean_x is the mean value of x at a specific timestep
    Eigen::ArrayXf mean_x = _mean_x.colwise().sum();

    // same goes here
    Eigen::ArrayXXf _mean_x_squared(sites, time);
    _mean_x_squared = P.colwise() * x.array().pow(2);
    Eigen::ArrayXf mean_x_squared = _mean_x_squared.colwise().sum();

    Eigen::ArrayXf variance = mean_x_squared - (mean_x * mean_x);

    /*-----------------------------------------------------------------------------------*/

    // Save files for plotting
    namespace fs = std::filesystem;
    fs::path p = fs::current_path();
    fs::create_directory(p+="/data");

    std::ofstream prob{ "data/P.dat" };
    for (int k = 0; k < sites; k++)
    {
        for (int t = 0; t < time; t++)
        {
            prob << P(k, t) << " ";
        }
        prob << "\n";
    }
    prob.close();

    std::ofstream potential{ "data/V.dat" };
    for (int k = 0; k < sites; k++)
    {
        potential << V.diagonal()(k) << "\n";
    }
    potential.close();

    std::ofstream initial{ "data/init.dat" };
    for (int k = 0; k < sites; k++)
    {
        initial << c(k) << "\n";
    }
    initial.close();

    std::ofstream m_x{ "data/mean_x.dat" };
    for (int t = 0; t < time; t++)
    {
        m_x << mean_x(t) << "\n";
    }
    m_x.close();

    std::ofstream var{ "data/variance.dat" };
    for (int t = 0; t < time; t++)
    {
        var << variance(t) << "\n";
    }
    var.close();

    return 0;
}