#include "hashtable.h"

// default constructor
HashTable::HashTable(int size) : m(size) {
  table = new LinkedList<Record>[size];
  for (int i = 0; i < size; i++) {
    table[i] = LinkedList<Record>{};
  }
}

// destructor
HashTable::~HashTable() {}

// insert a key value pair
void HashTable::insert(Record record) {
  int index = hash(record.first());
  table[index].push_front(record);
}

// delete a key value pair
void HashTable::delete_element(int key) {
  int index = hash(key);
  if (table[index].empty()) return;
  Record* element = search(key);
  if (element == nullptr) return;
  table[index].remove(*element);
}

// find a key value pair
Record* HashTable::search(int key) { return find(key); }

// private search
Record* HashTable::find(int key) {
  int index = hash(key);
  if (table[index].empty()) return nullptr;
  for (std::size_t i = 0; i < table[index].size(); i++) {
    Record* p = &table[index][i];
    if ((*p).first() == key) return p;
  }
  return nullptr;
}

// check to see if table is empty
bool HashTable::is_empty() const {
  for (int i = 0; i < m; ++i)
    if (!table[i].empty()) return false;
  return true;
}

// clear the table
void HashTable::clear() {
  if (m == 0) return;
  for (int i = 0; i < m; i++)
    if (!table[i].empty()) table[i].clear();
}

// print out the pairs in the list (one per line)
void HashTable::print_values(std::ofstream& out) {
  for (int i = 0; i < m; i++)
    if (!table[i].empty()) out << table[i];
}

// hash a pair's key
int HashTable::hash(Record record) { return hash(record.first()); }

// hash a key with mutliplicaiton method
int HashTable::hash(int key) {
  return static_cast<int>(m * (key * c - static_cast<int>(key * c)));
}
