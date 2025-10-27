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

    // extended_test_in_order();
    // extended_test_usecase();
    extended_trim();
    // extended_remove();
}
