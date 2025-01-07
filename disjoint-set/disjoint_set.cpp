/**
 * @author Ethan Okamura (eokamura)
 * @email: ethanokamura3@gmail.com
 * @assignment: Programming Assignment 6 [p6]
 * @file disjoint_set.cpp
 * @brief implimenting member functions for my disjoint set
 */

#include "disjoint_set.h"

// constructor
DisjointSet::DisjointSet(int n) {
  if (n < 3) throw std::domain_error("invalid size!");
  p = new int[n];
  r = new int[n];
  count = n;
  this->n = n;
  for (int i = 0; i < n; i++) {
    p[i] = i;  // parent is itself
    r[i] = 0;  // all are initially rank 0
  }
}

DisjointSet::~DisjointSet() {
  delete[] p;
  delete[] r;
}

/**
 * @brief union by rank
 *   unites set that includes x and y by rank
 *   determined representative element
 *   combine by rank to try to avoid worst-case
 */
void DisjointSet::union_by_rank(int x, int y) {
  // bounds check x and y
  if (x >= n || y >= n) throw std::domain_error("out of range");
  if (x == y) return;
  // find the representatives (or root nodes)
  // unite then together
  link(find(x), find(y));
}

void DisjointSet::link(int x, int y) {
  // tuck smaller rank under larger rank, no rank change
  // if they are the same rank, then one rank increases by one (one on top)
  if (r[x] > r[y]) {
    p[y] = x;
  } else {
    p[x] = y;
    if (r[x] == r[y]) r[y]++;
  }
  count--;
}

/**
 * @brief find representative using path compression
 *   flatten structure
 *   fix parents at the same time
 *   do not change rank
 * @return representative of value
 */
int DisjointSet::find(int x) {
  // bounds check
  if (x >= n) throw std::domain_error("out of range");
  if (p[x] != x) p[x] = find(p[x]);
  return p[x];
}

void DisjointSet::print_set() {
  // map to store representative elements and their corresponding sets
  std::unordered_map<int, std::vector<int>> sets;

  for (int i = 0; i < n; i++) {
    // find the representative of the current element
    int representative = find(i);
    // add the element to its corresponding set
    sets[representative].push_back(i);
  }

  // Print out the sets
  std::cout << "sets:\n";
  for (const auto& pair : sets) {
    std::cout << "rep " << pair.first << ": { ";
    for (int elem : pair.second) {
      std::cout << elem << " ";
    }
    std::cout << "}\n";
  }
}
