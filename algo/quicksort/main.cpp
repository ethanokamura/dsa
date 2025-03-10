/**
 * @author Ethan Okamura
 * @file main.cpp
 * @brief created a quicksort algorithm using lomuto's technique
 * @status: working / tested
 * @issues: compiles without warning using the flags -Wall -Wextra -pedantic
 * @notes: had fun automating tests
 */

#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>

// find the median of 3 values
int med_of_three(std::vector<int>& list, int start, int end) {
  int mid = start + (end - start) / 2;
  int start_value = list.at(start);
  int end_value = list.at(end);
  int mid_value = list.at(mid);
  if ((start_value >= mid_value && start_value <= end_value) ||
      (start_value >= end_value && start_value <= mid_value))
    return start;
  if ((mid_value >= start_value && mid_value <= end_value) ||
      (mid_value >= end_value && mid_value <= start_value))
    return mid;
  return end;
}

// partition the list!
int lomuto_partition(std::vector<int>& list, int start, int end) {
  const int const_value = 25;  // read README.md
  int med = ((end - start + 1) >= const_value) 
      ? med_of_three(list, start, end) 
      : end;
  std::swap(list.at(med), list.at(end));
  int pivot = list.at(end);            // select pivot point
  int boundary = start - 1;            // select lower bounds
  for (int i = start; i < end; i++) {  // for each value
    if (list.at(i) <= pivot) {         // if value is less than pivot point
      boundary++;                      // increment bound
      std::swap(list.at(boundary),     // swap lower bound with current val
                list.at(i));
    }
  }
  // swap lower bound and last value
  std::swap(list.at(boundary + 1), list.at(end));
  return boundary + 1;      // return the new lower bound
}

// lomuto's implimentation of quicksort
void lomuto_quicksort(std::vector<int>& list, int start, int end) {
  if (start >= end) return;
  int pivot = lomuto_partition(list, start, end);  // create partition
  lomuto_quicksort(list, start, pivot - 1);        // sort first half
  lomuto_quicksort(list, pivot + 1, end);          // sort last half
}

int main() {
  std::vector<int> list;
  std::string line_of_input;
  // fill the list of numbers
  while (std::getline(std::cin, line_of_input)) {
    int val = std::stoi(line_of_input);
    list.push_back(val);
  }
  // sort
  lomuto_quicksort(list, 0, list.size() - 1);
  // output ordered elements
  for (int x : list)
    std::cout << std::setfill('0') << std::setw(9) << x << '\n';
  return 0;
}
