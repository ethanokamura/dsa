#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/**
 * @author Ethan Okamura
 * @file linked_list.h
 * @brief creates a simple linked list!
 */

#include <initializer_list>
#include <iostream>

// Defines a doubly-linked list
template <typename T>
class LinkedList {
  struct Node;  // forward declaration for our private Node type
 public:
  // default constructor
  LinkedList() : head(nullptr), tail(nullptr), list_size(0) {}

  // list constructor
  LinkedList(std::initializer_list<T> init_list) {
    for (const T &val : init_list) push_back(val);
  }

  // copy constructor
  LinkedList(const LinkedList<T> &another) {
    for (Node *current = another.head; current; current = current->next)
      push_back(current->data);
  }

  // destructor
  ~LinkedList() {
    Node *current = head;
    while (current) {
      Node *next = current->next;
      delete current;
      current = next;
    }
  }

  // return head for iteration
  Node *begin() const { return head; }

  // return tail for iteration
  Node *end() const { return tail; }

  // returns the value of the head node
  T &front() const {
    if (!head) throw std::domain_error("empty list!");
    return head->data;
  }

  // returns the value of the tail node
  T &back() const {
    if (!tail) throw std::domain_error("empty list!");
    return tail->data;
  }

  // returns the size of the linked list
  std::size_t size() const { return list_size; }

  // returns true if list is empty
  bool empty() const { return !head; }

  // adds a new element (val)
  // assigns new element as tail
  void push_back(T val) {
    Node *new_node = new Node(val);
    if (empty()) {
      head = tail = new_node;
    } else {
      tail->next = new_node;
      tail = new_node;
    }
    list_size++;
  }

  // removes the current head node from list
  // reassigns new head
  void pop_front() {
    if (empty()) throw std::domain_error("empty list!");
    Node *temp = head;
    head = head->next;
    delete temp;
    if (!head) tail = nullptr;
    list_size--;
  }

 private:
  struct Node {
    T data;
    Node *next = nullptr;
    Node(T value) : data(value), next(nullptr) {}
  };
  Node *head = nullptr;
  Node *tail = nullptr;
  std::size_t list_size = 0;
};

#endif  // LINKED_LIST_H
