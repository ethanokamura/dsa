/**
 * @author Ethan Okamura (eokamura)
 * @email: eokamura@ucsc.edu
 * @file ListTest.cpp
 * @brief Main testing file List ADT
 * @status: working / tested
 */

#include <cassert>
#include <iostream>

#include "List.h"

using std::cout;
using std::endl;

void testEmptyList() {
  cout << "=== Test Empty List ===" << endl;
  List L;
  assert(L.length() == 0);
  assert(L.position() == 0);
  try {
    L.front();
    assert(false && "front() should throw on empty list");
  } catch (std::logic_error &) {
  }
  try {
    L.back();
    assert(false && "back() should throw on empty list");
  } catch (std::logic_error &) {
  }
  cout << "Empty list tests passed." << endl << endl;
}

void testInsertAndAccess() {
  cout << "=== Test Insertion and Access ===" << endl;
  List L;
  L.moveFront();
  L.insertAfter(10);
  assert(L.length() == 1);
  assert(L.front() == 10 && L.back() == 10);
  cout << "After insertAfter: " << L << endl;
  cout << "position: " << L.position() << endl;
  L.insertBefore(5);
  assert(L.length() == 2);
  assert(L.front() == 5);
  cout << "After insertBefore: " << L << endl;
  cout << "Insertion tests passed." << endl << endl;
}

void testCursorMovement() {
  cout << "=== Test Cursor Movement ===" << endl;
  List L;
  L.moveFront();
  for (int i = 1; i <= 5; i++) {
    L.insertAfter(i);
    L.moveNext();
  }
  assert(L.length() == 5);

  L.moveFront();

  int a = L.moveNext();
  assert(a == 1);
  int b = L.peekNext();
  assert(b == 2);

  L.moveBack();

  int c = L.movePrev();
  assert(c == 5);
  cout << "Cursor movement tests passed." << endl << endl;
}

void testSetAndErase() {
  cout << "=== Test Set and Erase ===" << endl;
  List L;
  L.moveFront();

  L.insertAfter(10);
  L.insertBefore(3);
  L.setAfter(15);

  assert(L.length() == 2);

  L.moveFront();
  L.moveNext();

  L.setAfter(20);
  assert(L.back() == 20);
  L.setBefore(1);
  assert(L.front() == 1);
  cout << "List after setBefore/setAfter: " << L << endl;

  L.eraseAfter();
  assert(L.length() == 1);
  cout << "List after eraseAfter: " << L << endl;

  L.clear();
  L.moveFront();
  for (int i = 1; i <= 5; i++) {
    L.insertAfter(i);
    L.moveNext();
  }

  assert(L.length() == 5);
  L.moveBack();
  L.eraseBefore();

  assert(L.length() == 4);
  cout << "List after eraseBefore: " << L << endl;
  cout << "Set and erase tests passed." << endl << endl;
}

void testFindAndCleanup() {
  cout << "=== Test findNext, findPrev, and cleanup ===" << endl;
  List L;
  L.moveFront();

  L.insertAfter(10);
  L.moveNext();
  L.insertAfter(20);
  L.moveNext();
  L.insertAfter(10);
  L.moveNext();
  L.insertAfter(30);
  L.moveNext();
  L.insertAfter(20);
  L.moveNext();
  cout << "List before cleanup: " << L << endl;
  int pos = L.findPrev(20);
  assert(pos >= 0);

  pos = L.findPrev(30);
  assert(pos >= 0);

  L.cleanup();

  cout << "post clean: " << L << endl;

  assert(L.length() == 3);
  cout << "List after cleanup: " << L << endl;
  cout << "findNext/findPrev/cleanup tests passed." << endl << endl;
}

void testConcatAndCopy() {
  cout << "=== Test concat, copy constructor, and assignment operator ==="
       << endl;
  List L1, L2;
  L1.moveFront();
  L2.moveFront();

  for (int i = 1; i <= 3; i++) {
    L1.insertAfter(i);
    L1.moveNext();
  }

  for (int i = 4; i <= 6; i++) {
    L2.insertAfter(i);
    L2.moveNext();
  }

  List L3 = L1.concat(L2);
  cout << "Concatenated list L3: " << L3 << endl;
  assert(L3.length() == 6);

  List L4 = L3;
  assert(L4 == L3);

  List L5;
  L5 = L3;
  assert(L5 == L3);

  cout << "Copy and assignment tests passed." << endl << endl;
}

void testToStringAndEquals() {
  cout << "=== Test to_string() and equals() ===" << endl;
  List L;
  L.moveFront();
  for (int i = 1; i <= 4; i++) {
    L.insertAfter(i);
    L.moveNext();
  }
  std::string str = L.to_string();
  cout << "List string: " << str << endl;
  List L2 = L;
  assert(L.equals(L2));
  cout << "to_string() and equals() tests passed." << endl << endl;
}

void printStats(List &A) {
  cout << A << endl;
  cout << "pos: " << A.position() << '\n';
  cout << "len: " << A.length() << '\n';
  cout << "front: " << A.front() << '\n';
  cout << "back: " << A.back() << '\n';
  if (A.position() < A.length()) cout << "peekNext: " << A.peekNext() << '\n';
  if (A.position() > 0) cout << "peekPrev: " << A.peekPrev() << '\n';
  cout << endl << endl;
}

int main() {
  testEmptyList();
  testInsertAndAccess();
  testCursorMovement();
  testSetAndErase();
  testFindAndCleanup();
  testConcatAndCopy();
  testToStringAndEquals();

  // Test movePrev by traversing backward and printing each value.
  cout << "=== Test movePrev Traversal ===" << endl;
  List L;
  L.moveFront();
  for (int i = 1; i <= 5; i++) {
    L.insertAfter(i);
    L.moveNext();
  }
  // Now list is (1,2,3,4,5)
  L.moveBack();
  cout << "Traversing backwards: ";
  while (L.position() > 0) {
    int v = L.movePrev();
    cout << v << " ";
  }
  cout << endl;

  cout << "All tests passed." << endl;
  return 0;
}
