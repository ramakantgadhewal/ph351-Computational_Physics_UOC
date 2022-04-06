# Computational Physics: Solving the Poisson Equation in 1D & 2D
<div align="right">Iasonas Andronis - ph4783 (UOC Department of Physics) </div>
<br></br>

## Introduction

The [poisson equation](https://en.wikipedia.org/wiki/Poisson%27s_equation) is a famous PDE that is used to derive solutions to various physical problems. One such problem is deriving the charge potential and electric field of a system, given some initial and boundary conditions and a source charge distribution. All of the units of the variables of the problems presented below are dimensionless.

## 1D Problem

A simple problem that can be solved with the poisson equation is finding the electric potential on a 1 dimensional rod that is insulated on each end. The definition of this problem is:

<!-- $$
-\frac{d^2\phi(x)}{dx^2} = S(x)\; ,
\\\;
\\
\phi(0)=\phi(1)=0\; ,
\\\;
\\
S(x) = 12x^2
$$ --> 

<div align="center"><img style="background: white;" src="https://render.githubusercontent.com/render/math?math=-%5Cfrac%7Bd%5E2%5Cphi(x)%7D%7Bdx%5E2%7D%20%3D%20S(x)%5C%3B%20%2C%0A%5C%5C%5C%3B%0A%5C%5C%0A%5Cphi(0)%3D%5Cphi(1)%3D0%5C%3B%20%2C%0A%5C%5C%5C%3B%0A%5C%5C%0AS(x)%20%3D%2012x%5E2"></div>

with <!-- $\phi(x)$ --> <img style="transform: translateY(0.1em); background: white;" src="https://render.githubusercontent.com/render/math?math=%5Cphi(x)"> being a real valued function representing the electric potential and <!-- $S(x)$ --> <img style="transform: translateY(0.1em); background: white;" src="https://render.githubusercontent.com/render/math?math=S(x)"> being the source charge distribution. The solution of this problem is provided from the course notes and is <!-- $\phi(x)=x(1-x^3)$ --> <img style="transform: translateY(0.1em); background: white;" src="https://render.githubusercontent.com/render/math?math=%5Cphi(x)%3Dx(1-x%5E3)"> and the energy of the system should asymptotically converge to the value <!-- $E=-0.64286$ --> <img style="transform: translateY(0.1em); background: white;" src="https://render.githubusercontent.com/render/math?math=E%3D-0.64286">. We can see the numerical solution in the figures below, along with the analytical solution provided.

<div style="text-align:center">
<img src="../data_1d/images/energypotential_1d_plot.png"/>
</div>
<div style="text-align:center">
<b>Figure 1 - </b> Left: Energy of the system as a function of the timesteps. Right: Electric Potential as a function of x. The red dashed lines corresponds to the analytical result provided in the notes.
</div>

<div style="text-align:center">
<img src="../data_1d/images/field_1d_plot.jpg" width="500"/>
</div>
<div style="text-align:center">
<b>Figure 2 - </b> The electric Field produced by the final charge distribution.
</div>

<div style="text-align:center">
<img src="../data_1d/images/source_1d_plot.jpg" width="500"/>
</div>
<div style="text-align:center">
<b>Figure 4 - </b> The initial charge distribution on the rod.
</div>
<br></br>

The electric potential & field that are shown represent their respective quantities after 10000 repetitions. As we can surmise the numerical solution is producing satisfactory results.
<br></br>

## 2D Problem

The poisson equation presented in the previous section is a special case of the generalized equation:

<!-- $$
\nabla^2 \phi(x,y) = S(x,y)
$$ --> 

<div align="center"><img style="background: white;" src="https://render.githubusercontent.com/render/math?math=%5Cnabla%5E2%20%5Cphi(x%2Cy)%20%3D%20S(x%2Cy)"></div>

where <!-- $\nabla^2$ --> <img style="transform: translateY(0.1em); background: white;" src="https://render.githubusercontent.com/render/math?math=%5Cnabla%5E2"> is the laplacian. We can define a source distribution:

<!-- $$
S(x,y) = sin(x^2+y^2)
$$ --> 

<div align="center"><img style="background: white;" src="https://render.githubusercontent.com/render/math?math=S(x%2Cy)%20%3D%20sin(x%5E2%2By%5E2)"></div>

which we can see in . The boundary conditions are, for a cartesian domain <!-- $\Omega$ --> <img style="transform: translateY(0.1em); background: white;" src="https://render.githubusercontent.com/render/math?math=%5COmega"> where <!-- $\Omega\subset\R^2$ --> <img style="transform: translateY(0.1em); background: white;" src="https://render.githubusercontent.com/render/math?math=%5COmega%5Csubset%5CR%5E2">, <!-- $\phi(x,y)=0$ --> <img style="transform: translateY(0.1em); background: white;" src="https://render.githubusercontent.com/render/math?math=%5Cphi(x%2Cy)%3D0"> on <!-- $\partial\Omega$ --> <img style="transform: translateY(0.1em); background: white;" src="https://render.githubusercontent.com/render/math?math=%5Cpartial%5COmega">, where <!-- $\partial\Omega$ --> <img style="transform: translateY(0.1em); background: white;" src="https://render.githubusercontent.com/render/math?math=%5Cpartial%5COmega"> is the boundary of <!-- $\Omega$ --> <img style="transform: translateY(0.1em); background: white;" src="https://render.githubusercontent.com/render/math?math=%5COmega">. The resulting numerical solution is presented in the figures below.

<div style="text-align:center">
<img src="../data_2d/images/energy_2d_plot.jpg" width="500">
</div>
<div style="text-align:center">
<b>Figure 5 - </b> Energy of the system as a function of the timesteps. It assymptotically converges to the value 33.0973.
</div>

<div style="text-align:center">
<img src="../data_2d/images/field_streamplot.jpg" width="500" alt="source_distribution">
</div>
<div style="text-align:center">
<b>Figure 6 - </b> Stream lines of the electric Field produced by the final charge distribution.
</div>

<div style="text-align:center">
<img src="../data_2d/images/potential_2d_plot.jpg" width="500">
</div>
<div style="text-align:center">
<b>Figure 7 - </b> The electric potential after 10000 timesteps.
</div>

<div style="text-align:center">
<img src="../data_2d/images/fieldx_2d_plot.jpg" width="500">
</div>
<div style="text-align:center">
<b>Figure 8 - </b> The x component of the electric field after 10000 timesteps.
</div>

<div style="text-align:center">
<img src="../data_2d/images/fieldy_2d_plot.jpg" width="500">
</div>
<div style="text-align:center">
<b>Figure 9- </b> The x component of the electric field after 10000 timesteps.
</div>

<div style="text-align:center">
<img src="../data_2d/images/source_2d_plot.jpg" width="500">
</div>
<div style="text-align:center">
<b>Figure 10 - </b> The source charge distribution.
</div>
