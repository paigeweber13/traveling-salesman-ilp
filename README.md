# Traveling Salesman ILP
Applying integer linear programming to the traveling salesman problem

Warning: VERY WIP. The only real code is in `src/main-tsp-ilp.cpp`. Everything
else is files for unit tests and libraries and such that I figured I'd need but
didn't get far enough in the project to use

# Dependencies:
 - **[catch](https://github.com/catchorg/Catch2)**: only needed for tests
   (runnable with `make test`). Installable on ubuntu with `sudo apt install
   catch`
 - **[boost](https://www.boost.org/)**: installable on ubuntu with `sudo apt
   install libboost-all-dev`
   - specifically, only the Matrix datatype is used, so you can include that
     alone if you'd rather not install everything

# Running:
## Running Implementation that uses the C/C++ Callable Library
Install dependencies, then run `make run` in the root directory of this
project 

# Problems: 
 - doesn't currently find a feasible solution and I'm not sure why. On paper I
   can make a feasible solution so it must be something with how I've
   programmed it.

# Questions: 
 - How do the `such that` statements map to the parts of the matrix?
 - so the matrix is a list of linear equations, right? So I guess the sum of
   all $x_{ij}$ would be to list every $x_{ij}$ and then say the constraint is
   equal to 2?
   - so only list the edges that don't have that k could be given a constant of
     infinity

# Help from Erik
l_ij is a coefficient in one constraint
x_ij are the variables
 - need one variable for every edge

2nd constraint
 - will need a row for every k 
 - constraint isn't exactly right, should be sum ik and sum kj
 the sum of x_e for an incident edge is 2.
