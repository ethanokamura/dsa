/**
 * @author Ethan Okamura
 * @file List.cpp
 * @brief Implementation of List ADT
 * @status: working / tested
 */

#include "List.h"

#include <unordered_map>

List::Node::Node(ListElement x) : data(x), next(nullptr), prev(nullptr) {}

// Creates new List in the empty state.
List::List() : pos_cursor(0), num_elements(0) {
  frontDummy = new Node(-1);
  backDummy = new Node(-1);
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;
  beforeCursor = frontDummy;
  afterCursor = backDummy;
}

// Copy constructor.
List::List(const List &L) : List() {
  Node *current = L.frontDummy->next;
  while (current != L.backDummy) {
    insertBefore(current->data);
    current = current->next;
  }
}

// Destructor
List::~List() {
  Node *current = frontDummy;
  while (current != nullptr) {
    Node *next = current->next;
    delete current;
    current = next;
  }
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const { return num_elements; }

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
  if (num_elements == 0) throw std::logic_error("Empty List: Calling front()");
  return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
  if (num_elements == 0) throw std::logic_error("Empty List: Calling back()");
  return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const { return pos_cursor; }

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
  if (afterCursor == backDummy)
    throw std::domain_error("Out of Bounds: Calling peekNext()");
  return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
  if (beforeCursor == frontDummy)
    throw std::domain_error("Out of Bounds: Calling peekPrev()");
  return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
  Node *current = frontDummy->next;
  while (current != backDummy) {
    Node *next = current->next;
    delete current;
    current = next;
  }
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;
  beforeCursor = frontDummy;
  afterCursor = backDummy;
  pos_cursor = 0;
  num_elements = 0;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
  if (num_elements == 0) return;
  beforeCursor = frontDummy;
  afterCursor = frontDummy->next;
  pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
  if (num_elements == 0) return;
  beforeCursor = backDummy->prev;
  afterCursor = backDummy;
  pos_cursor = num_elements;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<length()
ListElement List::moveNext() {
  if (pos_cursor >= num_elements)
    throw std::domain_error("Out of Bounds: Calling moveNext()");
  beforeCursor = beforeCursor->next;
  afterCursor = beforeCursor->next;
  pos_cursor++;
  return beforeCursor->data;  // Return passed-over element
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
ListElement List::movePrev() {
  if (pos_cursor <= 0)
    throw std::domain_error("Out of Bounds: Calling movePrev()");
  beforeCursor = beforeCursor->prev;
  afterCursor = beforeCursor->next;
  pos_cursor--;
  return afterCursor->data;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
  Node *n = new Node(x);
  n->next = afterCursor;
  n->prev = beforeCursor;
  beforeCursor->next = n;
  afterCursor->prev = n;
  beforeCursor = n;
  pos_cursor++;
  num_elements++;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
  Node *n = new Node(x);
  n->next = afterCursor;
  n->prev = beforeCursor;
  beforeCursor->next = n;
  afterCursor->prev = n;
  afterCursor = n;
  num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
  if (pos_cursor >= num_elements)
    throw std::domain_error("Out of Bounds: Calling setAfter()");
  afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
  if (pos_cursor <= 0)
    throw std::domain_error("Out of Bounds: Calling setBefore()");
  beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
  if (pos_cursor >= num_elements)
    throw std::domain_error("Out of Bounds: Calling eraseAfter()");
  Node *temp = afterCursor;
  beforeCursor->next = temp->next;
  temp->next->prev = beforeCursor;
  delete temp;
  afterCursor = beforeCursor->next;
  num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
  if (pos_cursor <= 0)
    throw std::domain_error("Out of Bounds: Calling eraseBefore()");
  Node *temp = beforeCursor;
  beforeCursor = beforeCursor->prev;
  beforeCursor->next = afterCursor;
  afterCursor->prev = beforeCursor;
  delete temp;
  num_elements--;
  pos_cursor--;
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1.
int List::findNext(ListElement x) {
  moveNext();
  while (afterCursor != backDummy) {
    if (peekPrev() == x) return pos_cursor;
    moveNext();
  }
  return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1.
int List::findPrev(ListElement x) {
  movePrev();
  while (beforeCursor != frontDummy) {
    if (peekNext() == x) return pos_cursor;
    movePrev();
  }
  return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost
// occurrance of each element, and removing all other occurances. The cursor
// is not moved with respect to the retained elements, i.e. it lies between
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
  Node *cur = frontDummy->next;
  std::unordered_map<int, int> freq;
  int index = 0;
  int old_pos = pos_cursor;
  while (cur != backDummy) {
    if (freq[cur->data] > 0) {
      if (cur == beforeCursor) beforeCursor = beforeCursor->prev;
      Node *temp = cur;
      cur = cur->next;
      temp->prev->next = temp->next;
      temp->next->prev = temp->prev;
      delete temp;
      num_elements--;
      if (index < old_pos) pos_cursor--;
    } else {
      freq[cur->data]++;
      cur = cur->next;
    }
    index++;
  }
  afterCursor = beforeCursor->next;
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List &L) const {
  List c;
  if (num_elements == 0) {
    c = L;
    c.moveFront();
    return c;
  }
  if (L.num_elements == 0) {
    c = *this;
    c.moveFront();
    return c;
  }
  Node *front = frontDummy->next;
  for (int i = 0; i < length(); i++) {
    c.insertAfter(front->data);
    front = front->next;
  }
  Node *frontL = L.frontDummy->next;
  for (int i = 0; i < L.length(); i++) {
    c.insertAfter(frontL->data);
    frontL = frontL->next;
  }
  c.moveFront();
  return c;
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
  std::string str = "(";
  Node *current = frontDummy->next;
  while (current->next) {
    str += std::to_string(current->data);
    current = current->next;
    if (current->next) str += ", ";
  }
  str += ")";
  return str;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List &R) const {
  if (length() != R.length()) return false;
  Node *current = frontDummy->next;
  Node *other = R.frontDummy->next;
  while (current) {
    if (other->data != current->data) return false;
    current = current->next;
    other = other->next;
  }
  return true;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream &operator<<(std::ostream &stream, const List &L) {
  return stream << L.to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged.
bool operator==(const List &A, const List &B) { return A.equals(B); }

// operator=()
// Overwrites the state of this List with state of L.
List &List::operator=(const List &L) {
  if (this != &L) {
    List temp = L;
    std::swap(frontDummy, temp.frontDummy);
    std::swap(backDummy, temp.backDummy);
    std::swap(afterCursor, temp.afterCursor);
    std::swap(beforeCursor, temp.beforeCursor);
    std::swap(pos_cursor, temp.pos_cursor);
    std::swap(num_elements, temp.num_elements);
  }
  return *this;
}
