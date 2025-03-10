/**
 * @author Ethan Okamura (eokamura)
 * @email: eokamura@ucsc.edu
 * @file List.c
 * @brief Implementation file for List ADT
 * @status: working / tested
 */

#include "List.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

// Errors --------------------------------------------------------------------
void handleNullList(const char* message) {
  fprintf(stderr, "List Failure: %s on NULL List reference\n", message);
  exit(EXIT_FAILURE);
}

void handleEmptyList(const char* message) {
  fprintf(stderr, "List Failure: %s on empty List\n", message);
  exit(EXIT_FAILURE);
}

void handleBoundsFailure(const char* message) {
  fprintf(stderr, "List Failure: %s - out of bounds\n", message);
  exit(EXIT_FAILURE);
}

// Structs --------------------------------------------------------------------
// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj {
  ListElement data;
  Node next;
  Node prev;
} NodeObj;

// ListObj type
typedef struct ListObj {
  Node front;
  Node back;
  Node cursor;
  int index;
  int length;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(ListElement data) {
  Node N;
  N = malloc(sizeof(NodeObj));
  assert(N != NULL);
  N->data = data;
  N->next = NULL;
  N->prev = NULL;
  return (N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN) {
  if (pN != NULL && *pN != NULL) {
    free(*pN);
    *pN = NULL;
  }
}

// Lists ----------------------------------------------------------------------
// Creates and returns a new empty List.
List newList(void) {
  List L;
  L = malloc(sizeof(ListObj));
  assert(L != NULL);
  // code that inits L in heap memory
  L->back = L->front = L->cursor = NULL;
  L->index = -1;
  L->length = 0;
  return (L);
}

// Frees all heap memory associated with *pL, and sets
// *pL to NULL.
void freeList(List* pL) {
  if (pL == NULL || *pL == NULL) return;
  while (!isEmpty(*pL)) {
    deleteFront(*pL);
  }
  free(*pL);
  *pL = NULL;
}

// Access functions -----------------------------------------------------------
// Returns the number of elements in L.
int length(List L) {
  if (L == NULL) handleNullList("calling length()");
  return (L->length);
}
// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
  if (L == NULL) handleNullList("calling index()");
  return (L->index);
}
// Returns front element of L. Pre: length()>0
ListElement front(List L) {
  if (L == NULL) handleNullList("calling front()");
  if (isEmpty(L)) handleEmptyList("calling front()");
  return (L->front->data);
}
// Returns back element of L. Pre: length()>0
ListElement back(List L) {
  if (L == NULL) handleNullList("calling back()");
  if (isEmpty(L)) handleEmptyList("calling back()");
  return (L->back->data);
}

// Returns cursor element of L. Pre: length()>0, index()>=0
ListElement get(List L) {
  if (L == NULL) handleNullList("calling get()");
  if (isEmpty(L)) handleEmptyList("calling get()");
  if (index(L) < 0) handleBoundsFailure("calling get()");
  return (L->cursor->data);
}

// Returns true iff Lists A and B contain the same
bool equals(List A, List B) {
  if (A == NULL || B == NULL) handleNullList("calling equals()");
  bool eq;
  Node N, M;
  eq = (A->length == B->length);
  if (eq == false) return false;
  N = A->front;
  M = B->front;
  while (eq && N != NULL) {
    eq = (N->data == M->data);
    N = N->next;
    M = M->next;
  }
  return eq;
}

// Manipulation procedures ----------------------------------------------------
// Resets L to its original empty state.
void clear(List L) {
  if (L == NULL) handleNullList("calling clear()");
  while (!isEmpty(L)) {
    deleteFront(L);
  }
}

// Pre: length()>0, index()>=0
// Overwrites the cursor element’s data with x.
void set(List L, ListElement x) {
  if (L == NULL) handleNullList("calling set()");
  if (isEmpty(L)) handleEmptyList("calling set()");
  if (index(L) < 0) handleEmptyList("calling set()");
  L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
  if (L == NULL) handleNullList("calling moveFront()");
  if (isEmpty(L)) return;
  L->cursor = L->front;
  L->index = 0;
}

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L) {
  if (L == NULL) handleNullList("calling moveBack()");
  if (isEmpty(L)) return;
  L->cursor = L->back;
  L->index = L->length - 1;
}

// If cursor is defined and not at front, move cursor one step toward the front
// of L; if cursor is defined and at front, cursor becomes undefined; if cursor
// is undefined do nothing
void movePrev(List L) {
  // bounds check
  if (L == NULL) handleNullList("calling movePrev()");
  if (L->cursor == NULL) {
    return;
  } else if (L->cursor == L->front) {
    L->cursor = NULL;
    L->index = -1;
  } else {
    L->cursor = L->cursor->prev;
    L->index--;
  }
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
  if (L == NULL) handleNullList("calling moveNext()");
  if (L->cursor == NULL) {
    return;
  } else if (L->cursor == L->back) {
    L->cursor = NULL;
    L->index = -1;
  } else {
    L->cursor = L->cursor->next;
    L->index++;
  }
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, ListElement x) {
  if (L == NULL) handleNullList("calling prepend()");
  Node N = newNode(x);
  if (isEmpty(L)) {
    L->front = L->back = N;
  } else {
    N->next = L->front;
    L->front->prev = N;
    L->front = N;
  }
  L->index++;
  L->length++;
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, ListElement x) {
  if (L == NULL) handleNullList("calling append()");
  Node N = newNode(x);
  if (isEmpty(L)) {
    L->front = L->back = N;
  } else {
    N->prev = L->back;
    L->back->next = N;
    L->back = N;
  }
  L->length++;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, ListElement x) {
  if (L == NULL) handleNullList("calling insertBefore()");
  if (isEmpty(L)) handleEmptyList("calling insertBefore()");
  if (index(L) < 0) handleEmptyList("calling insertBefore()");
  Node n = newNode(x);
  n->prev = L->cursor->prev;
  n->next = L->cursor;
  if (L->cursor->prev != NULL) {
    L->cursor->prev->next = n;
  } else {
    L->front = n;
  }
  L->cursor->prev = n;
  L->index++;
  L->length++;
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, ListElement x) {
  if (L == NULL) handleNullList("calling insertAfter()");
  if (isEmpty(L)) handleEmptyList("calling insertAfter()");
  if (index(L) < 0) handleEmptyList("calling insertAfter()");
  Node n = newNode(x);
  n->next = L->cursor->next;
  n->prev = L->cursor;
  if (L->cursor->next != NULL) {
    L->cursor->next->prev = n;
  } else {
    L->back = n;
  }
  L->cursor->next = n;
  L->length++;
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
  if (L == NULL) handleNullList("calling deleteFront()");
  if (isEmpty(L)) handleEmptyList("calling deleteFront()");
  Node N = NULL;
  N = L->front;
  if (N == L->cursor) {
    L->cursor = NULL;
    L->index = -1;
  } else if (L->index != -1) {
    L->index--;
  }
  if (L->length > 1) {
    L->front = N->next;
    L->front->prev = NULL;
  } else {
    L->front = L->back = NULL;
  }
  freeNode(&N);
  L->length--;
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
  if (L == NULL) handleNullList("calling deleteBack()");
  if (isEmpty(L)) handleEmptyList("calling deleteBack()");
  Node N = L->back;
  if (N == L->cursor) {
    L->cursor = NULL;
    L->index = -1;
  }
  if (L->length > 1) {
    L->back = N->prev;
    L->back->next = NULL;
  } else {
    L->back = L->front = NULL;
  }
  freeNode(&N);
  L->length--;
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
// (next and prev connect)
void delete (List L) {
  if (L == NULL) handleNullList("calling delete()");
  if (isEmpty(L)) handleEmptyList("calling delete()");
  if (L->cursor == NULL) handleEmptyList("calling delete()");
  if (L->cursor == L->back) {
    deleteBack(L);
    return;
  } else if (L->cursor == L->front) {
    deleteFront(L);
    return;
  }
  Node N = L->cursor;
  N->prev->next = N->next;
  N->next->prev = N->prev;
  L->cursor = NULL;
  L->index = -1;
  freeNode(&N);
  L->length--;
}

// Other operations -----------------------------------------------------------
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L) {
  if (L == NULL) handleNullList("calling printList()");
  if (isEmpty(L)) handleEmptyList("calling printList()");
  Node N = NULL;
  for (N = L->front; N != NULL; N = N->next) {
    fprintf(out, FORMAT " ", N->data);
  }
  fprintf(out, "%c", '\n');
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L) {
  if (L == NULL) handleNullList("calling copyList()");
  List list = newList();
  if (isEmpty(L)) return list;
  Node oldCursor = L->cursor;
  int i = L->index;
  moveFront(L);
  while (index(L) >= 0) {
    ListElement x = get(L);
    append(list, x);
    moveNext(L);
  }
  L->cursor = oldCursor;
  L->index = i;
  return list;
}

// Helpers  -------------------------------------------------------------------
// Returns true if L is empty, otherwise returns false.
bool isEmpty(List L) {
  if (L == NULL) handleNullList("calling isEmpty()");
  return (L->length == 0);
}

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printListToStdout(List L) {
  if (L == NULL) handleNullList("calling printListToStdout()");
  if (isEmpty(L)) handleEmptyList("calling printListToStdout()");
  // if (L->cursor != NULL && L->index != -1) {
  //   printf("the cursor (%d) is at index: %d\n", get(L), index(L));
  // } else {
  //   printf("the cursor is undefined:\n");
  // }
  Node N = NULL;
  for (N = L->front; N != NULL; N = N->next) {
    printf(FORMAT " ", N->data);
  }
  printf("%c", '\n');
}
