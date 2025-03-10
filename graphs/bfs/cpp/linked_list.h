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
    while (current != nullptr) {
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
    if (head == nullptr) throw std::domain_error("empty list!");
    return head->data;
  }

  // returns the value of the tail node
  T &back() const {
    if (tail == nullptr) throw std::domain_error("empty list!");
    return tail->data;
  }

  // returns the size of the linked list
  std::size_t size() const { return list_size; }

  // returns true if list is empty
  bool empty() const { return head == nullptr; }

  // adds a new element (val)
  // assigns new element as head
  void push_front(T val) {
    Node *new_node = new Node(val);
    if (empty()) {
      head = tail = new_node;
    } else {
      new_node->next = head;
      head = new_node;
    }
    list_size++;
  }

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
    if (head == nullptr) tail = nullptr;
    list_size--;
  }

  // removes the current head node from list
  // reassigns new head
  void pop_back() {
    if (empty()) throw std::domain_error("empty list!");
    if (head->next == nullptr) {
      delete head;
      head = tail = nullptr;
      list_size--;
      return;
    }
    Node *current = head;
    while (current->next->next != nullptr) current = current->next;
    delete current->next;
    current->next = nullptr;
    tail = current;
    list_size--;
  }

  // resizes the list
  void resize(std::size_t n) {
    if (list_size == n) return;
    while (list_size < n) push_back(0);
    while (list_size > n) pop_back();
  }

  // resizes the list with filler values
  void resize(std::size_t n, const T &fill_value) {
    if (list_size == n) return;
    while (list_size < n) push_back(fill_value);
    while (list_size > n) pop_back();
  }

  // clears the linked list
  void clear() {
    while (head) pop_front();
  }

  // removes the first value in the list that matches the target value
  void remove(const T &target) {
    if (empty()) return;
    if (head->data == target) {
      pop_front();
      return;
    }
    Node *current = head;
    while (current->next != nullptr && current->next->data != target)
      current = current->next;
    if (current->next != nullptr) {
      Node *temp = current->next;
      current->next = current->next->next;
      list_size--;
      delete temp;
    }
  }

  // function to remove all occurrences of a value from the linked list
  void remove_all(const T &target) {
    for (std::size_t i = 0; i < size(); i++) {
      if ((*this)[i] == target) {
        remove(target);
        --i;
      }
    }
  }

  // reverse the order of elements
  void reverse() {
    Node *prev = nullptr;
    Node *cur = head;
    Node *next = nullptr;
    while (cur) {
      next = cur->next;
      cur->next = prev;
      prev = cur;
      cur = next;
    }
    head = prev;
  }

  // check if a value exists in the linked list
  bool contains(const T &target) const {
    for (std::size_t i = 0; i < size(); ++i)
      if ((*this)[i] == target) return true;
    return false;
  }

  // assigns list to a new list
  LinkedList &operator=(std::initializer_list<T> init_list) {
    clear();
    for (const T &val : init_list) push_back(val);
    return *this;
  }

  // assigns list to an existing list
  LinkedList &operator=(const LinkedList &another) {
    Node *current = another.head;
    clear();
    while (current != nullptr) {
      push_back(current->data);
      current = current->next;
    }
    return *this;
  }

  // checks list for equivalency to another list
  bool operator==(const LinkedList &another) {
    if (size() != another.size()) return false;
    for (int i = 0; i < size(); i++)
      if (another[i] != (*this)[i]) return false;
    return true;
  }

  // checks list for inequivalency to another list
  bool operator!=(const LinkedList &another) { return !(*this == another); }

  // allows indexing functionality
  T &operator[](std::size_t index) const {
    if (index >= list_size) throw std::out_of_range("Index out of range");
    Node *current = head;
    for (std::size_t i = 0; i < index; ++i) current = current->next;
    return current->data;
  }

  // allows stdout of list
  friend std::ostream &operator<<(std::ostream &out, const LinkedList &list) {
    out << '[';
    for (size_t i = 0; i < list.size(); i++) {
      out << list[i];
      if (i < list.size() - 1) out << ", ";
    }
    out << ']';
    return out;
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
