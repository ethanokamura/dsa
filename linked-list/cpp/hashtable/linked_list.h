#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <initializer_list>
#include <iomanip>
#include <iostream>

#include "record.h"

// Defines a doubly-linked list
template <typename Record>
class LinkedList {
  struct Node;  // forward declaration for our private Node type
 public:
  // default constructor
  LinkedList() : head(nullptr), tail(nullptr), list_size(0) {}

  // list constructor
  LinkedList(std::initializer_list<Record> init_list) {
    for (const Record &val : init_list) push_back(val);
  }

  // copy constructor
  LinkedList(const LinkedList<Record> &another) {
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
  Record &front() const {
    if (!head) throw std::domain_error("empty list!");
    return head->data;
  }

  // returns the value of the tail node
  Record &back() const {
    if (!tail) throw std::domain_error("empty list!");
    return tail->data;
  }

  // returns the size of the linked list
  std::size_t size() const { return list_size; }

  // returns true if list is empty
  bool empty() const { return !head; }

  // adds a new element (val)
  // assigns new element as head
  void push_front(Record val) {
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
  void push_back(Record val) {
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

  // removes the current head node from list
  // reassigns new head
  void pop_back() {
    if (empty()) throw std::domain_error("empty list!");
    if (!head->next) {
      delete head;
      head = tail = nullptr;
      list_size--;
      return;
    }
    Node *current = head;
    while (current->next->next) current = current->next;
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
  void resize(std::size_t n, const Record &fill_value) {
    if (list_size == n) return;
    while (list_size < n) push_back(fill_value);
    while (list_size > n) pop_back();
  }

  // clears the linked list
  void clear() {
    while (head) pop_front();
  }

  // removes the first value in the list that matches the target value
  void remove(const Record &target) {
    if (empty()) return;
    if (head->data == target) {
      pop_front();
      return;
    }
    Node *current = head;
    while (current->next && current->next->data != target)
      current = current->next;
    if (current->next) {
      Node *temp = current->next;
      current->next = current->next->next;
      list_size--;
      delete temp;
    }
  }

  // function to remove all occurrences of a value from the linked list
  void remove_all(const Record &target) {
    Node *current = head;
    Node *prev = nullptr;
    while (current) {
      if (current->data == target) {
        Node *temp = current;
        if (!prev)
          head = current->next;
        else
          prev->next = current->next;
        current = current->next;
        delete temp;
        list_size--;
      } else {
        prev = current;
        current = current->next;
      }
    }
    if (prev) tail = prev;
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
    Node *temp = head;
    head = prev;
    tail = temp;
  }

  // check if a value exists in the linked list
  bool contains(const Record &target) const {
    Node *current = head;
    while (current) {
      if (current->data == target) return true;
      current = current->next;
    }
    return false;
  }

  // assigns list to a new list
  LinkedList &operator=(std::initializer_list<Record> init_list) {
    clear();
    for (const Record &val : init_list) push_back(val);
    return *this;
  }

  // assigns list to an existing list
  LinkedList &operator=(const LinkedList &another) {
    Node *current = another.head;
    clear();
    while (current) {
      push_back(current->data);
      current = current->next;
    }
    return *this;
  }

  // checks list for equivalency to another list
  bool operator==(const LinkedList &another) {
    if (size() != another.size()) return false;
    Node *current = head;
    Node *other = another.head;
    while (current) {
      if (other->data != current->data) return false;
      current = current->next;
      other = other->next;
    }
    return true;
  }

  // checks list for inequivalency to another list
  bool operator!=(const LinkedList &another) { return !(*this == another); }

  // allows indexing functionality
  Record &operator[](std::size_t index) const {
    if (index >= list_size) throw std::out_of_range("Index out of range");
    Node *current = head;
    for (std::size_t i = 0; i < index; ++i) current = current->next;
    return current->data;
  }

  // allows stdout of list
  friend std::ostream &operator<<(std::ostream &out, const LinkedList &list) {
    for (size_t i = 0; i < list.size(); i++) {
      Record p = list[i];
      out << std::setfill('0') << std::setw(9) << p.first() << ' ';
      out << p.second() << '\n';
    }
    return out;
  }

 private:
  struct Node {
    Record data;
    Node *next = nullptr;
    Node(Record value) : data(value), next(nullptr) {}
  };
  Node *head = nullptr;
  Node *tail = nullptr;
  std::size_t list_size = 0;
};

#endif  // LINKED_LIST_H
