#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

/**
 * @author Ethan Okamura
 * @file binary_search_tree.h
 * @brief declaring the member functions and variables for
 *        the binary tree class
 * @note used smart pointers to take care of deleting my int*
 */

#include <initializer_list>
#include <vector>

class BinarySearchTree {
  struct Node;

 public:
  // default constructor
  BinarySearchTree() : root(nullptr), n(0) {}
  // list constructor
  BinarySearchTree(std::initializer_list<int>);
  // destructor
  ~BinarySearchTree();
  // get root of tree
  int get_root() const;
  // public wrapper for min
  int get_min() const { return min(root)->key; }
  // public wrapper for max
  int get_max() const { return max(root)->key; }
  // public wrapper for successor
  int get_successor(int);
  // public wrapper for predecessor
  int get_predecessor(int);
  // in order traversal
  std::vector<int> get_inorder();
  // pre order traversal
  std::vector<int> get_preorder();
  // post order traversal
  std::vector<int> get_postorder();
  // size of BST!
  std::size_t size() const { return n; };
  // public wrapper for search
  bool find(int key) { return search(root, key) != nullptr; }
  // insert value
  bool insert(int);
  // public wrapper for delete
  void remove(int key) { delete_node(search(root, key)); }

 private:
  Node* root;     // root of the BST
  std::size_t n;  // size
  struct Node {
    int key;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    Node(int value)
        : key(value), left(nullptr), right(nullptr), parent(nullptr) {}
    ~Node() { left = right = parent = nullptr; }
  };
  // search for node with value
  Node* search(Node*, int);
  // find minimum value
  Node* min(Node*) const;
  // find max value
  Node* max(Node*) const;
  // find successor
  Node* successor(Node*);
  // find predecessor
  Node* predecessor(Node*);
  // in order traversal
  void in_order(Node*, std::vector<int>&);
  // // pre order traversal
  void pre_order(Node*, std::vector<int>&);
  // // post order traversal
  void post_order(Node*, std::vector<int>&);
  // delete a node
  void delete_node(Node*);
  // remove all nodes recursively
  void delete_all(Node*);
};

#endif  // BINARY_SEARCH_TREE_H
