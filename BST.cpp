//=================================================
// empty()
// Description: Indicate whether the binary search tree
// bst is empty.
//
// RETURN VALUE:
//  true or false
//=================================================
template <typename D, typename K> 
bool BST<D, K>::empty() {}

//=================================================
// insert(D d, K k)
// Description: should insert a data d and key k into
// the binary search tree bst.
//
// PARAMETERS:
//  D data, K key
//
//=================================================
template <typename D, typename K> 
void BST<D, K>::insert(D d, K k) {}

//=================================================
// get(K k)
// Description: return the data associated with key k
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
// Description: should remove the first (closest to
// the root) node with key k in the bst.
//
// PARAMETERS:
//  K key
//=================================================
template <typename D, typename K> 
void BST<D, K>::remove(K k) {}

//=================================================
// max_data()
// Description: return the data associate with the
// largest key in bst.
//
// RETURN VALUE:
//  D data associate with the largest K key.
//=================================================
template <typename D, typename K> 
D BST<D, K>::max_data() {}

//=================================================
// max_key()
// Description: return the largest key in bst.
//
// RETURN VALUE:
//  Largest K key in the bst.
//=================================================
template <typename D, typename K> 
K BST<D, K>::max_key() {}

//=================================================
// min_data()
// Description: return the data associate with the
// smallest key in the bst.
//
// RETURN VALUE:
//  D data associate with the smallest K key.
//=================================================
template <typename D, typename K> 
D BST<D, K>::min_data() {}

//=================================================
// min_key()
// Description: return the smallest key in the bst.
//
// RETURN VALUE:
//  Smallest K key in the bst.
//=================================================
template <typename D, typename K> 
K BST<D, K>::min_key() {}

//=================================================
// successor(K k)
// Description: return the next key after the indicated
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
// Description: return all the keys in bst in string
// form.
//
// RETURN VALUE:
//  A string of keys.
//=================================================
template <typename D, typename K> 
string BST<D, K>::to_string() {}

//=================================================
// in_order()
// Description: same as to_string, but keys in
// ascending order.
//
// RETURN VALUE:
//  A string of keys in ascending order.
//=================================================
template <typename D, typename K> 
string BST<D, K>::in_order() {}

//=================================================
// trim(K low, K high)
// Description: should trim the binary search
// tree bst so that the keys of every node lie in
// the interval [low, high].
//
// PARAMETERS:
//  K low, K high
//=================================================
template <typename D, typename K> 
void BST<D, K>::trim(K low, K high) {}
