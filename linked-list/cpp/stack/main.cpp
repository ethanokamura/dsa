/**
 * @author Ethan Okamura
 * @file main.cpp
 * @brief created a program to demonstrate a simple stack data structure.
 */

#include <iostream>

#include "stack.h"

int main() {
  Stack<std::string> stack;
  std::string input;
  while (std::getline(std::cin, input)) stack.push(input);
  while (stack.size() > 0) {
    std::cout << stack.top() << '\n';
    stack.pop();
  }
  return 0;
}
