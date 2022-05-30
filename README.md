# Computational Physics Projects

## Introduction

This is a repository of the projects created for the PH351 course. Every project is contained in its own directory, with a report directory for the projects written report and a code directory for all the code used to produce the results presented in said reports.

## Compilation and Execution Instructions

The code in all of the projects is written in a way that is very sensitive to the directory from which compilation and execution commands are run from the shell. To properly use the code in this directory follow these instructions:

1. Navigate into the `project_*` directory.
2. Configure CMake using the command `cmake -S code/cpp -B build -G Ninja`.
3. If you want to compile the source, use the command `cmake --build build --config Release --target all --`, otherwise this step can be skipped since binaries are provided.
4. To run the binaries produced use the `./build/*binary_name*` command from the `project_*` directory. A `data` directory will be produced in the directory this command is run so that is why its important to write this code from the correct directory.
5. To plot the data, after making sure the data directory is in the `project_*` directory, you can run `python code/python/plot.py` to run the plotting script that will produce an `images` directory in the data directory, which will contain figures of the data calculated by the c++ code.

## Dependencies

The repository's dependencies are listed below:

* python > 3.6
* C++ compiler with C++17 support
* [numpy](https://numpy.org/)
* [matplotlib](https://matplotlib.org/)
* [pandas](https://pandas.pydata.org/)
* [cmake](https://cmake.org/download/)
* [Ninja](https://ninja-build.org/)
