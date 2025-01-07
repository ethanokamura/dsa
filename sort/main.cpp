#include <iomanip>
#include <iostream>
#include <vector>

// partition the list!
int partition(std::vector<int>& list, int left, int right, int pivot) {
  while (left <= right) {
    while(list[left] < pivot) { left++; }
    while (list[right] > pivot) { right--; }
    if (left <= right) {
      std::swap(list[left], list[right]);
      left++;
      right--;
    }
  }
  return left;
}

// quick sort!
void quicksort(std::vector<int>& list, int left, int right) {
  if (left >= right) return;
  int pivot = list[(left + right)/2];
  int index = partition(list, left, right, pivot);
  quicksort(list, left, index - 1);
  quicksort(list, index, right);
}

// merge list
void merge_halves(std::vector<int>& list, std::vector<int>& temp_list, int left, int right) {
  int newLeft = (right + left) / 2;
  int newRight = newLeft + 1;
  int size = right - left + 1;
  int curLeft = left;
  int curRight = newRight;
  int index = left;

  while (curLeft <= left && curRight <= right) {
    if (list[curLeft] <= list[curRight]) {
      temp_list[index] = list[curLeft];
      curLeft++;
    } else {
      temp_list[index] = list[curRight];
      curRight++;
    }
    index++;
  }

  for (int i = curLeft; i < newLeft - curLeft + 1; i++) {
    temp_list[i] = list[i];
  }

  for (int i = curRight; i < right - curRight + 1; i++) {
    temp_list[i] = list[i];
  }
}

// merge sort!
void merge_sort(std::vector<int>& list, std::vector<int>& temp_list, int left, int right) {
  if (left >= right) return;
  int middle = (left + right) / 2;
  merge_sort(list, temp_list, left, middle);
  merge_sort(list, temp_list, middle + 1, right);
  merge_halves(list, temp_list, left, right);
}

// output ordered elements
void print_list(std::string type, std::vector<int> list) {
  std::cout << type << ":\n";
  for (int x : list) {
    std::cout << std::setfill('0') << std::setw(9) << x << '\n';
  }
}

int main() {
  std::vector<int> list;
  std::string line_of_input;
  // fill the list of numbers
  while (std::getline(std::cin, line_of_input)) {
    int val = std::stoi(line_of_input);
    list.push_back(val);
  }
  // quicksort
  std::vector<int> quicksort_list = list;
  quicksort(quicksort_list, 0, quicksort_list.size() - 1);
  print_list("quicksort", quicksort_list);

  // merge sort
  std::vector<int> merge_sort_list = list;
  std::vector<int> temp_merge_list = merge_sort_list;
  merge_sort(merge_sort_list, temp_merge_list, 0, merge_sort_list.size() - 1);
  print_list("merge sort", merge_sort_list);

  return 0;
}
