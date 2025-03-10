/**
 * @author Ethan Okamura (eokamura)
 * @file find_paths.h
 * @brief declaring the member functions and variables for
 *        the find paths class
 */

#include <vector>
#include <iostream>
#include <limits>
#include <iomanip>

class FindPaths {
 private:
  int n;
  std::vector<std::vector<int>> d;
  std::vector<std::vector<int>> p;
  const int INF = std::numeric_limits<int>::max();
  void floyd_warshall();
  void init_parent();
  void print_matrix(char, std::vector<std::vector<int>> matrix);
  void print_formatted_matrix(char, std::vector<std::vector<int>> matrix);
 public:
  FindPaths();
  FindPaths(std::vector<std::vector<int>>&);
  ~FindPaths();
  void print(bool);
  void find_paths();
};