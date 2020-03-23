# Traveling Salesman ILP
Applying integer linear programming to the traveling salesman problem

Warning: VERY WIP. The only real code is in `tsp.mod` and
`src/main-tsp-ilp.cpp`. Everything else is files for unit tests and libraries
and such that I figured I'd need but didn't get far enough in the project to
use

# Dependencies:
 - **[catch](https://github.com/catchorg/Catch2)**: installable on ubuntu with
   `sudo apt install catch`
 - **[boost](https://www.boost.org/)**: installable on ubuntu with `sudo apt
   install libboost-all-dev`
   - specifically, only the Matrix datatype is used, so you can include that
     alone if you'd rather not install everything

# Running:
## Using the Mathprog Implementation
Make sure glpk utils are installed (specifically glpsol) and run `make glpsol`
in the root of this project.

## Using Implementation that uses the C/C++ Callable Library
Install dependencies, then run `make test` in the root directory of this
project 

# Questions: 
 - How do the `such that` statements map to the parts of the matrix?
 - so the matrix is a list of linear equations, right? So I guess the sum of
   all $x_{ij}$ would be to list every $x_{ij}$ and then say the constraint is
   equal to 2?
