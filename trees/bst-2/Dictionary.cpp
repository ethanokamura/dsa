/**
 * @author Ethan Okamura (eokamura)
 * @email: eokamura@ucsc.edu
 * @file Dictionary.cpp
 * @brief Implementation of Dictionary ADT
 * @status: working / tested
 */

#include "Dictionary.h"

// Constants
constexpr char NEWLINE = '\n';

// ANSI Color Codes
constexpr const char* RST = "\x1B[0m";
constexpr const char* RED = "\x1B[31m";

/**
 * @brief Handles test failures by throwing an exception.
 * @param message The error message.
 * @note [[noreturn]] ensures function never returns.
 */
[[noreturn]] void handleFailure(const std::string& message) {
  std::cerr << "Dictionary: " << RED << message << RST << NEWLINE;
  throw std::invalid_argument(message);
}

// Class Constructors & Destructors ----------------------------------------

// Creates new Node in the empty state.
Dictionary::Node::Node(keyType k, valType v)
    : key(k), val(v), parent(this), left(this), right(this) {}

// Creates new Dictionary in the empty state.
Dictionary::Dictionary() : num_pairs(0) {
  nil = new Node("NIL", -1);
  root = current = nil;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D)
    : nil(new Node("NIL", -1)), root(nil), current(nil), num_pairs(0) {
  preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
  if (root != nil) postOrderDelete(root);
  delete nil;
  nil = root = current = nullptr;
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const { return num_pairs; }

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
  Node* res = search(root, k);
  return res != nil;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
  Node* res = search(root, k);
  if (res == nil) handleFailure("Missing key -> getValue()");
  return res->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false
// otherwise.
bool Dictionary::hasCurrent() const { return current != nil; }

// currentKey()
// Returns the current key.
// Pre: hasCurrent()
keyType Dictionary::currentKey() const {
  if (!hasCurrent()) handleFailure("NIL value -> currentKey()");
  return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
  if (!hasCurrent()) handleFailure("NIL value -> currentVal()");
  return current->val;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
  postOrderDelete(root);
  root = current = nil;
  num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v,
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
  // check if it's empty
  if (root == nil) {
    root = new Node(k, v);
    root->parent = root->left = root->right = nil;
    current = root;
    num_pairs++;
    return;
  }

  // keep track of prev and current
  Node* prev = nil;
  Node* current = root;

  // find the correct empty spot to insert val
  while (current != nil) {
    prev = current;
    // key already in tree
    if (k == current->key) {
      current->val = v;
      return;
    }
    current = k < current->key ? current->left : current->right;
  }  // temp is guaranteed null

  // create new node
  Node* node = new Node(k, v);

  // first attachment
  node->parent = prev;
  node->left = node->right = nil;

  // update correct pointers
  // second attatchment
  if (k < prev->key)
    prev->left = node;
  else
    prev->right = node;
  num_pairs++;
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
  Node* res = search(root, k);
  // check to make sure the tree isn't empty
  if (res == nil) handleFailure("Missing key -> remove()");
  deleteNode(res);
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::begin() {
  if (num_pairs == 0) return;
  current = findMin(root);
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::end() {
  if (num_pairs == 0) return;
  current = findMax(root);
}

// next()
// If the current iterator is not at the last pair, advances current
// to the next pair (as defined by the order operator < on keys). If
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
  if (!hasCurrent()) handleFailure("NIL value -> next()");
  current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to
// the previous pair (as defined by the order operator < on keys). If
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
  if (!hasCurrent()) handleFailure("NIL value -> prev()");
  current = findPrev(current);
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value
// are separated by the sequence space-colon-space " : ". The pairs are arranged
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
  std::string str;
  inOrderString(str, root);
  return str;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
  std::string str;
  preOrderString(str, root);
  return str;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
  if (num_pairs != D.num_pairs) return false;
  return to_string() == D.to_string();
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
  if (R == nil) return;
  inOrderString(s, R->left);
  s += R->key + " : " + std::to_string(R->val) + '\n';
  inOrderString(s, R->right);
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
  if (R == nil) return;
  s += R->key + '\n';
  preOrderString(s, R->left);
  preOrderString(s, R->right);
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
  if (R == N) return;
  setValue(R->key, R->val);
  preOrderCopy(R->left, N);
  preOrderCopy(R->right, N);
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R) {
  if (R == nil) return;
  postOrderDelete(R->left);
  postOrderDelete(R->right);
  if (R == R->parent->left) {
    R->parent->left = nil;
  } else {
    R->parent->right = nil;
  }
  num_pairs--;
  delete R;
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
  // found or not found
  if (R == nil || R->key == k) return R;
  // search left or search right
  return (k < R->key) ? search(R->left, k) : search(R->right, k);
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
  if (R == nil) return nil;
  while (R->left != nil) R = R->left;
  return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
  if (R == nil) return nil;
  while (R->right != nil) R = R->right;
  return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findNext(Node* N) {
  if (N == nil) return nil;
  if (N->right != nil) return findMin(N->right);
  Node* temp = N->parent;
  while (temp != nil && N == temp->right) {
    N = temp;
    temp = temp->parent;
  }
  return temp;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
  if (N == nil) return nil;
  if (N->left != nil) return findMax(N->left);
  Node* temp = N->parent;
  while (temp != nil && N == temp->left) {
    N = temp;
    temp = temp->parent;
  }
  return temp;
}

void Dictionary::deleteNode(Node* N) {
  // check if the tree is empty
  if (N == nil) return;
  // preserve cursor
  Node* temp = (N == current) ? nil : current;
  // find the target node (node to be deleted)
  Node* target = (N->left == nil || N->right == nil) ? N : findNext(N);
  // determine the child node of the target
  Node* child = (target->left != nil) ? target->left : target->right;
  // reassign parent (disconnecting target)
  if (child != nil) {
    child->parent = target->parent;
  }
  // handle the case when target is the root or its parent's child
  if (target->parent == nil) {
    root = child;
  } else {
    if (target == target->parent->left) {
      target->parent->left = child;
    } else {
      target->parent->right = child;
    }
  }
  // if target is different from N, copy the target’s key to N
  if (target != N) N->key = target->key;
  // delete the target node
  delete target;
  // decrement the count
  num_pairs--;
  // reset the cursor
  current = temp;
}

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
  return stream << D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals().
bool operator==(const Dictionary& A, const Dictionary& B) {
  return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=(const Dictionary& D) {
  clear();
  preOrderCopy(D.root, findMax(D.root));
  return *this;
}
