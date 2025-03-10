#include <iostream>

#include "hashtable.h"

int main() {
  HashTable table(178000);
  bool is_inputing = true;

  while (is_inputing) {
    int choice = 0;
    std::cout << "(1)load (2)insert (3)delete (4)search (5)clear (6)save "
                 "(7)quit -- Your choice?: ";
    std::cin >> choice;

    switch (choice) {
      case 1: {
        std::string filename;
        std::cout << "read hash table - filename? ";
        std::cin >> filename;
        int key;
        std::string value;
        std::ifstream file(filename);
        while (file >> key && file.seekg(1, std::ios_base::cur) &&
               std::getline(file, value)) {
          table.insert(Record(key, value));
        }
        break;
      }
      case 2: {
        int key;
        std::string value;
        std::cout << "input a new record:\n";
        std::cin >> key;
        std::cin.ignore();  // clear the space between the input
        std::getline(std::cin, value);
        table.insert(Record(key, value));
        break;
      }
      case 3: {
        int key;
        std::cout << "delete record - key? ";
        std::cin >> key;
        Record* p = table.search(key);
        if (p != nullptr) {
          std::cout << "Delete: " << p->first() << " " << p->second() << '\n';
          table.delete_element(key);
        } else {
          std::cout << "Delete not found: " << key << '\n';
        }
        break;
      }
      case 4: {
        int key;
        std::cout << "search for a record - key? ";
        std::cin >> key;
        Record* p = table.search(key);
        if (p != nullptr) {
          std::cout << "Found: " << p->first() << " " << p->second() << '\n';
        } else {
          std::cout << "Search not found: " << key << '\n';
        }
        break;
      }
      case 5: {
        std::cout << "clearing hash table.\n";
        table.clear();
        break;
      }
      case 6: {
        std::string filename;
        std::cout << "write hash table - filename? ";
        std::cin >> filename;
        std::ofstream out(filename);
        table.print_values(out);
        out.close();
        break;
      }
      case 7:
        is_inputing = false;
        break;
      default:
        std::cout << "Invalid choice. Please try again.\n";
        break;
    }
  }

  return 0;
}
