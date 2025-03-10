/**
 * @author Ethan Okamura
 * @file main.cpp
 * @brief created a program to find the shortest path from
 *        start to finish in a maze represented by hexidecimal
 *        digits.
 * @status: working / tested
 * @issues: compiles without warning using the flags
 *          -Wall -Wextra -pedantic
 * @notes: pretty straight forward
 */

#include <iostream>
#include <vector>

#include "pathfinder.h"

int main() {
  std::vector<std::vector<int>> maze;
  std::string line;

  while (std::getline(std::cin, line)) {
    std::vector<int> row;
    for (char c : line) {
      if (c >= 'a' && c <= 'z')
        row.push_back(c - 87);
      else if (c >= 'A' && c <= 'Z')
        row.push_back(c - 55);
      else if (c >= '0' && c <= '9')
        row.push_back(c - 48);
      else
        std::cout << "invalid: " << c << '\n';
    }
    maze.push_back(row);
  }

  if (maze.empty()) {
    std::cout << "empty maze!\n";
  } else {
    std::size_t n = maze[0].size();
    PathFinder path_finder(maze, n);
    std::vector<int> path = path_finder.get_path();
    for (int v : path) {
      int x = v / n;
      int y = v % n;
      std::cout << "(" << x << ", " << y << ")\n";
    }
  }
  return 0;
}
