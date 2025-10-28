# CS271 Binary Search Tree Implementation
Binary Search Tree implementation for CS271, data structures,
at Denison University by Khai Le and Joel Singh.

## Caveats

- The binary search tree can only handle data types of
`string`, `bool`, and `arithmetic` as they are the only ones
programmed with default values for `get` if the requested key,
`k`, is not in the tree.

- Returns default value for the data functions min_data, max_data, and get

## Compiling

To compile: `make && ./main`.

To run the usecase main instead of the tests, uncomment the following line from `./main.cpp`:
```cpp
// #define ENABLE_USECASE_MAIN
```

# neat things
We nested a bst in a bst to test the default class constructor.


