#include "tsp-ilp.hpp"

int main(){
  int n = 5;
  int e = 7;

  weighted_ugraph g(n, n);

  // in this graph, shortest tour is 3, 0, 1, 2, 4 with cost 13
  //r, c
  g(0, 1) = 1;
  g(0, 3) = 2;
  g(0, 4) = 7;

  g(1, 2) = 6;
  g(1, 3) = 3;

  g(2, 4) = 4;

  g(3, 4) = 10;

  /* declare variables */
  glp_prob *tsp;
  int ia[1+1000], ja[1+1000];
  double ar[1+1000], z, x1, x2;
  /* create problem */
  tsp = glp_create_prob();
  glp_set_prob_name(tsp, "tsp");
  glp_set_obj_dir(tsp, GLP_MIN);

  /* fill problem */
  // rows are constraints (such that)
  // there should be more than this... because there's an exponential number of
  // constraints. For each subset of V

  // every node has to have something going in and something going out
  // row for every node
  glp_add_rows(tsp, n);
  for (unsigned i = 1; i < 1 + n; i++){
    // sum of x_ij is 2 on each of these rows
    glp_set_row_bnds(tsp, i, GLP_FX, 2.0, 0.0);
  }

  // glp_set_row_name(tsp, 2, "eliminating_subtours");
  // glp_set_row_bnds(tsp, 2, GLP_UP, 0.0, s);

  // columns are variables
  glp_add_cols(tsp, pow(n, 2));
  // for (unsigned i = 1; i < 1 + pow(n, 2); i++){
  //   glp_set_col_bnds(tsp, 1, GLP_LO, 0.0, 0.0);
  // }
  ia[0] = 0, ja[0] = 1, ar[0] = 1.0; /* g[0,1] = 1 */
  ia[1] = 0, ja[1] = 3, ar[1] = 2.0; /* g[0,3] = 2 */
  ia[2] = 0, ja[2] = 4, ar[2] = 7.0; /* g[0,4] = 7 */

  ia[3] = 1, ja[3] = 2, ar[3] = 6.0; /* g[1,2] = 6 */
  ia[4] = 1, ja[4] = 3, ar[4] = 3.0; 

  ia[5] = 2, ja[5] = 4, ar[5] = 4.0; 

  ia[6] = 3, ja[6] = 4, ar[6] = 10.0; 
  glp_load_matrix(tsp, 4, ia, ja, ar);

  /* solve problem */
  glp_simplex(tsp, NULL);
  /* recover and display results */
  z = glp_get_obj_val(tsp);
  x1 = glp_get_col_prim(tsp, 1);
  x2 = glp_get_col_prim(tsp, 2);
  printf("z = %g; x1 = %g; x2 = %g\n", z, x1, x2);
  /* housekeeping */
  glp_delete_prob(tsp);
  glp_free_env();

  return 0;
}
