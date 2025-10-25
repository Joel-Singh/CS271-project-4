test_bst_example: BST.cpp BST.h usecase.cpp
	g++ -o test_bst_example test_bst_example.cpp

test_bst_example_debug: BST.cpp BST.h usecase.cpp
	g++ -g -O0 -o test_bst_example_debug test_bst_example.cpp

test_bst_sanitized: BST.cpp BST.h usecase.cpp
	g++ -fsanitize=address -o test_bst_sanitized test_bst_example.cpp
