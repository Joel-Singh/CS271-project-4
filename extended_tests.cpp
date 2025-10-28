#include "BST.h"
#include "test.cpp"
#include <iostream>
#include "usecase.cpp"

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

    test("Get on empty bst returns default value", bst_string.get(non_existent_key), "");

    test("Get on empty bst returns default value", bst_char.get(non_existent_key) == '\0', "true");

    test("Get on empty bst returns default value", bst_bool.get(non_existent_key), "false");

    test("Get on empty bst returns default value", bst_arithmetic.get(non_existent_key), "0");

    test("Get on empty bst returns default value", bst_class.get(0), "");

}

void extended_test_remove() {
    BST<bool, long> bst;

    bst.remove(0);
    test("Removing from empty bst does nothing", bst, "");

    bst.insert(false, 42);
    bst.remove(42);
    test("Removing by key", bst, "");

    bst.insert(false, 50);
    bst.insert(false, 25);
    bst.insert(false, 75);

    bst.remove(50);
    test("Removing the head of a tree", bst, "25 75");

    bst.insert(false, 50);
    bst.insert(false, 25);
    bst.insert(false, 75);
    bst.insert(false, 90);

    bst.remove(75);
    test("Removing in the middle of a tree", bst, "50 25 90");
}

void extended_max_data() {
    BST<char, long int> bst;
    test("max_data returns default value on empty bst", bst.max_data(), "");

    bst.insert('d', 5);
    bst.insert('i', 10);
    bst.insert('z', 20);
    bst.insert('a', 100);

    test("max_data returns the data of highest key", bst.max_data(), "a");
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

}

void extended_test_usecase() {
    BST<string, string>* bst = create_bst<string, string>("binhex.txt");
    delete bst;
}

void extended_remove() {
    try
    {
        int vals[10] = {5, 2, 7, 1, 3, 4, 6, 9, 8, 10};
        BST<string, int> balanced_bst;
        for (int i = 0; i < 10; i++)
        {
            balanced_bst.insert("some data", vals[i]);
        }
        balanced_bst.remove(7);
        // string bst_str = balanced_bst.to_string();
        // if (bst_str != "5 2 8 1 3 6 9 4 10")
        // {
        //     cout << "Incorrect result of removing 7. Expected 5 2 8 1 3 6 9 4 10 but got : " << bst_str << endl;
        // }
    }
    catch (exception &e)
    {
        cerr << "Error in removing node from bst : " << e.what() << endl;
    }
}

void extended_trim() {
    try
    {
        // {
        //     BST<string, int> bst;
        //     bst.insert("data", 1);
        //     bst.insert("data", 0);
        //     bst.insert("data", 2);
        //     bst.trim(1, 2);
        // }

        {
            BST<string, int> bst;
            bst.insert("data", 3);
            bst.insert("data", 0);
            bst.insert("data", 4);
            bst.trim(1, 3);

        }
    }
    catch (exception &e)
    {
        cerr << "Error in trimming the bst : " << e.what() << endl;
    }

    // try
    // {
    //     BST<string, int> bst;
    //     int vals[3] = {1, 0, 2};
    //     for (int i = 0; i < 3; i++)
    //     {
    //         bst.insert(to_string(vals[i]) + " data", vals[i]);
    //     }
    //     bst.trim(1, 2);
    //     string bst_str = bst.to_string();
    //     if (bst_str != "1 2")
    //     {
    //         cout << "Incorrect tree after trimming 1 0 2 with low=1, high=2. Expected 1 2 but got : " << bst_str << endl;
    //     }
    //     BST<string, int> bst2;
    //     int vals2[5] = {3, 0, 4, 2, 1};
    //     for (int i = 0; i < 5; i++)
    //     {
    //         bst2.insert(to_string(vals2[i]) + " data", vals2[i]);
    //     }
    //     bst2.trim(1, 3);
    //     bst_str = bst2.to_string();
    //     if (bst_str != "3 2 1")
    //     {
    //         cout << "Incorrect tree after trimming 3 0 4 2 1 with low=1, high=3. Expected 3 2 1 but got : " << bst_str << endl;
    //     }
    // }
    // catch (exception &e)
    // {
    //     cerr << "Error in trimming the bst : " << e.what() << endl;
    // }

}

void extended_tests() {
    cout << "Running extended tests (i.e not the default)" << endl;

    extended_test_in_order();
    extended_test_usecase();
    extended_trim();
    extended_remove();
    extended_test_empty();
    extended_test_insert();
    extended_test_get();
}
