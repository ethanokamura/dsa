/**
 * @author Ethan Okamura
 * @file binary_search_tree.cpp
 * @brief implementing member functions for the binary search tree
 * @note used smart pointers to take care of deleting my int*
 */

#include "binary_search_tree.h"

// list constructor
BinarySearchTree::BinarySearchTree(std::initializer_list<int> init_list)
    : root(nullptr), n(0) {
  for (int i : init_list) insert(i);
}

// default destructor
BinarySearchTree::~BinarySearchTree() {
  if (root) delete_all(root);
}

// insert a value if it is not already inside the structure - O(h)
bool BinarySearchTree::insert(int val) {
  // check if value already exists
  if (find(val)) return false;

  Node* node = new Node(val);

  // check if it's empty
  if (!root) {
    root = node;
    n++;
    return true;
  }

  Node* prev = nullptr;
  Node* current = root;


  // find the correct empty spot to insert val
  while (current) {
    prev = current;
    current = val < current->key
      ? current->left
      : current->right;
  }  // temp is guaranteed null

  // first attachment
  node->parent = prev;
  // update correct pointers
  // second attatchment
  if (val < prev->key)
    prev->left = node;
  else
    prev->right = node;
  n++;
  return true;
}

// Find the value inside the structure - O(h)
BinarySearchTree::Node* BinarySearchTree::search(Node* node, int key) {
  // found or not found
  if (!node || node->key == key) return node;
  // search left or search right
  if (key < node->key) return search(node->left, key);
  return search(node->right, key);
}

// Find the smallest value inside the structure - O(h)
BinarySearchTree::Node* BinarySearchTree::min(Node* node) const {
  if (!node) return nullptr;
  while (node->left) node = node->left;
  return node;
}

// Find the largest value inside the structure - O(h)
BinarySearchTree::Node* BinarySearchTree::max(Node* node) const {
  if (!node) return nullptr;
  while (node->right) node = node->right;
  return node;
}

// find next largest node down the tree
// (typically the node to the right)
BinarySearchTree::Node* BinarySearchTree::successor(Node* node) {
  if (!node) return nullptr;
  if (node->right) return min(node->right);
  Node* temp = node->parent;
  while (temp && node == temp->right) {
    node = temp;
    temp = temp->parent;
  }
  return temp;
}

// find next smallest node down the tree
// (typically the node to the left)
BinarySearchTree::Node* BinarySearchTree::predecessor(Node* node) {
  if (!node) return nullptr;
  if (node->left) return max(node->left);
  Node* temp = node->parent;
  while (temp && node == temp->left) {
    node = temp;
    temp = temp->parent;
  }
  return temp;
}

// build a list with inorder traversal
void BinarySearchTree::in_order(Node* x, std::vector<int>& list) {
  if (!x) return;
  in_order(x->left, list);
  list.push_back(x->key);
  in_order(x->right, list);
}

// build a list with preorder traversal
void BinarySearchTree::pre_order(Node* x, std::vector<int>& list) {
  if (!x) return;
  list.push_back(x->key);
  pre_order(x->left, list);
  pre_order(x->right, list);
}

// build a list with postorder traversal
void BinarySearchTree::post_order(Node* x, std::vector<int>& list) {
  if (!x) return;
  post_order(x->left, list);
  post_order(x->right, list);
  list.push_back(x->key);
}

// delete all nodes in the tree
void BinarySearchTree::delete_all(Node* node) {
  if (!node) return;
  delete_all(node->left);
  delete_all(node->right);
  delete_node(node);
}

// delete a specific node in the tree
void BinarySearchTree::delete_node(Node* node) {
  // check to make sure the tree isn't empty
  if (!node) return;

  // value to be stranded
  // if the target has 0 or 1 child(ren) then we set it to the current node
  // if the node has two children, we set the target to the successor node
  Node* target = (!node->left || !node->right) ? node : successor(node);

  // set child node
  Node* child = (target->left) ? target->left : target->right;
  // reassign parent (first disconnection)
  if (child) child->parent = target->parent;
  // check if node has a parent
  // if so, figure out what child it is
  if (!target->parent)
    root = child;
  else if (target == target->parent->left)
    target->parent->left = child;
  else
    target->parent->right = child;
  // if target is different than the node param
  if (target != node) {
    // copy target to new node?
    node->key = target->key;
  }
  // delete target!
  delete target;
  n--;
}

// get the value of the root
int BinarySearchTree::get_root() const {
  if (!root) return -1;
  return root->key;
}

// get the value of a node's successor
int BinarySearchTree::get_successor(int key) {
  Node* node = search(root, key);
  Node* res = successor(node);
  if (res) return res->key;
  return -1;
}

// get the value of a node's predecessor
int BinarySearchTree::get_predecessor(int key) {
  Node* node = search(root, key);
  Node* res = predecessor(node);
  if (res) return res->key;
  return -1;
}

// return list with inorder traversal
std::vector<int> BinarySearchTree::get_inorder() {
  std::vector<int> list;
  in_order(root, list);
  return list;
}

// return list with preorder traversal
std::vector<int> BinarySearchTree::get_preorder() {
  std::vector<int> list;
  pre_order(root, list);
  return list;
}

// return list with postorder traversal
std::vector<int> BinarySearchTree::get_postorder() {
  std::vector<int> list;
  post_order(root, list);
  return list;
}
