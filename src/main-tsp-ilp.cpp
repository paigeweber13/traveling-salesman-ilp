#include <glpk.h>
#include <limits>
#include <vector>

using namespace std;

int main(){
  size_t n = 5;
  size_t e = 7;
  double inf = std::numeric_limits<double>::infinity();

  // edge list representation of graph
  // one edge: {start_node, end_node, weight}
  // edges are assumed to be bidirectional
  vector<vector<int>> g(e);
  g.push_back({1, 2, 1});
  g.push_back({1, 4, 2});
  g.push_back({1, 5, 7});

  g.push_back({2, 3, 6});
  g.push_back({2, 4, 3});

  g.push_back({3, 5, 4});

  g.push_back({4, 5, 10});

  // in this graph, shortest tour is 3, 0, 1, 2, 4 with cost 13
  //r, c
  // g(0, 1) = 1;
  // g(0, 3) = 2;
  // g(0, 4) = 7;

  // g(1, 2) = 6;
  // g(1, 3) = 3;

  // g(2, 4) = 4;

  // g(3, 4) = 10;

  /* declare c variables */
  glp_prob *tsp;
  int ia[1+1000], ja[1+1000];
  double ar[1+1000];
  size_t index = 1;

  double z, x1, x2;

  /* create problem */
  tsp = glp_create_prob();
  glp_set_prob_name(tsp, "tsp");
  glp_set_obj_dir(tsp, GLP_MIN);

  /* fill problem */
  // columns are variables. So list the edges.
  glp_add_cols(tsp, e);
  for (size_t i = 1; i < 1 + e; i++){
    // every variable is binary
    glp_set_col_kind(tsp, i, GLP_BV);
  }

  // rows are constraints (such that)
  // there should be more than this... because there's an exponential number of
  // constraints. For each subset of V

  // every node has to have something going in and something going out
  // row for every node

  // for each k in V
  glp_add_rows(tsp, n);
  for (size_t k = 1; k < 1 + n; k++){
    // sum of x_kj ks 2 on each of these rows
    glp_set_row_bnds(tsp, k, GLP_FX, 2.0, 0.0);
    for(size_t i = 0; i < g.size(); i++){
      if(g[i][0] == k || g[i][1] == k){
        ia[index] = k, ja[index] = i + 1, ar[index] = g[i][2];
      }
      else{
        ia[index] = k, ja[index] = i + 1, ar[index] = inf;
      }
      index++;
    }
  }

  // glp_set_row_name(tsp, 2, "eliminating_subtours");
  // glp_set_row_bnds(tsp, 2, GLP_UP, 0.0, s);

  // columns are variables
  // glp_add_cols(tsp, pow(n, 2));
  // for (size_t i = 1; i < 1 + pow(n, 2); i++){
  //   glp_set_col_bnds(tsp, 1, GLP_LO, 0.0, 0.0);
  // }

  ia[3] = 1, ja[3] = 2, ar[3] = 6.0; 
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
  // printf("z = %g; x1 = %g; x2 = %g\n", z, x1, x2);
  /* housekeeping */
  glp_delete_prob(tsp);
  glp_free_env();

  return 0;
}
