/**
 * @author Ethan Okamura
 * @file main.cpp
 * @brief created a program to find the shortest path from
 *        all pairs of verticies in a weighted, directed graph
 * @status: working / tested
 * @issues: compiles without warning using the flags
 *          -Wall -Wextra -pedantic
 * @notes: this one was initially pretty tricky
 */

#include "find_paths.h"
#include <iostream>

int main(int argc, char* argv[]) {
  std::string cmd {"-f"};
  bool formatted { argc > 1 && argv[1] == cmd };
  int n {0};
  std::string line;
  std::vector<std::vector<int>> graph;
  while (std::getline(std::cin, line)) {
    std::vector<int> set;
    int id {0};
    std::string num;
    int x {0};
    bool neg = false;
    for (std::size_t i = 0; i < line.length(); i++) {
      if (line[i] == '-') neg = true;
      if (line[i] >= '0' && line[i] <= '9') num += line[i];
      if (num.length() > 0 && (line[i] == ' ' || line[i] == ',' || i == line.length() - 1)) {
        x = std::stoi(num);
        x = neg ? -x : x;
        set.push_back(x);
        if (id < 2 && n < x) n = x;
        num = "";
        neg = false;
        id++;
      }
    }
    graph.push_back(set);
  }

  const int INF = std::numeric_limits<int>::max();

  std::vector<std::vector<int>> dist(n, std::vector<int>(n, INF));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) dist[i][j] = 0;
    }
  }

  for (std::vector<int> v: graph) {
    if (v[0] > 0 && v[1] > 0) {
      dist[v[0]-1][v[1]-1] = v[2];
    } else {
      throw std::domain_error("out of bounds!");
    }
  }

  FindPaths paths(dist);
  paths.find_paths();
  paths.print(formatted);

  return 0;
}
