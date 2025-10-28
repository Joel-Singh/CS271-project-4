# CS271 Binary Search Tree Implementation
Binary Search Tree implementation for CS271, data structures,
at Denison University by Khai Le and Joel Singh.

## Caveats

- The binary search tree can only handle data types of `string`,
`bool`, `arithmetic`, `char`, and classes with a default
constructor as they are the only ones programmed with default
values for functions that return data in cases where a node can't
be found.

## Compiling

To compile: `make && ./main`.

To run the usecase main instead of the tests, uncomment the following line from `./main.cpp`:
```cpp
// #define ENABLE_USECASE_MAIN
```
