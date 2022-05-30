#include "../../../../universal_code/cpp/src/Eigen/Core"
#include "../../../../universal_code/cpp/src/Eigen/Eigenvalue"
#include <iostream>
#include <cmath>
#include <filesystem>
#include <fstream>

int main()
{
    // Declare and initialize problem variables
    const int sites = 50, time = 100;
    const double hopping = 4;
    const Eigen::ArrayXd x = Eigen::ArrayXd::LinSpaced(sites,0,sites);
    Eigen::MatrixXd H(sites, sites);
    Eigen::MatrixXd T(sites, sites);
    Eigen::MatrixXd V(sites, sites);
    Eigen::ArrayXd c(sites);

    // Set all elements to 0
    H.setZero();
    T.setZero();
    V.setZero();

    for(int i=0; i<H.cols(); i++)
    {
        for(int j=0; j<H.cols(); j++)
        {
            if (i == j)
            {
                if (i>=10 && i<=40) V(i, j) = 3;
                else V(i,j) = 0;
            }
            if(i==j-1) T(i,j) = -hopping;
            if(j==i-1) T(i,j) = -hopping;
            if(i==j+1) T(i,j) = -hopping;
            if(j==i+1) T(i,j) = -hopping;
            H(i,j) = T(i,j)+V(i,j);
        }
        c(i) = std::exp(-0.04*std::pow(x(i)-25,2));
    }
    
    // Normalize initial coefficients
    c.matrix().normalize();

    // Derive eigenvectors and eigenvalues from Hamiltonian
    Eigen::EigenSolver<Eigen::MatrixXd> es(H);
    Eigen::MatrixXd eigvecs = es.eigenvectors().real();
    Eigen::VectorXd eigvals = es.eigenvalues().real();

    Eigen::ArrayXXd yr(sites, time);
    Eigen::ArrayXXd yi(sites, time);
    double sum_mr{0}, sum_mi{0};

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
                    double temp = eigvals(m) * t;
                    sum_mr += c(i) * eigvecs(i, m) * eigvecs(k, m) * std::cos(temp);
                    sum_mi += c(i) * eigvecs(i, m) * eigvecs(k, m) * std::sin(temp);
                }
            }
            yr(k, t) = sum_mr;
            yi(k, t) = -sum_mi;
        }
    }

    Eigen::ArrayXXd P = yr.abs().pow(2) + yi.abs().pow(2);

    // Arrays with _ in front are helper arrays
    Eigen::ArrayXXd _mean_x(sites, time);
    // Column wise operation, multiply every column with x
    _mean_x = P.colwise() * x;
    // every element of mean_x is the mean value of x at a specific timestep
    Eigen::ArrayXd mean_x = _mean_x.colwise().sum();

    // same goes here
    Eigen::ArrayXXd _mean_x_squared(sites, time);
    _mean_x_squared = P.colwise() * x.array().pow(2);
    Eigen::ArrayXd mean_x_squared = _mean_x_squared.colwise().sum();

    Eigen::ArrayXd variance = mean_x_squared - (mean_x * mean_x);

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
