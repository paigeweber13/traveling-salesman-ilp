// Basic framework and data structures taken from PetterS, who write a MathProg
// tsp implementation available here: https://github.com/PetterS/glpk/blob/master/examples/tsp.mod

param n, integer, >= 3;
set V:= 1..n;
set E, within V cross V;
param c{(i,j) in E};
var x{(i,j) in E}, binary;

minimize total: sum{(i,j) in E} c[i,j] * x[i,j];

s.t.
