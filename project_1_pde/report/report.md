# Computational Physics: Solving the Poisson Equation in 1D & 2D

## Introduction

The [poisson equation](https://en.wikipedia.org/wiki/Poisson%27s_equation) is a famous PDE that is used to derive solutions to various physical problems. One such problem is deriving the charge potential and electric field of a system, given some initial and boundary conditions and a source charge distribution. 

## 1D Problem

A simple problem that can be solved with the poisson equation is finding the electric potential on a 1 dimensional rod that is insulated on each end. The definition of this problem is:

$$
-\frac{d^2\phi(x)}{dx^2} = S(x)\; ,
\\\;
\\
\phi(0)=\phi(1)=0\; ,
\\\;
\\
S(x) = 12x^2
$$

with $\phi(x)$ being a real valued function representing the electric potential and $S(x)$ being the source charge distribution. The solution of this problem is provided from the course notes and is $\phi(x)=x(1-x^3)$ and the energy of the system should asymptotically converge to the value $E=-0.64286$. We can see the numerical solution in the figures below, along with the analytical solution provided.

![image](energy_1d_plot.jpg "../../../data_1d/images/energy_1d_plot.jpg")
