/**
 * @author Ethan Okamura (eokamura)
 * @email: ethanokamura3@gmail.com
 * @assignment: Programming Assignment 7 [p7]
 * @file main.cpp
 * @brief created a program to allow the user to interact
 *        with my binary search tree structure.
 * @status: working / tested
 * @issues: compiles without warning using the flags
 *          -Wall -Wextra -pedantic
 * @notes: I had to do a few small fixes to some of the functions
 */

#include <iostream>

#include "binary_search_tree.h"

// insert a value to the tree!
void ins(BinarySearchTree& tree, int val) {
  if (tree.insert(val)) std::cout << "inserted " << val << ".\n";
}

// delete a value from the tree
void del(BinarySearchTree& tree, int val) {
  if (tree.size() < 1 || !tree.find(val)) {
    std::cout << "delete " << val << " - not found.\n";
  } else {
    tree.remove(val);
    std::cout << "deleted " << val << ".\n";
  }
}

// find a value in the tree
void find(BinarySearchTree& tree, int val) {
  std::cout << val << (tree.find(val) ? " found.\n" : " not found.\n");
}

// find the successor of a node
void successor(BinarySearchTree& tree, int val) {
  if (!tree.find(val)) {
    std::cout << val << " not in tree.\n";
    return;
  }
  int res = tree.get_successor(val);
  if (res == -1)
    std::cout << "no successor for " << val << ".\n";
  else
    std::cout << val << " successor is " << res << ".\n";
}

// find the predecessor of a node
void predecessor(BinarySearchTree& tree, int val) {
  if (!tree.find(val)) {
    std::cout << val << " not in tree.\n";
    return;
  }
  int res = tree.get_predecessor(val);
  if (res == -1)
    std::cout << "no predecessor for " << val << ".\n";
  else
    std::cout << val << " predecessor is " << res << ".\n";
}

// print the tree using inorder traversal
void inorder(BinarySearchTree& tree) {
  if (tree.size() == 0) return;
  std::cout << "inorder traversal:\n";
  std::vector<int> list = tree.get_inorder();
  for (std::size_t i = 0; i < tree.size(); i++) {
    std::cout << list[i];
    if (i < tree.size() - 1)
    std::cout << " ";
  }
  std::cout << '\n';
}

// print the tree using preorder traversal
void preorder(BinarySearchTree& tree) {
  if (tree.size() == 0) return;
  std::cout << "preorder traversal:\n";
  std::vector<int> list = tree.get_preorder();
  for (std::size_t i = 0; i < tree.size(); i++) {
    std::cout << list[i];
    if (i < tree.size() - 1)
    std::cout << " ";
  }
  std::cout << '\n';
}

// print the tree using postorder traversal
void postorder(BinarySearchTree& tree) {
  if (tree.size() == 0) return;
  std::cout << "postorder traversal:\n";
  std::vector<int> list = tree.get_postorder();
  for (std::size_t i = 0; i < tree.size(); i++) {
    std::cout << list[i];
    if (i < tree.size() - 1)
    std::cout << " ";
  }
  std::cout << '\n';
}

// find the maximum value in the tree
void max(BinarySearchTree& tree) {
  std::cout << "max is " << tree.get_max() << ".\n";
}

// find the minimum value in the tree
void min(BinarySearchTree& tree) {
  std::cout << "min is " << tree.get_min() << ".\n";
}

int main() {
  // create a tree using the default constructor
  BinarySearchTree tree;
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line[0] != '#') {
      // holds the user's command
      std::string cmd;
      // holds the user's input value
      std::string num_str;
      bool has_num = false;
      // read the lines
      for (char c : line) {
        if (!has_num && c != ' ') cmd += c;
        if (has_num) num_str += c;
        if (c == ' ') has_num = true;
      }
      // turn the value string into int
      int val;
      if (has_num) val = stoi(num_str);
      // had to use if / else structure
      // (cannot use strings in a switch case)
      if (cmd == "insert")
        ins(tree, val);
      else if (cmd == "delete")
        del(tree, val);
      else if (cmd == "search")
        find(tree, val);
      else if (cmd == "successor")
        successor(tree, val);
      else if (cmd == "predecessor")
        predecessor(tree, val);
      else if (cmd == "min")
        min(tree);
      else if (cmd == "max")
        max(tree);
      else if (cmd == "inorder")
        inorder(tree);
      else if (cmd == "preorder")
        preorder(tree);
      else if (cmd == "postorder")
        postorder(tree);
    }
  }
  return 0;
}
