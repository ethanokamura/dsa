/**
 * @author Ethan Okamura (eokamura)
 * @email: ethanokamura3@gmail.com
 * @file main.cpp
 * @brief created a program to demonstrate a simple queue data structure.
 */

#include <iostream>

#include "queue.h"

int main() {
  Queue<std::string> queue;
  std::string input;
  while (std::getline(std::cin, input)) queue.push(input);
  while (queue.size() > 0) {
    std::cout << queue.front() << '\n';
    queue.pop();
  }
  return 0;
}
