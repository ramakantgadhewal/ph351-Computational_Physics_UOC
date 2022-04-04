#pragma once
#include "../../../../universal_code/cpp/src/FuncTools.hpp"
# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <cmath>
# include <ctime>
# include <cstring>
#include "Eigen/Eigenvalues"

// EISPACK - CODE: JOHN BURCKARDT
double pythag ( double a, double b );
double r8_abs ( double x );
double r8_max ( double x, double y );
double r8_min ( double x, double y );
double r8_sign ( double x );
int tql2 ( int n, double d[], double e[], double z[] );
void tred2 ( int n, double a[], double d[], double e[], double z[] );

// QUANTUM - CODE: JASON ANDRONIS
