/**
 * @author Ethan Okamura (eokamura)
 * @email: ethanokamura3@gmail.com
 * @assignment: Programming Assignment 6 [p6]
 * @file maze_generation.cpp
 * @brief implimenting member functions for the MazeGeneration class
 *
 * Random number gen:
 * @cite
 * https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
 */

#include "maze_generation.h"

MazeGeneration::MazeGeneration(int n)
: n(n), cells(n, std::vector<int>(n, 15)) {
  if (n < 3) throw std::domain_error("invalid size");
  cells[0][0] = 11;          // start
  cells[n - 1][n - 1] = 14;  // end
}

// randomly generate the maze!
void MazeGeneration::generate() {
  // create a random number engine
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, 3);
  // create disjoint set
  DisjointSet ds(n * n);
  // create an array of x and y directions
  int directions[8]{0, 0, 1, -1, 1, -1, 0, 0};
  while (ds.get_num_sets() > 1) {
    for (int x = 0; x < n; x++) {    // O(n)
      for (int y = 0; y < n; y++) {  // O(n)
        int new_x{}, new_y{};
        // find random direction
        do {
          int r {dist(gen)};
          new_x = x + directions[r];
          new_y = y + directions[r + 4];
        } while (!in_bounds(new_x, new_y));  // O(4)
        // calculate the 2 cells (current and new)
        int cell1 {y * n + x};
        int cell2 {new_y * n + new_x};
        // make sure they are not already in the same set
        if (!ds.same_component(cell1, cell2)) {
          remove_walls(x, y, new_x, new_y);  // O(1)
          ds.union_by_rank(cell1, cell2);    // O(lgn)
        }
      }
    }
  }
}

// remove walls between 2 cells using bitwise operators
void MazeGeneration::remove_walls(int x1, int y1, int x2, int y2) {
  if (y1 == y2) {  // no change in y
    if (x1 < x2) {
      cells[x1][y1] &= ~2;  // remove bottom wall from cell 1
      cells[x2][y2] &= ~8;  // remove top wall from cell 2
    } else {
      cells[x1][y1] &= ~8;  // remove top wall from cell 1
      cells[x2][y2] &= ~2;  // remove bottom wall from cell 2
    }
  } else {  // no change in x
    if (y1 < y2) {
      cells[x1][y1] &= ~1;  // remove right wall from cell 1
      cells[x2][y2] &= ~4;  // remove left wall from cell 2
    } else {
      cells[x1][y1] &= ~4;  // remove left wall from cell 1
      cells[x2][y2] &= ~1;  // remove right wall from cell 2
    }
  }
}

// check to see if a cell is in bounds
constexpr bool MazeGeneration::in_bounds(int x, int y) const {
  return x < n && x >= 0 && y < n && y >= 0;
}

// print the maze row by row
void MazeGeneration::print_maze() {
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      if (cells[x][y] > 9)
        std::cout << convert(cells[x][y]);
      else
        std::cout << cells[x][y];
    }
    std::cout << std::endl;
  }
}

// convert int to char
constexpr char MazeGeneration::convert(int x) const { return (x + 87); }
