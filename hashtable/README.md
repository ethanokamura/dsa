## What is a HashTable:

According to GeeksForGeeks: 

"A Hash table is defined as a data structure used to insert, look up, and remove key-value pairs quickly. It operates on the hashing concept, where each key is translated by a hash function into a distinct index in an array. The index functions as a storage location for the matching value. In simple words, it maps the keys with the value."

## Time Complexity:
Expected:   O(1)
Worst Case: O(n)

## Example Structure:
```
0
1 -> 4352: "value1" -> 4533: "value4"
2 -> 6575: "value3" -> 1325: "value5"
3 -> 9534: "value2"
```

## Collision Resolution:
1. **Chaining**: Make an array of lists (should be short and spread out)
2. **Open Addressing**: Pick another spot if one is taken (using double hashing, linear probing, or quadratic probing)

## Our HashTable:
1. Our hashtable will not check for duplicates
2. We will be hashing with multiplication (double hashing)
3. We will be using a 2D Linked List (or a Linked List of Linked Lists)

Our double hashing function:
```
h'(k,i) = h(k) + i * h2(k) % m
```
Where `m` prevents primary and secondary clustering.

## Example Data:
```
245323545 hello
024504523 W
023434234 def
000049456 asdfasdf
345234564 asdf
123456789 abc
000200042 L
509348548 goodbye
342145435 testing
435567467 wassp
```