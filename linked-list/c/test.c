#include "linked_list.h"
#include <assert.h>
#include <stdio.h>

// Helper macro for test results
#define RUN_TEST(test)                                                         \
  do {                                                                         \
    if (test()) {                                                              \
      printf(#test " PASSED\n");                                               \
    } else {                                                                   \
      printf(#test " FAILED\n");                                               \
    }                                                                          \
  } while (0)

int test_linked_list_init() {
  LinkedList* list = create_list();
  return list->head == NULL && list->tail == NULL && list->size == 0;
}

int test_push_back() {
  LinkedList* list = create_list();

  push_back(list, 10);
  push_back(list, 20);

  return list->size == 2 && list->head != NULL && list->tail != NULL &&
         list->head->data == 10 && list->tail->data == 20;
}

int test_push_front() {
  LinkedList* list = create_list();

  push_front(list, 10);
  push_front(list, 20);

  return list->size == 2 && list->head != NULL && list->tail != NULL &&
         list->head->data == 20 && list->tail->data == 10;
}

int test_pop_front() {
  LinkedList* list = create_list();

  push_back(list, 10);
  push_back(list, 20);

  pop_front(list);

  return list->size == 1 && list->head->data == 20 && list->tail->data == 20;
}

int test_pop_back() {
  LinkedList* list = create_list();
  push_back(list, 10);
  push_back(list, 20);

  pop_back(list);

  return list->size == 1 && list->head->data == 10 && list->tail->data == 10;
}

int test_clear() {
  LinkedList* list = create_list();
  push_back(list, 10);
  push_back(list, 20);
  clear(list);
  return list->size == 0 && list->head == NULL && list->tail == NULL;
}

int test_contains() {
  LinkedList* list = create_list();
  push_back(list, 10);
  push_back(list, 20);

  return contains(list, 10) && !contains(list, 30);
}

int test_reverse() {
  LinkedList* list = create_list();
  push_back(list, 10);
  push_back(list, 20);
  push_back(list, 30);

  reverse(list);

  return list->head->data == 30 && list->tail->data == 10 && list->size == 3;
}

int main() {
  RUN_TEST(test_linked_list_init);
  RUN_TEST(test_push_back);
  RUN_TEST(test_push_front);
  RUN_TEST(test_pop_front);
  RUN_TEST(test_pop_back);
  RUN_TEST(test_clear);
  RUN_TEST(test_contains);
  RUN_TEST(test_reverse);
  return 0;
}
