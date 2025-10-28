#include "BST.h"
#include "test.cpp"
#include "usecase.cpp"
#include <iostream>

using namespace std;

void extended_test_empty() {
  {
    BST<string, int> bst;

    test("default bst is empty", bst.empty(), "true");

    bst.insert("data", 0);

    test("inserting into bst makes it not empty", bst.empty(), "false");

    bst.remove(0);

    test("removing from bst makes it empty", bst.empty(), "true");
  }

  {
    BST<char, short> bst;

    test("empty with char and short", bst.empty(), "true");

    bst.insert('a', 0);

    test("empty with char and short", bst.empty(), "false");

    bst.remove(0);

    test("empty with char and short", bst.empty(), "true");
  }
}

void extended_test_insert() {
  {
    BST<string, long> bst;
    bst.insert("data", 1);
    bst.insert("data", 5);
    bst.insert("data", -3);

    test("inserting with long as key", bst.to_string(), "1 -3 5");
  }

  {
    BST<bool, int> bst;
    bst.insert(false, 1);
    bst.insert(true, 5);
    bst.insert(false, -3);

    test("inserting with bool as data", bst.to_string(), "1 -3 5");
    test("inserting with bool as data", bst.get(1), "false");
    test("inserting with bool as data", bst.get(5), "true");
    test("inserting with bool as data", bst.get(-3), "false");
  }
}

void extended_test_get() {
  BST<string, int> bst_string;
  BST<char, int> bst_char;
  BST<bool, int> bst_bool;
  BST<long, int> bst_arithmetic;
  BST<BST<string, int>, int> bst_class;

  int non_existent_key = 0;

  test("Get on empty bst returns default value",
       bst_string.get(non_existent_key), "");

  test("Get on empty bst returns default value",
       bst_char.get(non_existent_key) == '\0', "true");

  test("Get on empty bst returns default value", bst_bool.get(non_existent_key),
       "false");

  test("Get on empty bst returns default value",
       bst_arithmetic.get(non_existent_key), "0");

  test("Get on empty bst returns default value", bst_class.get(0), "");
}

void extended_test_remove() {
  {
    BST<bool, long> bst;

    bst.remove(0);
    test("Removing from empty bst does nothing", bst, "");
  }

  {
    BST<bool, long> bst;

    bst.insert(false, 42);
    bst.remove(42);
    test("Removing by key", bst, "");
  }

  {
    BST<bool, long> bst;

    bst.insert(false, 50);
    bst.insert(false, 25);
    bst.insert(false, 75);

    bst.remove(50);
    test("Removing the head of a tree", bst, "75 25");
  }

  {
    BST<bool, long> bst;

    bst.insert(false, 50);
    bst.insert(false, 25);
    bst.insert(false, 75);
    bst.insert(false, 90);

    bst.remove(75);
    test("Removing in the middle of a tree", bst, "50 25 90");
  }
}

void extended_test_max_data() {
  BST<char, long int> bst;
  test("max_data returns default value on empty bst", bst.max_data(), "");

  bst.insert('d', 5);
  bst.insert('i', 10);
  bst.insert('z', 20);
  bst.insert('a', 100);

  test("max_data returns the data of highest key", bst.max_data(), "a");
}

void extended_test_max_key() {
  BST<int, int> bst;

  test("Returns default value of 0 on max_key", bst.max_key(), "0");

  bst.insert(30, 80);
  bst.insert(50, 100);
  bst.insert(20, 500);

  test("max_key returns max key", bst.max_key(), "500");
}

void extended_test_min_data() {
  BST<char, long int> bst;
  test("min_data returns default value on empty bst", bst.min_data(), "");

  bst.insert('d', 5);
  bst.insert('i', 10);
  bst.insert('z', 20);
  bst.insert('a', 100);

  test("min_data returns the data of lowest key", bst.min_data(), "d");
}

void extended_test_min_key() {
  BST<int, int> bst;

  test("Returns default value of 0 on min_key", bst.min_key(), "0");

  bst.insert(30, 80);
  bst.insert(50, 100);
  bst.insert(20, 500);

  test("min_key returns min key", bst.min_key(), "80");
}

void extended_test_successor() {
  BST<char, int> bst;

  test("Returns default value if passed in key does not exist",
       bst.successor(0), "0");

  bst.insert('a', 5);
  bst.insert('b', 8);
  bst.insert('c', 10);
  bst.insert('d', 3);
  bst.insert('e', 1);
  bst.insert('f', 2);

  test("successor returns 0 on no successor", bst.successor(10), "0");
  test("successor returns the right successor", bst.successor(5), "8");
  test("successor returns the right successor", bst.successor(3), "5");
}

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

  {
    BST<string, short> bst;

    bst.insert("data", 8);
    bst.insert("data", 10);
    bst.insert("data", 3);
    bst.insert("data", 100);
    bst.insert("data", -4);
    bst.insert("data", -8);
    bst.insert("data", 22);

    test("in order returns the right order", bst.in_order(),
         "-8 -4 3 8 10 22 100");
  }
}

void extended_test_trim() {
  BST<bool, int> bst;

  bst.trim(0, 0);
  test("Trimming empty tree does nothing", bst, "");

  bst.insert(false, 39);
  bst.insert(false, 42);
  bst.insert(false, 10);
  bst.insert(false, 32);
  bst.insert(false, 26);
  bst.insert(false, 0);
  bst.insert(false, 23);

  bst.trim(30, 50);

  test("Trim trims tree correctly", bst, "39 32 42");
}

void extended_test_usecase() {
  BST<string, string> *bst = create_bst<string, string>("binhex.txt");
  delete bst;
}

void extended_tests() {
  cout << "Running extended tests (i.e not the default)" << endl;

  extended_test_empty();
  extended_test_insert();
  extended_test_get();
  extended_test_remove();
  extended_test_max_data();
  extended_test_max_key();
  extended_test_min_data();
  extended_test_min_key();
  extended_test_successor();
  extended_test_in_order();
  extended_test_trim();
  extended_test_usecase();
}
