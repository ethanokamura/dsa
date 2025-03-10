
A stack is a data structure that works fairly intuitively. You have a stack of data that you can pull from.

Like a stack of pancakes, the first one on the plate is the last one to be eaten.

This type of system is known as "LIFO" or "last in first out".

With stacks, you can only access the data on the top or bottom of the stack, but not both. You can either add to the stack or remove/delete the value that was most recently added.

For example, let's look at the list: `[ 1, 2, 3, 4 ]`

```
start:   [ 1, 2, 3, 4 ]
push(0): [ 0, 1, 2, 3, 4 ]
pop(3):  [ 3, 4 ]
```

When we implement stacks, we use an internal data structure. For our stack, we will use a Linked List with something called composition. It is a method of "reusing code".

It is important to check to make sure that when we manipulate the stack, we are always within bounds and are not trying to access memory that does not exist. For me, I took care of the memory issues and bounds checking within my `LinkedList` class, however, this can be done in the Stack itself.