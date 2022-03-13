# Compilation and Execution Instructions

The code in this project is written in a way that is very sensitive to the directory from which compilation and execution commands are run from the shell.

## Instructions

To properly use the code in this directory follow these instructions:

1. Navigate into the `project_1_pde` directory.
2. If you want to compile the source, make sure to output (`g++ -o`) the executable in the provided `obj` directory, otherwise this step can be skipped since binaries are provided.
3. To run the binaries produced use the `./code/cpp/obj/*binary_name*` command from the `project_1_pde` directory. A `data` directory will be produced in the directory this command is run so that is why its important to write this code from the correct directory.
4. To plot the data, after makin sure the data directory is in the `project_1_pde` directory, you can run `python3 code/python/plot.py` to run the plotting script that will produce an `images` directory in the data directory, which will contain figures of the data calculated by the c++ code.
