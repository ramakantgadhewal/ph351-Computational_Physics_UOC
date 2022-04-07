# Computational Physics Projects

## Introduction

This is a repository of the projects created for the PH351 course. Every project is contained in its own directory, with a report directory for the projects written report and a code directory for all the code used to produce the results presented in said reports.

## Compilation and Execution Instructions

The code in all of the projects is written in a way that is very sensitive to the directory from which compilation and execution commands are run from the shell.

### Instructions

To properly use the code in this directory follow these instructions:

1. Navigate into the `project_*` directory.
2. If you want to compile the source, make sure to output (`g++ -o`) the executable in the provided `obj` directory, otherwise this step can be skipped since binaries are provided.
3. To run the binaries produced use the `./code/cpp/obj/*binary_name*` command from the `project_*` directory. A `data` directory will be produced in the directory this command is run so that is why its important to write this code from the correct directory.
4. To plot the data, after making sure the data directory is in the `project_*` directory, you can run `python code/python/plot.py` to run the plotting script that will produce an `images` directory in the data directory, which will contain figures of the data calculated by the c++ code.

## Dependencies

The repository's dependencies are listed below:

* `python > 3.6`.
* `numpy`.
* `matplotlib`.
* `clang++` or `g++` for compilation with `c++17` support.
