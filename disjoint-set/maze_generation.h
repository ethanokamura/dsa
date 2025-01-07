#ifndef MAZE_GENERATION_H
#define MAZE_GENERATION_H

/**
 * @author Ethan Okamura (eokamura)
 * @email: ethanokamura3@gmail.com
 * @assignment: Programming Assignment 6 [p6]
 * @file maze_generation.h
 * @brief declaring the member functions and variables for the maze generator
 * class
 */

#include <iostream>
#include <random>

#include "disjoint_set.h"

class MazeGeneration {
 public:
  MazeGeneration(int);
  void print_maze();
  void generate();
 private:
  int n;
  std::vector<std::vector<int>> cells;
  void remove_walls(int, int, int, int);
  constexpr bool in_bounds(int, int) const;
  constexpr char convert(int) const;
};

#endif  // MAZE_GENERATION_H
