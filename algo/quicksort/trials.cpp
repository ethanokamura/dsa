#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

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

int lomuto_partition(std::vector<int>& list, int start, int end,
                     const size_t size) {
  const size_t med_of_three_value = size;  // read README.md
  int med;
  if ((end - start + 1) >= med_of_three_value)
    med = med_of_three(list, start, end);
  else
    med = end;
  std::swap(list.at(med), list.at(end));
  int pivot = list.at(end);
  int boundary = start - 1;
  for (int i = start; i < end; i++) {
    if (list.at(i) <= pivot) {
      boundary++;
      std::swap(list.at(boundary), list.at(i));
    }
  }
  std::swap(list.at(boundary + 1), list.at(end));
  return boundary + 1;
}

void lomuto_quicksort(std::vector<int>& list, int start, int end,
                      const size_t size) {
  if (start >= end) return;

  int med = lomuto_partition(list, start, end, size);
  lomuto_quicksort(list, start, med - 1, size);
  lomuto_quicksort(list, med + 1, end, size);
}

int main() {
  const int SIZE = 4;
  // sum of the fastest constants
  int sum = 0;
  // the amount of times I wanted to run the files
  int trials = 5;
  // keep track of what trial we are on
  int iteration = 0;
  // list of files in my home directory
  std::string files[SIZE] = {"9K.txt", "99K.txt", "999K.txt", "9M.txt"};
  // values to test
  const size_t const_value[SIZE] = {23, 24, 25, 26};

  for (int trials_left = trials; trials_left > 0; trials_left--) {
    for (int i = 0; i < SIZE; i++) {
      std::vector<int> list;
      std::string file_name;
      std::string line_of_input;

      // open file / create list
      {
        file_name = "../datasets/data/" + files[i];
        std::fstream file(file_name);
        while (std::getline(file, line_of_input)) {
          int val = std::stoi(line_of_input);
          list.push_back(val);
        }
      }

      // create a few copies of the list to sort!
      std::vector<int> list_of_list[SIZE] = {list};
      // keep track of the amount of
      long double entries_per_second[SIZE];

      // time it against the list of const sizes
      for (int j = 0; j < SIZE; j++) {
        std::clock_t time = std::clock();  // start
        lomuto_quicksort(list_of_list[j], 0, list_of_list[j].size() - 1,
                         const_value[j]);
        time = std::clock() - time;  // stop
        // how fast it is per data entry
        entries_per_second[j] =
            list.size() / (static_cast<long double>(time) / CLOCKS_PER_SEC);
      }

      // find fastest time
      float fastest_time = entries_per_second[0];
      int min_index = 0;
      for (int j = 0; j < SIZE; j++) {
        if (entries_per_second[j] > fastest_time) {
          fastest_time = entries_per_second[j];
          min_index = j;
        }
      }
      // output fastest times
      std::cout << "[trial " << iteration + 1
                << "] const: " << const_value[min_index] << " for " << files[i]
                << '\n';
      sum += const_value[min_index];
      iteration++;
    }
  }
  // print average (really the only output I needed)
  std::cout << "AVG: " << sum / (SIZE * trials) << '\n';
  return 0;
}
