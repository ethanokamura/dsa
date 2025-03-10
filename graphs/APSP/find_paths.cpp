/**
 * @author Ethan Okamura
 * @file find_paths.cpp
 * @brief implementing member functions for the find paths class
 */

#include "find_paths.h"

FindPaths::FindPaths() : n(0) {}
FindPaths::FindPaths(std::vector<std::vector<int>>& matrix) {
  n = matrix.size();
  d = matrix;
  p = matrix;
}
FindPaths::~FindPaths() {}

void FindPaths::find_paths() {
  init_parent();
  floyd_warshall();
}

void FindPaths::print(bool formatted) {
  if (formatted) {
    print_formatted_matrix('D',d);
    std::cout << '\n';
    print_formatted_matrix('P',p);  
  } else {
    print_matrix('D',d);
    std::cout << '\n';
    print_matrix('P',p);
  }
}

void FindPaths::init_parent() {
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == j || d[i][j] == INF) {
          p[i][j] = INF;
        } else {
          p[i][j] = i + 1;
        }
      }
    }
  }
}

void FindPaths::floyd_warshall() {
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (d[i][k] != INF &&
            d[k][j] != INF &&
            d[i][j] > (d[i][k] + d[k][j]))
        {
          p[i][j] = p[k][j];
          d[i][j] = d[i][k] + d[k][j];
        }
      }
    }
  }
}

void FindPaths::print_formatted_matrix(char c, std::vector<std::vector<int>> matrix) {
  int y {0};
  for (int i = 0; i < n + 1; i++) {
    for (int j = 0; j < n + 1; j++) {
      if (i == 0 && j == 0) {
        std::cout << std::setw(4) << c;
      } else if (i == 0 && j != 0) {
        std::cout << std::setw(3) << j << ":";
      } else if (i != 0 && j == 0) {
        std::cout << std::setw(3) << y << ":";
      } else {
        int x = matrix[i-1][j-1];
        if (x == INF || x == 0) std::cout << std::setw(4) << '.';
        else std::cout << std::setw(4) << x;
      }
    }
    y++;
    std::cout << '\n';
  }
}

void FindPaths::print_matrix(char c, std::vector<std::vector<int>> matrix) {
  int y {0};
  for (int i = 0; i < n + 1; i++) {
    for (int j = 0; j < n + 1; j++) {
      if (i == 0 && j == 0) {
        std::cout << c;
      } else if (i == 0 && j != 0) {
        std::cout << j << ":";
      } else if (i != 0 && j == 0) {
        std::cout << y << ":";
      } else {
        int x = matrix[i-1][j-1];
        if (x == INF || x == 0) std::cout << '.';
        else std::cout << x;
      }
      if (j != n) std::cout << " ";
    }
    y++;
    std::cout << '\n';
  }
}
