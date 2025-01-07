#ifndef QUEUE_H
#define QUEUE_H

/**
 * @author Ethan Okamura (eokamura)
 * @email: ethanokamura3@gmail.com
 * @assignment: Programming Assignment 8 [p8]
 * @file queue.h
 * @brief creates a simple queue class!
 */

#include "linked_list.h"

// Defines a stack that uses a doubly-linked list as a data structure.
template <typename T>
class Queue : private LinkedList<T> {
 public:
  // default constructor
  Queue() : LinkedList<T>() {}
  // list constructor
  Queue(std::initializer_list<T> init_list) : LinkedList<T>() {
    for (const std::string& val : init_list) this->push_back(val);
  }
  // pushes a string to the top of the stack
  void push(T val) { this->push_back(val); }
  // pops off the top value in the stack
  void pop() { this->pop_front(); }
  // returns the data at the top of the stack
  T& front() const { return this->LinkedList<T>::front(); }
  // checks if the stack is empty (bool return value)
  bool empty() const { return this->LinkedList<T>::empty(); }
  // returns the size of the stack
  int size() const { return this->LinkedList<T>::size(); }
};

#endif  // QUEUE_H
