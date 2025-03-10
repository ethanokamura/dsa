/**
 * @author Ethan Okamura
 * @file minimum_heap.cpp
 * @brief implimenting pulbic member functions
 *        creating the heap && queue
 * @citation: matt blanke -> using (int min) in min_of_three
 */

#include "minimum_heap.h"

// default constructor for the heap
IntMinHeap::IntMinHeap(int cap) {
  A = new int[cap];
  capacity = cap;
  size = 0;
}

// destructor
IntMinHeap::~IntMinHeap() { delete[] A; }

// sorts the heap and returns an array and its size
std::pair<int*, int> IntMinHeap::heap_sort() {
  if (is_empty()) return std::pair<int*, int>(nullptr, 0);
  int* temp_arr = new int[size];
  for (int i = 0; i < size; i++) temp_arr[i] = A[i];
  int* old_a = A;
  A = temp_arr;
  int old_size = size;
  for (int i = size - 1; i >= 0; i--) {
    std::swap(A[0], A[i]);
    size--;
    heapify(0);
  }
  size = old_size;
  std::pair<int*, int> _pair(A, size);
  A = old_a;
  return _pair;
}

// returns a string value of the heap
std::string IntMinHeap::to_string() {
  std::ostringstream oss;
  oss << "heap size " << size << ": ";
  if (size > 0) {
    for (int i = 0; i < size; i++) oss << A[i] << ", ";
    std::string temp = oss.str();
    temp = temp.substr(0, temp.length() - 2);
    return temp;
  }
  return oss.str();
}

// inserts a value at the end of the heap
bool IntMinHeap::heap_insert(int val) {
  if (is_full()) return false;
  size++;
  A[size - 1] = val + 1;
  decrease_key(size - 1, val);
  return true;
}

// return the root value
int IntMinHeap::minimum() { return (size == 0) ? 0 : A[0]; }

// extract the root
int IntMinHeap::extract_min() {
  if (is_empty()) return 0;
  int min = A[0];
  A[0] = A[size - 1];
  size--;
  heapify(0);
  return min;
}

// promote element in heap
void IntMinHeap::decrease_key(int i, int k) {
  if (i < 0 || i >= size) return;
  if (A[i] <= k) return;
  A[i] = k;
  while (i > 0 && A[parent(i)] > A[i]) {
    std::swap(A[i], A[parent(i)]);
    i = parent(i);
  }
}

// check if heap is empty
bool IntMinHeap::is_empty() { return size == 0; }

// check if heap is full
bool IntMinHeap::is_full() { return size == capacity; }

// finds the smallest value of up to 3 ints
int IntMinHeap::min_of_three(int i, int j, int k) {
  if (i < 0 || i > size) throw std::domain_error("err with bounds (min of 3)");
  int min = i;
  bool valid_k = k < size;
  bool valid_j = j < size;
  if (valid_j)
    if (A[j] < A[min]) min = j;
  if (valid_k)
    if (A[k] < A[min]) min = k;
  return min;
}

// find left child of index i
int IntMinHeap::left(int i) { return i * 2 + 1; }

// find right child of index i
int IntMinHeap::right(int i) { return i * 2 + 2; }

// find parent of index i
int IntMinHeap::parent(int i) { return i % 2 == 0 ? (i / 2 - 1) : (i / 2); }

// convert array to a heap
void IntMinHeap::build_heap() {
  for (int i = size / 2 - 1; i >= 0; i--) heapify(i);
}

// heapify at position i
void IntMinHeap::heapify(int i) {
  int n = min_of_three(i, left(i), right(i));
  if (n != i) {
    std::swap(A[i], A[n]);
    heapify(n);
  }
}
