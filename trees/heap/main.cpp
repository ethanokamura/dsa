/**
 * @author Ethan Okamura (eokamura)
 * @email: ethanokamura3@gmail.com
 * @file main.cpp
 * @brief created a priority queue using a minimum heap (holding ints)
 */

#include <iostream>
#include <sstream>

#include "minimum_heap.h"

// create a readable output for an array
std::string stringify_array(int* arr, int size) {
  std::ostringstream oss;
  std::string array_string = "";
  if (size > 0) {
    for (int i = 0; i < size; i++) oss << arr[i] << ", ";
    array_string += oss.str();
    array_string = array_string.substr(0, array_string.length() - 2);
  }
  return array_string;
}

int main() {
  const int SIZE = 2400000;
  IntMinHeap heap(SIZE);
  int input;
  while (std::cin >> input) {  // while user is inputting
    if (input > 0) {           // if input is positive int, insert val
      heap.heap_insert(input);
      std::cout << "insert: " << input << '\n';
    } else if (input == 0) {  // if input is 0, print heap
      std::cout << heap.to_string() << '\n';
    } else if (input == -1) {  // if input is -1, extract min
      std::cout << "extracted min: " << heap.extract_min() << '\n';
    } else if (input == -2) {  // if input is -2, sort and print array`
      std::pair<int*, int> _pair = heap.heap_sort();
      std::cout << "sorted array: [";
      if (_pair.first != nullptr)
        std::cout << stringify_array(_pair.first, _pair.second);
      std::cout << "]\n";
      delete[] _pair.first;
      _pair.first = nullptr;
    }
  }
  return 0;
}