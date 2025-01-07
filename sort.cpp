#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
  std::vector<int> list;
  int input;
  while (std::cin >> input) list.push_back(input);
  std::sort(list.begin(), list.end());
  for (int i : list)
    std::cout << std::setfill('0') << std::setw(9) << i << '\n';
  return 0;
}
