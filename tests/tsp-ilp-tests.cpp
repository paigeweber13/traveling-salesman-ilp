#include "tsp-ilp-tests.hpp"

void init()
{
  weighted_ugraph g(5, 5);

  // in this graph, shortest tour is 3, 0, 1, 2, 4 with cost 13
  //r, c
  g(0, 1) = 1;
  g(0, 3) = 2;
  g(0, 4) = 7;

  g(1, 2) = 6;
  g(1, 3) = 3;

  g(2, 4) = 4;

  g(3, 4) = 10;

  graphs.push_back(g);
}

TEST_CASE( "Adjacency matrix is converted to glpk problem", 
           "[tsp-conversion]" )
{
  init();

  // REQUIRE( tsp_matrix_to_ilp() == )
}
