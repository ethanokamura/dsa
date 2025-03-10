# Lists
This directory covers everything you might need for linked lists and list-like structures.

## List:
Elements probably not laid out sequentially in memory
Access a subscript/index via traversing nodes (which is slow)
Implemented as a "linked list"

## Linked List
Internally has "nodes".

Using this example:
```cpp
char* data = "hello"
```

(Where `data[0] == h` and `data[4] == o`)

In this case, we have a char and two pointers in each node:
1. `char data` would be `'h'`
2. `Node *next` would be a pointer to the next node (`'e'`)

## Doubly Linked List
Each list element (ie node) contains a pointer to the next node in the list. Along with the data each node holds.

Here's a basic visual for a linked list! (Where `O`'s are nodes)

```
<-O<->O<->O<->O->
```

Class `LinkedList` is an archetypal doubly linked list. Where `Node` structures and internal list details are kept private. Also, note that all member functions are defined inside the class declaration. (No separate .h and .cpp/.cc files.) Template classes are usually defined this way. For this class, the param `T` is the type of the list elements. You can think of it as a dynamic or generic way to hold data!

## Starter Code
For this course, we will be building off of this code! If you would like to follow along with the code, I recommend copying this template class.
```cpp
template<typename T>
class LinkedList {
  // A forward declaration for a nested type named "Node"
  // We can refer to the Node type in the body of public member functions even though it hasn't been fully defined yet
  struct Node;
 public:
  // Constructors
  // Destructors
  // other public member functions
 private:
  struct Node {
    T data;
    Node* next = nullptr;
    Node* prev = nullptr;
    // default constructor!
    Node(T value) : data(value), next(nullptr), prev(nullptr) {}
  };
  Node* head = nullptr;
  Node* tail = nullptr;
  std::size_t list_size = 0;
};
```

A list type should almost always be a template type

An example of this is with **vectors**. `std::vector` is actually `std::vector<T>`
(ie T is the element type)

## Disadvantages:
### 1. No direct access (unlike an array)
Address of value at index 5 in an array: (ie a single integer addition).
```cpp
array_variable + 5
```

Address of node representing index 5 in a linked list: (ie multiple pointer dereferences)
```cpp
list_variable.head_->next->next->next->next->next
```

### 2. Overhead
Occupies more space than an array (overhead). An array of chars of size 3 holds 3 bytes. A doubly linked list of chars, size 3 holds up to 67 bytes (8 pointers, 3 chars) (more likely 88 bytes - memory alignment on 8-byte boundaries faster for CPU)

### 3. No Spacial Locality
(nodes likely not next to each other in memory) It may be difficult for the CPU cache to optimize.

## Advantages:
### 1. Linked Lists Are Dynamic
Linked lists allow for efficient memory allocation as nodes can be dynamically allocated and deallocated, enabling flexible memory management compared to arrays, which have a fixed size. Linked lists can be constructed on the fly, accommodating elements as needed, making them suitable for situations where the size of the data is unknown in advance.

Linked lists can grow or shrink dynamically during runtime, allowing for efficient insertion and deletion of elements anywhere in the list without requiring resizing or shifting of elements, as is the case with arrays.

### 2. Efficiency:
Insertion and deletion operations at the beginning or end of a linked list (when you have direct access to the head or tail) can be performed in constant time O(1), regardless of the list size. This makes linked lists efficient for dynamic data structures. More on time complexity [here](https://perfectline.io/courses/cpp/dsa/complexity/).

Insertions and deletions in the middle of a linked list can also be efficient if you have direct access to the node where the operation is performed. Unlike arrays, linked lists don't require shifting elements, resulting in faster operations.

Linked lists consume memory only for the actual data and the pointers connecting the nodes, making them memory-efficient compared to arrays, which may have unused space due to fixed-size allocation.

### 3. Versatility
Linked lists come in different forms, such as singly linked lists, doubly linked lists, and circular linked lists. Each variant offers unique advantages, allowing developers to choose the type that best fits their requirements.

### 4. Ease of Implementation
Linked lists are relatively easy to implement and understand compared to more complex data structures like trees and graphs. This simplicity makes them an excellent choice for learning data structures and algorithms.

