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

template <typename D, typename K>
BST<D, K>::~BST(void) {
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
        left: nullptr,
        right: nullptr,
        parent: nullptr,
        data: d,
        key: k
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
D BST<D, K>::get(K k) {}

//=================================================
// remove(K k)
// should remove the first (closest to
// the root) node with key k in the bst.
//
// PARAMETERS:
//  K key
//=================================================
template <typename D, typename K> 
void BST<D, K>::remove(K k) {}

//=================================================
// max_data()
// return the data associate with the
// largest key in bst.
//
// RETURN VALUE:
//  D data associate with the largest K key.
//=================================================
template <typename D, typename K> 
D BST<D, K>::max_data() {}

//=================================================
// max_key()
// return the largest key in bst.
//
// RETURN VALUE:
//  Largest K key in the bst.
//=================================================
template <typename D, typename K> 
K BST<D, K>::max_key() {}

//=================================================
// min_data()
// return the data associate with the
// smallest key in the bst.
//
// RETURN VALUE:
//  D data associate with the smallest K key.
//=================================================
template <typename D, typename K> 
D BST<D, K>::min_data() {}

//=================================================
// min_key()
// return the smallest key in the bst.
//
// RETURN VALUE:
//  Smallest K key in the bst.
//=================================================
template <typename D, typename K> 
K BST<D, K>::min_key() {}

//=================================================
// successor(K k)
// return the next key after the indicated
// key (if for smallest, then the smallest key after the
// indicated key, and vice versa)
//
// PARAMETERS:
//  K key
//
// RETURN VALUE:
//  The K key after the indicated K key.
//=================================================
template <typename D, typename K> 
K BST<D, K>::successor(K k) {}

//=================================================
// to_string
// return all the keys in bst in string
// form.
//
// RETURN VALUE:
//  A string of keys.
//=================================================
template <typename D, typename K> 
string BST<D, K>::to_string() {}

//=================================================
// in_order()
// same as to_string, but keys in
// ascending order.
//
// RETURN VALUE:
//  A string of keys in ascending order.
//=================================================
template <typename D, typename K> 
string BST<D, K>::in_order() {}

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
