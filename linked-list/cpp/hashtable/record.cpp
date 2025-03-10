#include "record.h"

Record::Record() : key(0), value("") {}
Record::Record(int key, std::string value) : key(key), value(value) {}
Record::Record(const Record& other) : key(other.key), value(other.value) {}
int Record::first() { return key; }
std::string Record::second() { return value; }
Record& Record::operator=(const Record& other) {
  if (this != &other) {  // Avoid self-assignment
    key = other.key;
    value = other.value;
  }
  return *this;
}
bool Record::operator==(Record other) {
  return other.key == key && other.value == value;
}
bool Record::operator!=(Record other) {
  return other.key != key || other.value != value;
}