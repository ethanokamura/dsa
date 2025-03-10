#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cmath>
#include <fstream>
#include <string>

#include "linked_list.h"

class HashTable {
 public:
  HashTable(int size = 100);  // build a table
  ~HashTable();               // destroy a table
  void insert(Record);        // insert copy of record
  void delete_element(int);   // delete a record
  // return pointer to a copy of found record, or null
  Record *search(int);
  void print_values(
      std::ofstream &);   // prints out a list of keys (one per line)
  bool is_empty() const;  // checks if the table is empty
  void clear();           // clears the list
 private:
  Record *find(int);  // keeps privacy
  int hash(Record);   // hash value for record
  int hash(int);      // hash value for key
  const int m;        // size of table
  // vector of linked lists that hold key value pairs
  LinkedList<Record> *table;
  const double c = 1 / ((std::sqrt(5) - 1) / 2.0);  // one over phi
};

#endif  // HASHTABLE_H
