#include "BST.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdexcept>

#ifndef USECASE_CPP
#define USECASE_CPP

//=================================================
// create_bst
// Creates a bst from pairs of key and data separated with commas and newlines
// located in file `fname`. create_bst assumes `fname` is a valid file and that
// D and K are strings.
//
// Example of valid file:
// 8,1000
// 4,0100
// C,1100
// ...
//
// PARAMETERS:
//  fname: Name of the file
//
// RETURN VALUE:
//  BST created from the elements in `fname`
//=================================================
template <typename D, typename K>
BST<D,K>* create_bst(string fname) {
    // Reading a file example from https://en.cppreference.com/w/cpp/io/basic_fstream.html
    std::fstream file(fname);
 
    BST<D, K>* bst = new BST<D, K>();
    if (!file.is_open())
        throw new runtime_error("Unable to open `" + fname + "`");
    else
    {
        // Used the getline example from:
        // https://en.cppreference.com/w/cpp/string/basic_string/getline
        for (string line; getline(file, line);) {
            K key;
            D data;

            int delimiter_index = 0;
            // No if guard, can assume there is a comma in every line
            for (int i = 0;; i++) {
                assert(i < line.size());
                if (line[i] == ',') {
                    delimiter_index = i;
                    break;
                }
            }

            data = line.substr(0, delimiter_index);
            key = line.substr(delimiter_index+1);

            bst->insert(data, key);
        }
    }

    return bst;
}

//=================================================
// convert
// converts a binary string to a hex string using `bst`.
// PARAMETERS:
//  bst: Assumes there is a pair of four bit binary strings as
//       keys and hex digits as data for every hex digit.
//  bin: The binary string to convert.
//
// RETURN VALUE:
//  A hex string representation of `bin`.
//=================================================
template <typename D, typename K>
string convert(BST<D, K>* bst, string bin) {
    int bin_size_four_remainder = bin.size() % 4;

    // Pad the binary string
    if (bin_size_four_remainder != 0) {
        if (bin_size_four_remainder == 1) {
            bin = "000" + bin;
        } else if (bin_size_four_remainder == 2) {
            bin = "00" + bin;
        } else if (bin_size_four_remainder == 3) {
            bin = "0" + bin;
        }
    }

    string hex;
    int hex_digit_count = bin.size() / 4;
    for (int i = 0; i < hex_digit_count; i++) {
        hex += bst->get(bin.substr(i * 4, 4));
    }

    return hex;
}

#if 0

int main() {
    string binary_str;

    cout << "Enter binary representation for conversion: ";
    cin >> binary_str;

    int str_size = binary_str.size();
    for (int i = 0; i < str_size; i++) {
        if (binary_str[i] != '0' && binary_str[i] != '1') {
            throw runtime_error("`" + binary_str.substr(i, 1) + "`" + " is not a valid binary digit");
        }
    }
    BST<string, string> *hex_bst = create_bst<string, string>("binhex.txt");

    cout << "Hexadecimal representation of " << binary_str << " is " << convert<string, string>(hex_bst, binary_str) << endl;

    delete hex_bst;
}

#endif

#endif
