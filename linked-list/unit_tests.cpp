#include <iostream>

#include "linked_list.h"

int main() {
  // Test default constructor
  LinkedList<int> list1;
  std::cout << "Test default constructor: ";
  if (list1.size() == 0 && list1.empty()) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  // Test list constructor
  LinkedList<int> list2 = {1, 2, 3};
  std::cout << "Test list constructor: ";
  if (list2.size() == 3 && list2.front() == 1 && list2.back() == 3) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  // Test copy constructor
  LinkedList<int> list3(list2);
  std::cout << "Test copy constructor: ";
  if (list3 == list2) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  // Test push_front
  list1.push_front(1);
  std::cout << "Test push_front: ";
  if (list1.size() == 1 && list1.front() == 1) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  // Test push_back
  list1.push_back(2);
  std::cout << "Test push_back: ";
  if (list1.size() == 2 && list1.back() == 2) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  // Test pop_front
  list1.pop_front();
  std::cout << "Test pop_front: ";
  if (list1.size() == 1 && list1.front() == 2) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  // Test pop_back
  list1.pop_back();
  std::cout << "Test pop_back: ";
  if (list1.empty()) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  // Test resize
  list1.resize(3);
  std::cout << "Test resize: ";
  if (list1.size() == 3) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  // Test clear
  list1.clear();
  std::cout << "Test clear: ";
  if (list1.empty()) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  // Test remove
  list2.remove(2);
  std::cout << "Test remove: ";
  if (list2.size() == 2 && !list2.contains(2)) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  // Test remove_all
  LinkedList<int> list4 = {1, 2, 2, 3, 2, 4, 2, 5};
  list4.remove_all(2);
  std::cout << "Test remove_all: ";
  if (list4.size() == 4 && !list4.contains(2)) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  // Test reverse
  LinkedList<int> list5 = {1, 2, 3};
  list5.reverse();
  std::cout << "Test reverse: ";
  if (list5.size() == 3 && list5.front() == 3 && list5.back() == 1) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  // Test contains
  LinkedList<int> list6 = {1, 2, 3};
  std::cout << "Test contains: ";
  if (list6.contains(2) && !list6.contains(4)) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  // Test assignment operators
  LinkedList<int> list7;
  list7 = list6;
  std::cout << "Test assignment operators: ";
  if (list7 == list6) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  return 0;
}