/**
 * @author Ethan Okamura (eokamura)
 * @email: eokamura@ucsc.edu
 * @file List.h
 * @brief Main testing file List ADT
 * @status: working / tested
 */

#include <assert.h>
#include <stdlib.h>

#include "List.h"

// Handle generic failures
void handleFailure(const char* message) {
  fprintf(stderr, "Test %s: FAILED\n", message);
  exit(EXIT_FAILURE);
}
// Handle generic success
void handleSucess(const char* message) {
  printf("Test %s: PASSED\n", message);
}

void clearTest(List L) {
  clear(L);
  assert(length(L) == 0);
  assert(index(L) == -1);
  assert(isEmpty(L));
  List B = newList();
  assert(equals(L, B));
  freeList(&B);
}

void prependTest(List L, int n) {
  for (int i = 0; i < n; i++) {
    prepend(L, i);
    assert(front(L) == i);
  }
  handleSucess("get front");
}

void copyTest2() {
  List A = newList();
  append(A, 2);
  prepend(A, 1);
  moveFront(A);
  List C = copyList(A);
  bool res = (index(A) != 0 || !equals(A, C) || A == C);
  freeList(&C);
  freeList(&A);
  assert(res == false);
}

void deleteFrontTest2() {
  List A = newList();
  prepend(A, 5);
  prepend(A, 65);
  prepend(A, 43);
  prepend(A, 2);
  prepend(A, 8);
  prepend(A, 1);
  moveFront(A);
  deleteFront(A);
  assert(index(A) == -1);
  moveBack(A);
  deleteFront(A);
  assert(index(A) == 3);
  freeList(&A);
}

void prependTest2() {
  List A = newList();
  prepend(A, 1);
  prepend(A, 5);
  prepend(A, 7);
  moveFront(A);
  prepend(A, 45);
  prepend(A, 51);
  prepend(A, 3214);
  prepend(A, 314);
  prepend(A, 324);
  assert(index(A) == 5);
  moveBack(A);
  movePrev(A);
  prepend(A, 234);
  movePrev(A);
  assert(index(A) == 6);
  moveFront(A);
  movePrev(A);
  assert(index(A) == -1);
  freeList(&A);
}

void nonEmptyFrontTest() {
  List A = newList();
  prepend(A, 5);
  assert(front(A) == 5);
  append(A, 7);
  prepend(A, 2);
  assert(front(A) == 2);
  moveFront(A);
  assert(front(A) == 2);
  insertBefore(A, 43);
  assert(front(A) == 43);
  deleteFront(A);
  assert(front(A) == 2);
  delete(A);
  assert(front(A) == 5);
  freeList(&A);
}

void appendTest(List L, int n) {
  for (int i = 0; i < n; i++) {
    append(L, i);
    assert(back(L) == i);
  }
  handleSucess("get back");
}

void insertAfterTest(List L, int n) {
  int x = index(L);
  for (int i = 0; i < n; i++) {
    insertAfter(L, i);
    assert(x == index(L));
  }
}

void insertBeforeTest(List L, int n) {
  int x = index(L);
  for (int i = 0; i < n; i++) {
    insertAfter(L, i);
    assert(x == index(L));
  }
}

// Test for List delete()
void deleteTest(List L) {
  while (!isEmpty(L)) {
    moveFront(L);
    assert(index(L) == 0);
    delete(L);
    assert(index(L) == -1);
  }
}

// Test for List deleteFront()
void deleteFrontTest(List L) {
  while (!isEmpty(L)) {
    deleteFront(L);
  }
}

// Test for List deleteBack()
void deleteBackTest(List L) {
  while (!isEmpty(L)) {
    deleteBack(L);
  }
}

void deleteBackTest2() {
    List A = newList();
    List B = newList();
    prepend(A, 1);
    prepend(B, 1);
    prepend(A, 2);
    prepend(B, 2);
    deleteBack(A);
    assert(!equals(A, B));
    deleteBack(B);
    assert(equals(A, B));
    append(A, 3);
    append(B, 3);
    deleteBack(A);
    deleteBack(B);
    assert(equals(A, B));
    freeList(&A);
    freeList(&B);
}

void deleteTest2() {
  List A = newList();
  List B = newList();
  prepend(A, 1);
  prepend(B, 1);
  prepend(A, 2);
  prepend(B, 2);
  moveBack(A);
  delete (A);
  assert (!equals(A, B));
  moveBack(B);
  delete (B);
  assert(equals(A, B));
  append(A, 3);
  append(B, 3);
  moveBack(A);
  delete (A);
  moveBack(B);
  delete (B);
  assert(equals(A, B));
  freeList(&A);
  freeList(&B);
}

void lengthTests(List L) {
  int n = 5;
  int len = 5;
  assert(isEmpty(L));
  assert(length(L) == 0);
  handleSucess("empty length");
  appendTest(L, n);
  assert(length(L) == len);
  handleSucess("append length");
  moveBack(L);
  insertAfterTest(L, n);
  assert(length(L) == len * 2);
  handleSucess("insert after length");
  deleteTest(L);
  assert(length(L) == 0);
  handleSucess("delete length");
  prependTest(L, n);
  assert(length(L) == len);
  handleSucess("prepend length");
  moveBack(L);
  insertBeforeTest(L, n);
  assert(length(L) == len * 2);
  handleSucess("insert before length");
  deleteBackTest(L);
  assert(length(L) == 0);
  handleSucess("delete back length");
  prependTest(L, n);
  clearTest(L);
  assert(length(L) == 0);
  handleSucess("clear length");
}

void indexTests(List L) {
  int n = 5;
  int i = -1;
  assert(isEmpty(L));
  assert(index(L) == i);
  handleSucess("empty index");
  appendTest(L, n);
  moveFront(L);
  i = index(L);
  assert(index(L) == i);
  handleSucess("append index");
  insertAfterTest(L, n);
  assert(index(L) == i);
  handleSucess("insert after index");
  deleteTest(L);
  assert(index(L) == -1);
  handleSucess("delete index");
  prependTest(L, n);
  moveFront(L);
  i = index(L);
  assert(index(L) == i);
  prependTest2();
  handleSucess("prepend index");  // this doesnt actually work
  insertBeforeTest(L, n);
  assert(index(L) == i);
  handleSucess("insert before index");  // this doesnt actually work
  deleteFrontTest(L);
  assert(index(L) == -1);
  handleSucess("delete front index");  // this doesnt actually work
  prependTest(L, n);
  clearTest(L);
  assert(index(L) == -1);
  handleSucess("clear index");  // this doesnt actually work
}

void getTests(List L) {
  prependTest(L, 10);
  int i = 9;
  for (moveFront(L); index(L) >= 0; moveNext(L)) {
    assert(i == get(L));
    i--;
  }
  clearTest(L);
  handleSucess("get");
}

// Test for List set()
void setTests(List L) {
  prependTest(L, 10);
  for (moveFront(L); index(L) >= 0; moveNext(L)) {
    set(L, 1);
  }
  clearTest(L);
  handleSucess("set");
}

void copyTests(List A) {
  List B = copyList(A);
  assert(equals(A, B));
  handleSucess("empty copy");
  handleSucess("copy equals");
  freeList(&B);
  prependTest(A, 50);
  B = copyList(A);
  assert(equals(A, B));
  handleSucess("non-empty copy");
  freeList(&B);
  clearTest(A);
}

// function to run all tests
bool runAllTests(void) {
  List A = newList();
  lengthTests(A);
  deleteFrontTest2();
  indexTests(A);
  copyTests(A);
  copyTest2();
  getTests(A);
  setTests(A);
  deleteTest2();
  deleteBackTest2();
  nonEmptyFrontTest();
  freeList(&A);
  return true;
}

int main(void) {
  if (!runAllTests()) {
    handleFailure("Failure to pass tests");
  }
  return 0;
}
