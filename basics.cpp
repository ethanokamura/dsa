#include <iostream>

using namespace std;

int linear_search(int* list, const int size, int target) {
  for (int i = 0; i < size; i++)
    if (list[i] == target) return i;
  return -1;
}

int binary_search(int* list, const int size, int target) {
  int low = 0;
  int high = size - 1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (list[mid] > target)
      high = mid - 1;
    else if (list[mid] < target)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

void selection_sort(int*& list, const int size) {
  for (int i = 0; i < size; i++) {
    int low = i;
    for (int j = i + 1; j < size; j++)
      if (list[j] < list[low]) low = j;
    swap(list[i], list[low]);
  }
}

void bubble_sort(int*& list, const int size) {
  bool swapped = true;
  while (swapped) {
    swapped = false;
    for (int i = 0; i < size - 1; i++) {
      if (list[i] > list[i + 1]) {
        swap(list[i], list[i + 1]);
        swapped = true;
      }
    }
  }
}

int main() {
  const int size = 12;
  int* list =
      new int[size]{1, 123, 4, 5, 234, 5647, 87, 124, 0, 543, 564, 1232};
  selection_sort(list, size);
  cout << "given the list: [ ";
  for (int i = 0; i < size; i++) {
    cout << i;
    if (i != size - 1) cout << ", ";
  }
  cout << " ]\n";
  int target;
  cout << "enter the target value you would like to find: ";
  cin >> target;
  int result = binary_search(list, size, target);
  if (result != -1) {
    cout << "found target: " << target << " at position " << result << '\n';
  } else {
    cout << target << " was not found!\n";
  }
  return 0;
}
