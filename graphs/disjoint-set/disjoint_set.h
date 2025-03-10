#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

/**
 * @author Ethan Okamura (eokamura)
 * @email: ethanokamura3@gmail.com
 * @assignment: Programming Assignment 6 [p6]
 * @file disjoint_set.h
 * @brief declaring the member functions and variables for the union find
 * structure
 */

#include <iostream>
#include <unordered_map>
#include <vector>

class DisjointSet {
 private:
  int* p;  // parent
  int* r;  // rank (height of tree rep. the set)
  int n;
  int count;
  void link(int, int);
 public:
  // default constructor
  DisjointSet() : p(nullptr), r(nullptr), n(0){};
  // size constructor
  DisjointSet(int);
  // default destructor
  ~DisjointSet();
  // union by rank
  void union_by_rank(int, int);
  // find rep
  int find(int);

  void print_set();
  int size() const { return n; }
  int get_num_sets() const { return count; }
  bool same_component(int x, int y) { return find(x) == find(y); }
};

#endif  // DISJOINT_SET_H
