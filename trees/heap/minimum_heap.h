#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

/**
 * @author Ethan Okamura
 * @file minimum_heap.h
 * @brief defining member functions and variables
 *        creating the heap && queue
 */

#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

// integer minimum heap with PQ
class IntMinHeap {
 public:
  IntMinHeap(int);                   // empty heap wth apacity
  ~IntMinHeap();                     // clean up allocated memory
  std::pair<int*, int> heap_sort();  // return sorted array and size from heap
  std::string to_string();
  bool heap_insert(int);        // add element to heap; return success
  int minimum();                // min functions should return 0 in empty heaps
  int extract_min();            // return and remove A[root]
  void decrease_key(int, int);  // A[i] decreased to k
  bool is_empty();
  bool is_full();

 private:
  int min_of_three(int, int, int);  // finds the smallest value of up to 3 ints
  int left(int);                    // find left child of index i
  int right(int);                   // find right child of index i
  int parent(int);                  // find parent of index i
  void build_heap();
  void heapify(int);  // heapify at position i
  int* A;             // array of integers - data
  int capacity;       // size of array A
  int size;           // data size in array
};
#endif  // PRIORITY_QUEUE_H
