#pragma once

#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <glpk.h>
#include <math.h>

using namespace std;
namespace ublas = boost::numeric::ublas;

typedef ublas::triangular_matrix<double, ublas::upper> weighted_ugraph;
typedef ublas::triangular_matrix<double, ublas::upper> edge_selection;

void tsp_matrix_to_ilp();
