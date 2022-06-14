#include "mock_exam_2.h"

void run(Eigen::ArrayXd x, Eigen::MatrixXd V, std::string dirname)
{
    Eigen::MatrixXd H(mock_2::sites, mock_2::sites);
    Eigen::MatrixXd T(mock_2::sites, mock_2::sites);
    Eigen::ArrayXd c(mock_2::sites);

    // Set all elements to 0
    H.setZero();
    T.setZero();
    V.setZero();

    for(int i=0; i<H.cols(); i++)
    {
        for(int j=0; j<H.cols(); j++)
        {
            if(i==j-1) T(i,j) = -mock_2::hopping;
            if(j==i-1) T(i,j) = -mock_2::hopping;
            if(i==j+1) T(i,j) = -mock_2::hopping;
            if(j==i+1) T(i,j) = -mock_2::hopping;
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

    Eigen::ArrayXXd yr(mock_2::sites, mock_2::time);
    Eigen::ArrayXXd yi(mock_2::sites, mock_2::time);
    double sum_mr{0}, sum_mi{0};

    for (int k = 0; k < mock_2::sites; k++)
    {
        for (int t = 0; t < mock_2::time; t++)
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
    Eigen::ArrayXXd _mean_x(mock_2::sites, mock_2::time);
    // Column wise operation, multiply every column with x
    _mean_x = P.colwise() * x;
    // every element of mean_x is the mean value of x at a specific timestep
    Eigen::ArrayXd mean_x = _mean_x.colwise().sum();

    // same goes here
    Eigen::ArrayXXd _mean_x_squared(mock_2::sites, mock_2::time);
    _mean_x_squared = P.colwise() * x.array().pow(2);
    Eigen::ArrayXd mean_x_squared = _mean_x_squared.colwise().sum();

    Eigen::ArrayXd variance = mean_x_squared - (mean_x * mean_x);

    /*-----------------------------------------------------------------------------------*/

    // Save files for plotting
    namespace fs = std::filesystem;
    fs::path p = fs::current_path();
    std::string _dirname = "/"+dirname;
    fs::create_directory(p+=_dirname);

    std::ofstream prob(_dirname+"/P.dat" );
    for (int k = 0; k < mock_2::sites; k++)
    {
        for (int t = 0; t < mock_2::time; t++)
        {
            prob << P(k, t) << " ";
        }
        prob << "\n";
    }
    prob.close();

    std::ofstream potential(_dirname+"/V.dat");
    for (int k = 0; k < mock_2::sites; k++)
    {
        potential << V.diagonal()(k) << "\n";
    }
    potential.close();

    std::ofstream initial(_dirname+"/init.dat");
    for (int k = 0; k < mock_2::sites; k++)
    {
        initial << c(k) << "\n";
    }
    initial.close();

    std::ofstream m_x(_dirname+"/mean_x.dat");
    for (int t = 0; t < mock_2::time; t++)
    {
        m_x << mean_x(t) << "\n";
    }
    m_x.close();

    std::ofstream var(_dirname+"/variance.dat");
    for (int t = 0; t < mock_2::time; t++)
    {
        var << variance(t) << "\n";
    }
    var.close();
}

int main()
{
    Eigen::ArrayXd _x = Eigen::ArrayXd::LinSpaced(mock_2::sites,0,mock_2::sites);
    Eigen::MatrixXd V1(mock_2::sites, mock_2::sites);
    Eigen::MatrixXd V2(mock_2::sites, mock_2::sites);
    V1.setZero();
    V2.setZero();

    for(int i=0; i<mock_2::sites; i++)
    {
        for(int j=0; j<mock_2::sites; j++)
        {
            if (i == j)
            {
                V1(i,j) = 0;
                V2(i,j) = std::sin(2*M_PI*i/10);
            }
        }
    }

    run(_x, V1, "m2_data_V1");
    run(_x, V2, "m2_data_V2");

    return 0;
}
