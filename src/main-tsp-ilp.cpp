#include <glpk.h>
#include <iostream>
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
  vector<vector<int>> g(e + 1);
  g[1] = {1, 2, 1};
  g[2] = {1, 4, 2};
  g[3] = {1, 5, 7};

  g[4] = {2, 3, 6};
  g[5] = {2, 4, 3};

  g[6] = {3, 5, 4};

  g[7] = {4, 5, 10};

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
  const size_t arr_size = 1000;
  glp_prob *tsp;
  int ia[1+arr_size], ja[1+arr_size];
  double ar[1+arr_size];
  size_t index = 1;

  // make all arrays 0, will be useful later when we print things
  for (size_t i = 0; i < 1 + arr_size; i++){
    ia[i] = 0;
    ja[i] = 0;
    ar[i] = 0.0;
  }

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
    glp_set_row_name(tsp, k,
      ("ensuring connectedness for k = " + to_string(k)).c_str());

    for(size_t i = 1; i < 1 + e; i++){
      if(g[i][0] == int(k) || g[i][1] == int(k)){
        // don't use the weights, just use 1 because we want x_ij to be summed
        // here, not the weight
        ia[index] = k, ja[index] = i, ar[index] = 1;
      }
      else{
        ia[index] = k, ja[index] = i, ar[index] = 0;
      }
      index++;
    }
  }

  glp_load_matrix(tsp, 4, ia, ja, ar);

  /* solve problem */
  glp_simplex(tsp, NULL);
  /* recover and display results */
  double z = glp_get_obj_val(tsp);
  cout << "total weight of tour: " << z << "\n";

  cout << "\nMatrix Entries:\n";
  for(size_t i = 1; i < 1 + arr_size; i++){
    if (ia[i] != 0 || ja[i] != 0){
      cout << "matrix entry " << ia[i] << "," << ja[i] << " = " << ar[i] 
           << "\n";
    }
  }

  cout << "\nVariables:\n";
  for(size_t i = 1; i < size_t(glp_get_num_cols(tsp)) + 1; i++){
    double x = glp_get_col_prim(tsp, i);
    double y = glp_get_col_dual(tsp, i);
    double s = glp_get_col_stat(tsp, i);
    // I believe these are each of the variable values
    cout << "column " << i << " has primal value " << x << "\n";
    cout << "column " << i << " has dual value " << y << "\n";
    cout << "column " << i << " has status " << s << "\n";
  }

  cout << "\nConstraints:\n";
  for(size_t i = 1; i < size_t(glp_get_num_rows(tsp)) + 1; i++){
    double x = glp_get_row_prim(tsp, i);
    double y = glp_get_row_dual(tsp, i);
    double s = glp_get_row_stat(tsp, i);
    double c = glp_get_obj_coef(tsp, i);
    cout << "row " << i << " has primal value " << x << "\n";
    cout << "row " << i << " has dual value " << y << "\n";
    cout << "row " << i << " has status " << s << "\n";
    cout << "row " << i << " has coefficient" << c << "\n";
  }

  /* housekeeping */
  glp_delete_prob(tsp);
  glp_free_env();

  return 0;
}
