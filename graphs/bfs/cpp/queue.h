#ifndef QUEUE_H
#define QUEUE_H

/**
 * @author Ethan Okamura
 * @file queue.h
 * @brief creates a simple queue class!
 */

#include "linked_list.h"

// Defines a stack that uses a doubly-linked list as a data structure.
template <typename T>
class Queue {
 public:
  // default constructor
  Queue() : _ll{} {}
  // list constructor
  Queue(std::initializer_list<T> init_list) {
    for (const std::string& val : init_list) this->_ll.push_front(val);
  }
  // pushes a string to the top of the stack
  void push(T val) { this->_ll.push_back(val); }
  // pops off the top value in the stack
  void pop() { this->_ll.pop_front(); }
  // returns the data at the top of the stack
  T& front() const { return this->_ll.front(); }
  // checks if the stack is empty (bool return value)
  bool empty() const { return this->_ll.empty(); }
  // returns the size of the stack
  int size() const { return this->_ll.size(); }

 private:
  LinkedList<T> _ll;
};

#endif  // QUEUE_H
