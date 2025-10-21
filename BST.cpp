#include <list>
#include "BST.h"
#include <sstream>
#include <iostream>
#include <cassert>

//=================================================
// BST()
// Constructor for the bst.
//
// RETURN VALUE:
//  an empty tree.
//=================================================
template <typename D, typename K>
BST<D, K>::BST(void) {
    root = nullptr;
}

//=================================================
// delete_BST(Node<D, K>* left, Node<D, K>* right)
// Description: ?
//
// PARAMETERS: ?
//  
//
// RETURN VALUE: ?
//  
//=================================================
template <typename D, typename K> 
static void delete_BST(Node<D, K>* left, Node<D, K>* right) {
    if (left != nullptr) {
        auto l = left->left;
        auto r = left->right;
        delete left;
        delete_BST(l, r);
    }

    if (right != nullptr) {
        auto l = right->left;
        auto r = right->right;
        delete right;
        delete_BST(l, r);
    }
}

//=================================================
// ~BST()
// Destructor for the bst.
//=================================================
template <typename D, typename K>
BST<D, K>::~BST(void) {
    if (root == nullptr) {
        return;
    }

    auto left = root->left;
    auto right = root->right;
    delete root;
    delete_BST(left, right);
}

//=================================================
// empty()
// Indicate whether the binary search tree
// bst is empty.
//
// RETURN VALUE:
//  true or false
//=================================================
template <typename D, typename K> 
bool BST<D, K>::empty() {
    return root == nullptr;
}

//=================================================
// insert(D d, K k)
// should insert a data d and key k into
// the binary search tree bst.
//
// PARAMETERS:
//  D data, K key
//
//=================================================
template <typename D, typename K> 
void BST<D, K>::insert(D d, K k) {
    // From page 321 of textbook
    Node<D, K>* z = new Node<D, K> {
        .left = nullptr,
        .right = nullptr,
        .parent = nullptr,
        .data = d,
        .key = k
    };

    Node<D, K>* x = root;
    Node<D, K>* y = nullptr;

    while (x != nullptr) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;

    if (y == nullptr) {
        root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
}

//=================================================
// iterative_tree_search
// Iteratively searches for a node with key k starting at node x. From page 316
// of the book. Used in the "get" method where x is the root node in the initial
// call.
//
// PARAMETERS:
//  x: The node to start at
//  k: The key to search for
//
// RETURN VALUE:
//  A pointer to the found node or null.
//=================================================
template <typename D, typename K> 
Node<D, K>* iterative_tree_search(Node<D, K>* x, K k) {
    while (x != nullptr && k != x->key) {
        if (k < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

//=================================================
// get(K k)
// return the data associated with key k
// in the bst.
//
// PARAMETERS:
//  K key
//
// RETURN VALUE:
//  D data associated with key.
//=================================================
template <typename D, typename K> 
D BST<D, K>::get(K k) {
    auto found = iterative_tree_search(root, k);
    if (found == nullptr) {
        if constexpr (is_same_v<D, string>) {
            return "";
        } else if constexpr (is_same_v<D, bool>) {
            return false;
        } else if constexpr (is_arithmetic_v<D>) {
            return 0;
        } else {
          throw runtime_error(
              "Tried to get a key for a Data type that doesn't have a default "
              "value (valid types: bool, arithmetic, and string)");
        }
    } else {
        return found->data;
    }
}

//=================================================
// transplant
// Replaces one subtree as a child of its parent with another subtree.
//
// PARAMETERS:
//  u: A non-nil ptr to a subtree
//  v: Possibly nil ptr to a subtree
//=================================================
template <typename D, typename K> 
void BST<D, K>::transplant(Node<D, K>* u, Node<D, K>* v) {
    assert(u != nullptr);
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    if (v != nullptr) {
        v->parent = u->parent;
    }
}

//=================================================
// remove(K k)
// removes the first (closest to the root) node with key k in the bst. Algorithm
// from page 325 of the book.
//
// PARAMETERS:
//  K key
//=================================================
template <typename D, typename K> 
void BST<D, K>::remove(K k) {
    auto z = iterative_tree_search(root, k);
    assert(z != nullptr);

    if (z->left == nullptr) {
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        transplant(z, z->left);
    } else {
        auto y = min(z->right);
        if (y != z->right) {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}

//=================================================
// max_data()
// return the data associate with the
// largest key in bst.
//
// RETURN VALUE:
//  D data associate with the largest K key.
//=================================================
template <typename D, typename K> 
D BST<D, K>::max_data() {
    assert(root != nullptr);
    while (root -> right != nullptr) {
        root = root -> right;
    }
    
    return root -> data;
}

//=================================================
// max_key()
// return the largest key in bst.
//
// RETURN VALUE:
//  Largest K key in the bst.
//=================================================
template <typename D, typename K> 
K BST<D, K>::max_key() {
    assert(root != nullptr);

    while (root -> right != nullptr) {
        root = root -> right;
    }
    
    return root -> key;
}

//=================================================
// min
// Returns the minimum node in the tree. From page 318 in the book.
//
// RETURN VALUE:
//  The minimum node in the tree, or nil x is nil.
//=================================================
template <typename D, typename K>
Node<D, K>* BST<D, K>::min(Node<D, K>* x) {
    if (x == nullptr) {
        return nullptr;
    }

    while (x -> left != nullptr) {
        x = x -> left;
    }

    return x;
}


//=================================================
// min_data()
// return the data associated with the
// smallest key in the bst.
//
// RETURN VALUE:
//  D data associate with the smallest K key.
//=================================================
template <typename D, typename K> 
D BST<D, K>::min_data() {
    // DANGER: does not check if root == nullptr
    return min(root)->data;
}

//=================================================
// min_key()
// return the smallest key in the bst.
//
// RETURN VALUE:
//  Smallest K key in the bst.
//=================================================
template <typename D, typename K> 
K BST<D, K>::min_key() {
    while (root -> left != nullptr) {
        root = root -> left;
    }
    
    return root -> key;
}

//=================================================
// successor(K k)
// return the right key after the indicated key.
//
// PARAMETERS:
//  K key
//
// RETURN VALUE:
//  The K key after the indicated K key, or 0 if
// the tree is empty.
//=================================================
template <typename D, typename K> 
K BST<D, K>::successor(K k) {
    while ((root != nullptr) && (k != root -> key)) {
        if (k < root -> key) {
            root = root -> left;
        } else {
            root = root -> right;
        }
    }
    
    if (root -> right == nullptr) {
        return 0;
    }
    
    else {
        root = root -> right;
    }
    
    return root -> key;
}

//=================================================
// to_string
// returns a string with the keys in the BST separated by a single space and
// ordered from top (root) to bottom (leaves) and left to right. For example:
// `9 49 58 78`
//
// RETURN VALUE:
//  A string of keys.
//=================================================
template <typename D, typename K> 
string BST<D, K>::to_string() {
    if (root == nullptr) {
        return "";
    }

    stringstream s;
    s << root->key << " ";

    list<Node<D, K>*> current_layer;
    current_layer.push_back(root);

    while (!current_layer.empty()) {
        list<Node<D, K>*> next_layer;

        for (auto node : current_layer) {
            auto left = node->left;
            auto right = node->right;

            if (node->left != nullptr) {
                s << node->left->key << " ";
                next_layer.push_back(left);
            }

            if (right != nullptr) {
                s << node->right->key << " ";
                next_layer.push_back(right);
            }
        }

        current_layer = next_layer;
    }

    string str = s.str();
    str = str.substr(0, str.size() - 1); // Remove trailing space
    return str;
}

template <typename D, typename K> 
string BST<D, K>::in_order(Node<D, K>* x) {
    stringstream s;

    if (x != nullptr) {
        sortAlg(x -> left)
    
        s << x -> key << " ";
    
        sortAlg(x -> right)
    }
    
    string str = s.str();
    str = str.substr(0, str.size() - 1); // Remove trailing space
    return str;
}
//=================================================
// in_order()
// same as to_string, but keys in
// ascending order.
//
// RETURN VALUE:
//  A string of keys in ascending order.
//=================================================
template <typename D, typename K> 
string BST<D, K>::in_order() {
    if (root == nullptr) {
        return "";
    }
    
    return in_order(root);
}

//=================================================
// trim(K low, K high)
// should trim the binary search
// tree bst so that the keys of every node lie in
// the interval [low, high].
//
// PARAMETERS:
//  K low, K high
//=================================================
template <typename D, typename K> 
void BST<D, K>::trim(K low, K high) {}
