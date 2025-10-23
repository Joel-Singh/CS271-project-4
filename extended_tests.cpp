#include "BST.h"
#include "test.cpp"
#include <iostream>
#include "usecase.cpp"

using namespace std;

void extended_test_in_order() {
    {
        BST<string, int> bst;
        test("in_order on empty bst", bst.in_order(), "");
    }

    {
        BST<string, int> bst;
        bst.insert("", 1);
        test("in_order on bst of input size 1", bst.in_order(), "1");
    }

    {
        BST<string, int> bst;
        bst.insert("", 1);
        bst.insert("", 2);
        test("in_order on bst of input size 2", bst.in_order(), "1 2");
    }

    {
        BST<string, int> bst;
        bst.insert("", 5);
        bst.insert("", 2);
        test("in_order on bst with many values", bst.in_order(), "2 5");
    }

}

void extended_test_usecase() {
    BST<string, string>* bst = create_bst<string, string>("binhex.txt");
}

void extended_tests() {
    cout << "Running extended tests (i.e not the default)" << endl;

    extended_test_in_order();
    extended_test_usecase();
}
