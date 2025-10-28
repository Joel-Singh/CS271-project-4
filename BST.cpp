#include <list>
#include "BST.h"
#include <sstream>
#include <iostream>
#include <cassert>
#include <queue>

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
// Cleans up the memory of the given leeft and right nodes.
//
// PARAMETERS: 
//   left: A possibly nil left node
//   right: A possibly nil right node
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

template <typename D> 
D default_data_value() {
    if constexpr (is_same_v<D, string>) {
        return "";
    }
    else if constexpr(is_same_v<D, char>) {
        return '\0';
    } else if constexpr (is_same_v<D, bool>) {
        return false;
    } else if constexpr (is_arithmetic_v<D>) {
        return 0;
    } else {
        return D();
    }
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
        return default_data_value<D>();
    } else {
        return found->data;
    }
}

//=================================================
// transplant
// Replaces one subtree as a child of its parent with another subtree.
// WARNING: transplant does _not_ clean up memory nor does it maintain the BST
// property. It is the onus of the caller.
//
// PARAMETERS:
//  u: A non-nil ptr to a subtree
//  v: Possibly nil ptr to a subtree
//=================================================
template <typename D, typename K> 
void BST<D, K>::transplant(Node<D, K>* u, Node<D, K>* v) {
    assert(u != nullptr);
    if (u == root) {
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
// remove(Node<D, K> z)
// Remove `z` from the BST and returns the node it was replaced with. Assumes
// node is not nullptr. Algorithm from page 325 of the book.
//
// PARAMETERS:
//  node: The node to remove
//
// RETURN:
//   The node `z` was replace with or nil
//=================================================
template <typename D, typename K> 
Node<D, K>* BST<D, K>::remove_node(Node<D, K>* z) {
    assert(z != nullptr);

    Node<D, K>* replacement = nullptr;
    if (z->left == nullptr) {
        transplant(z, z->right);

        replacement = z->right;
    } else if (z->right == nullptr) {
        transplant(z, z->left);

        replacement = z->left;
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

        replacement = y;
    }

    delete z;
    return replacement;
}

//=================================================
// remove(K k)
// removes the first (closest to the root) node with key k in the bst.
// 
// PARAMETERS:
//  K key
//=================================================
template <typename D, typename K> 
void BST<D, K>::remove(K k) {
    auto z = iterative_tree_search(root, k);
    if (z == nullptr) {
        return;
    }
    remove_node(z);
}

//=================================================
// max
// Returns the max node of the subtree rooted at x or nil if x == nil.
// Implementation from page 318 of the book.
//
// PARAMETERS:
//  x: Possibly nil pointer to Node
//
// RETURN VALUE:
//  The a reference to max or nil if x == nullptr
//=================================================
template <typename D, typename K> 
Node<D, K>* max(Node<D, K>* x) {
    while (x->right != nullptr) {
        x = x->right;
    }

    return x;
}

//=================================================
// max_data()
// return the data associated with the
// largest key in bst.
//
// RETURN VALUE:
//  D data associate with the largest K key.
//=================================================
template <typename D, typename K> 
D BST<D, K>::max_data() {
    if (empty()) {
        return default_data_value<D>();
    }
    return max(root)->data;
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
    if (empty()) {
        std::cout << "Warning: default key of 0 returned for max_key call on empty bst" << std::endl;
        return 0;
    }

    return max(root)->key;
}

//=================================================
// min
// Returns the minimum node in the tree or nil if x is nil. From page 318 in the book.
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
    if (empty()) {
        return default_data_value<D>();
    }

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
    if (empty()) {
        std::cout << "Warning: default key of 0 returned for min_key call on empty bst" << std::endl;
        return 0;
    }

    return min(root)->key;
}

//=================================================
// successor(K k)
// Returns the key of the successor in the binary search tree bst for key k
// (i.e., the smallest key in bst that is larger than k). If no such successor
// exists, return 0. Implemented from page 319 of the book.
//
// PARAMETERS:
//  K key
//
// RETURN VALUE:
//  The key of the successor or 0 if no such successor exists
//=================================================
template <typename D, typename K> 
K BST<D, K>::successor(K k) {
    auto x = iterative_tree_search(root, k);
    if (x == nullptr) {
      std::cout << "Warning: default key of 0 returned for successor call "
                   "because there is no node that has the passed in key"
                << std::endl;
      return 0;
    }

    if (x->right != nullptr) {
        return min(x->right)->key;
    } else {
        auto y = x->parent;
        while (y != nullptr && x == y->right) {
            x = y;
            y = y->parent;
        }
        if (y == nullptr) {
            std::cout << "Warning: No successor found, default value of 0 returned" << std::endl;
            return 0;
        }
        return y->key;
    }
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
string BST<D, K>::to_string() const {
    if (root == nullptr) {
        return "";
    }

    stringstream s;
    s << root->key << " ";

    // Level order traversal with a queue
    queue<Node<D, K>*> node_queue;
    node_queue.push(root);

    while (!node_queue.empty()) {
        auto node = node_queue.front();
        auto left = node->left;
        auto right = node->right;

        if (left != nullptr) {
            s << left->key << " ";
            node_queue.push(left);
        }

        if (right != nullptr) {
            s << right->key << " ";
            node_queue.push(right);
        }

        node_queue.pop();
    }

    string str = s.str();
    str = str.substr(0, str.size() - 1); // Remove trailing space
    return str;
}

template <typename D, typename K> 
string BST<D, K>::in_order(Node<D, K>* x) {
    stringstream s;

    if (x != nullptr) {
        s << in_order(x -> left);

        s << x -> key << " ";

        s << in_order(x -> right);
    }

    string str = s.str();
    return str;
}
//=================================================
// in_order()
// same as to_string, but keys displayed in
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
    

    string in_order_str = in_order(root);
    in_order_str = in_order_str.substr(0, in_order_str.size() - 1); // Remove trailing space
    return in_order_str;
}

//=================================================
// delete_BST(Node<D, K>*)
// Convenience function to delete a single node with delete_BST(Node<D, K>*, Node<D, K>*)
//=================================================
template <typename D, typename K> 
static void delete_BST(Node<D, K>* node) {
    delete_BST(node->left, node->right);

    delete node;
}

//=================================================
// in_range
// Checks if a `val` is in the range `low` to `high` inclusive
//
// PARAMETERS:
//  low: The low end of a range
//  high: The high end of a range
//
// RETURN VALUE:
//  bool representing whether `val` is in range
//=================================================
template <typename K> 
bool in_range(K low, K high, K val) {
    return ((val >= low) && (val <= high));
}

template <typename D, typename K> 
void BST<D, K>::trim(K low, K high, Node<D, K> *current) {
    if (current == nullptr) {
        return;
    }

    bool current_in_range = in_range(low, high, current->key);
    if (current == root && !current_in_range) {
        delete_BST(root);
        root = nullptr;
        return;
    } 

    if (current_in_range) {
        trim(low, high, current->left);
        trim(low, high, current->right);
    } else if (current->key > high){
        if (current->right != nullptr) {
            delete_BST(current->right);
            current->right = nullptr;
        }

        auto replacement = remove_node(current);
        trim(low, high, replacement);
    } else { // current->key must be less than high
        if (current->left != nullptr) {
            delete_BST(current->left);
            current->left = nullptr;
        }

        auto replacement = remove_node(current);
        trim(low, high, replacement);
    }
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
void BST<D, K>::trim(K low, K high) {
    trim(low, high, root);
}
