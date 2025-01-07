/**
 * @author Ethan Okamura (eokamura)
 * @email: ethanokamura3@gmail.com
 * @assignment: Programming Assignment 6 [p6]
 * @file main.cpp
 * @brief created a random maze of n*n size using a disjoint set
 * @status: working / tested
 * @issues: compiles without warning using the flags -Wall -Wextra -pedantic
 * @notes: fun project! i wrote one using recursive back tracking as well
 */

#include <string>

#include "maze_generation.h"

int main(int argc, char* argv[]) {
  if (argc > 1) {
    int n = std::stoi(argv[1]);
    MazeGeneration maze(n);
    maze.generate();
    maze.print_maze();
  }
  return 0;
}