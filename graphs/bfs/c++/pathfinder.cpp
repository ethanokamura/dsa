/**
 * @author Ethan Okamura (eokamura)
 * @email: ethanokamura3@gmail.com
 * @assignment: Programming Assignment 8 [p8]
 * @file pathfinder.cpp
 * @brief implementing member functions for the path finder class
 */

#include "pathfinder.h"

// default constructor
PathFinder::PathFinder() : n(0), p(nullptr), d(nullptr), color(nullptr){};

// maze constructor
PathFinder::PathFinder(std::vector<std::vector<int>> maze, std::size_t size)
    : n(size), nodes(maze) {
  p = new int[k];
  d = new int[k];
  color = new int[k];
}

// default destructor
PathFinder::~PathFinder() {
  delete[] p;
  delete[] d;
  delete[] color;
  p = d = color = nullptr;
}

// find all adjacent nodes to the current node v
std::vector<int> PathFinder::find_adj(int v) {
  std::vector<int> adj;
  int y{v / n};
  int x{v % n};
  int directions[8] = {0, 0, 1, -1, 1, -1, 0, 0};
  for (std::size_t i = 0; i < 4; i++) {
    int new_x{x + directions[i]};
    int new_y{y + directions[i + 4]};
    if (in_bounds(new_x, new_y) && is_connected(x, y, new_x, new_y))
      adj.push_back(new_y * n + new_x);
  }
  return adj;
}

// perform breadth-first search O(V + E)
void PathFinder::BFS(int s) {

  // create default values
  for (int i = 0; i < k; i++) {
    p[i] = -1;     // flag value
    d[i] = -1;     // flag value
    color[i] = 0;  // undiscovered
  }

  Queue<int> q;

  // initialization of the node we will search from (root)
  color[s] = 1;
  d[s] = 0;
  p[s] = -1;
  q.push(s);

  // main section O(E)
  while (!q.empty()) {
    int u = q.front();
    std::vector<int> adj = find_adj(u);
    for (const int &v : adj) {
      if (color[v] == 0) {  // non-discovered node
        color[v] = 1;
        d[v] = d[u] + 1;
        p[v] = u;
        q.push(v);
      }
    }
    // done with it
    q.pop();
    color[u] = 2;
  }
}

// find the shortest bath from the start node to end node
std::vector<int> PathFinder::find_path(int start, int end) {
  BFS(start);
  std::vector<int> path;
  // no path exists
  if (d[end] == -1) return path;
  // back track to find the path!
  int cur = end;
  while (cur != start) {
    path.push_back(cur);
    cur = p[cur];
  }
  path.push_back(start);
  return path;
}

// public wrapper to get the shortest path
std::vector<int> PathFinder::get_path() {
  return (n > 0) ? find_path(k - 1, 0) : std::vector<int>();
}

// check if there is a connection
bool PathFinder::is_connected(int x1, int y1, int x2, int y2) const {
  int u{nodes[x1][y1]};
  int v{nodes[x2][y2]};
  if (y1 == y2) {  // no change in y
    if (x1 < x2) {
      // check if bottom wall in cell 1 and top wall in cell 2 connect
      return (u & 2) == 0 || (v & 8) == 0;
    } else {
      // check if top wall in cell 1 and bottom wall in cell 2 connect
      return (u & 8) == 0 || (v & 2) == 0;
    }
  } else {  // no change in x
    if (y1 < y2) {
      // check if right wall in cell 1 and left wall in cell 2 connect
      return (u & 1) == 0 || (v & 4) == 0;
    } else {
      // check if left wall in cell 1 and right wall in cell 2 connect
      return (u & 4) == 0 || (v & 1) == 0;
    }
  }
}

// check to see if a node is in bounds
constexpr bool PathFinder::in_bounds(const int x, const int y) {
  return x < n && x >= 0 && y < n && y >= 0;
}
