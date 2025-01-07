#include <string>

class Record {
 public:
  Record();
  Record(int key, std::string value);
  Record(const Record& other);
  int first();
  std::string second();
  Record& operator=(const Record& other);
  bool operator==(Record other);
  bool operator!=(Record other);

 private:
  int key;
  std::string value;
};