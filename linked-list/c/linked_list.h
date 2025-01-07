#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Define the Node structure
typedef struct Node {
  int data;
  struct Node *next;
} Node;

// Define the LinkedList structure
typedef struct LinkedList {
  Node *head;
  Node *tail;
  size_t size;
} LinkedList;

// Function prototypes
LinkedList *create_list();
void destroy_list(LinkedList *list);
bool is_empty(LinkedList *list);
size_t list_size(LinkedList *list);
void push_front(LinkedList *list, int value);
void push_back(LinkedList *list, int value);
int pop_front(LinkedList *list);
int pop_back(LinkedList *list);
void clear(LinkedList *list);
bool contains(LinkedList *list, int value);
void remove_value(LinkedList *list, int value);
void reverse(LinkedList *list);

// Function definitions

// Create a new linked list
LinkedList *create_list() {
  LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

// Destroy the linked list
void destroy_list(LinkedList *list) {
  clear(list);
  free(list);
}

// Check if the list is empty
bool is_empty(LinkedList *list) { return list->size == 0; }

// Get the size of the list
size_t list_size(LinkedList *list) { return list->size; }

// Add an element to the front of the list
void push_front(LinkedList *list, int value) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = value;
  new_node->next = list->head;
  list->head = new_node;
  if (list->tail == NULL) {
    list->tail = new_node;
  }
  list->size++;
}

// Add an element to the back of the list
void push_back(LinkedList *list, int value) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = value;
  new_node->next = NULL;
  if (list->tail) {
    list->tail->next = new_node;
  } else {
    list->head = new_node;
  }
  list->tail = new_node;
  list->size++;
}

// Remove and return the first element
int pop_front(LinkedList *list) {
  if (is_empty(list)) {
    fprintf(stderr, "Error: List is empty!\n");
    exit(EXIT_FAILURE);
  }
  Node *temp = list->head;
  int value = temp->data;
  list->head = list->head->next;
  if (!list->head) {
    list->tail = NULL;
  }
  free(temp);
  list->size--;
  return value;
}

// Remove and return the last element
int pop_back(LinkedList *list) {
  if (is_empty(list)) {
    fprintf(stderr, "Error: List is empty!\n");
    exit(EXIT_FAILURE);
  }
  if (list->head == list->tail) {
    int value = list->head->data;
    free(list->head);
    list->head = list->tail = NULL;
    list->size--;
    return value;
  }
  Node *current = list->head;
  while (current->next != list->tail) {
    current = current->next;
  }
  int value = list->tail->data;
  free(list->tail);
  list->tail = current;
  list->tail->next = NULL;
  list->size--;
  return value;
}

// Clear the list
void clear(LinkedList *list) {
  while (!is_empty(list)) {
    pop_front(list);
  }
}

// Check if the list contains a value
bool contains(LinkedList *list, int value) {
  Node *current = list->head;
  while (current) {
    if (current->data == value) {
      return true;
    }
    current = current->next;
  }
  return false;
}

// Remove the first occurrence of a value
void remove_value(LinkedList *list, int value) {
  if (is_empty(list))
    return;
  if (list->head->data == value) {
    pop_front(list);
    return;
  }
  Node *current = list->head;
  while (current->next && current->next->data != value) {
    current = current->next;
  }
  if (current->next) {
    Node *temp = current->next;
    current->next = current->next->next;
    if (temp == list->tail) {
      list->tail = current;
    }
    free(temp);
    list->size--;
  }
}

// Reverse the list
void reverse(LinkedList *list) {
  Node *prev = NULL;
  Node *current = list->head;
  Node *next = NULL;
  list->tail = list->head;
  while (current) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  list->head = prev;
}

#endif // LINKED_LIST_H
