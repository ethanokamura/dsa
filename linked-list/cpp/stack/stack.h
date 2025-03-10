#ifndef STACK_H
#define STACK_H

/**
 * @author Ethan Okamura
 * @file stack.h
 * @brief creates a simple stack class!
 */

#include "../linked-list/linked_list.h"

// Defines a stack that uses a doubly-linked list as a data structure.
template <typename T>
class Stack {
 public:
  // default constructor
  Stack() : _ll{} {}
  // list constructor
  Stack(std::initializer_list<T> init_list) {
    for (const std::string& val : init_list) this->_ll.push_front(val);
  }
  // pushes a string to the top of the stack
  void push(T val) { this->_ll.push_front(val); }
  // pops off the top value in the stack
  void pop() { this->_ll.pop_front(); }
  // returns the data at the top of the stack
  T& top() { return this->_ll.front(); }
  // checks if the stack is empty (bool return value)
  bool is_empty() { return this->_ll.empty(); }
  // returns the size of the stack
  int size() { return this->_ll.size(); }

 private:
  LinkedList<T> _ll;
};

#endif  // STACK_H
