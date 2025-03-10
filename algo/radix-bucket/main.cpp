/**
 * @author Ethan Okamura
 * @file main.cpp
 * @brief created a hybrid of radix and bucket sort
 * @status: working / tested
 * @issues: compiles without warning using the flags -Wall -Wextra -pedantic
 * @notes: pretty quick and easy!
 */

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

void radix_bucket_sort(std::vector<int>& list, int size, int digits) {
  if (list.empty()) return;
  const int bucket_amount = 10;
  // ith from least sig digit to most sig digit
  for (int i = 1; i <= digits; i++) {
    std::vector<int> bucket[bucket_amount];
    for (int j = 0; j < size; j++) {  // loop through each element in list
      int r = static_cast<int>(list[j] / std::pow(10, i - 1)) %
              10;                    // find most sig digit
      bucket[r].push_back(list[j]);  // push element into correct bucket
    }
    // add ordered items from bucket[j] into list
    for (int j = 0; j < bucket_amount; j++)
      for (int k = 0; k < bucket[j].size(); k++)
        list[k + (10 * j)] = bucket[j][k];
  }
}

int main() {
  std::vector<int> list;
  std::string line_of_input;
  while (std::getline(std::cin, line_of_input))
    list.push_back(std::stoi(line_of_input));
  radix_bucket_sort(list, list.size(), 9);
  return 0;
}
