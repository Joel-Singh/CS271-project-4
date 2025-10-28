main: BST.cpp BST.h usecase.cpp main.cpp
	g++ -o main main.cpp

main_debug: BST.cpp BST.h usecase.cpp main.cpp
	g++ -g -O0 -o main_debug main.cpp

main_sanitized: BST.cpp BST.h usecase.cpp main.cpp
	g++ -g -fsanitize=address -o main_sanitized main.cpp
