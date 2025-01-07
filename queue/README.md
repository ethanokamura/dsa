
A queue is a data structure that works fairly intuitively. You have a list of things where the first item in the list is the first to be removed.

Think of a line of people waiting to order food. The first person to enter the line will be the first one to recieve their food and leave.

This type of system is known as "FIFO" or "first in first out".

With queues, you can only access the data from the front or the back of the queue, but not both. You can either add to the queue or remove/delete the value that was first added.

For example, let's look at the list: `[ 1, 2, 3, 4 ]`

```
start:   [ 1, 2, 3, 4 ]
push(5): [ 1, 2, 3, 4, 5 ]
pop():   [ 2, 3, 4, 5 ]
```

When we implement queues, we use an internal data structure. For our queue, we will use a Linked List with something called inheritance. It is another method of "reusing code".

It is important to check to make sure that when we manipulate the queue, we are always within bounds and are not trying to access memory that does not exist. For me, I took care of the memory issues and bounds checking within my `LinkedList` class, however, this can be done in the queue itself.