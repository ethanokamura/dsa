#include "linked_list.h"

int main() {
  LinkedList<int> ll;
  ll.push_back(2);
  std::cout << ll << '\n';
  ll.push_front(1);
  std::cout << ll << '\n';
  ll.pop_back();
  ll.pop_back();
  std::cout << ll << '\n';
  ll.push_back(4);
  ll.push_back(7);
  ll.push_front(7);
  ll.push_back(0);
  std::cout << ll << '\n';
  LinkedList<int> ll2 = {1, 2, 3, 4, 5};
  std::cout << ll2 << '\n';
  while (ll2.size() > 0) ll2.pop_front();
  std::cout << (ll2.empty() ? "empty" : "not empty") << '\n';
  ll2 = ll;
  std::cout << ll << (ll != ll2 ? " != " : " = ") << ll2 << '\n';
  std::cout << (ll2.empty() ? "empty" : "not empty") << '\n';
  std::cout << ll.back() << " = " << ll2.back() << '\n';
  std::cout << ll.front() << " = " << ll2.front() << '\n';
  ll2.clear();
  std::cout << ll << (ll != ll2 ? " != " : " = ") << ll2 << '\n';

  return 0;
}