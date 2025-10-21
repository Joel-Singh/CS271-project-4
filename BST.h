#include <string>

using namespace std;

#ifndef BST_HEADER
#define BST_HEADER

template <typename D, typename K> 
struct Node {
  Node<D, K>* left;
  Node<D, K>* right;
  Node<D, K>* parent;
  D data;
  K key;
};

template <typename D, typename K>
class BST {
public:
  BST(void);
  ~BST(void);
  bool empty();
  void insert(D d, K k);
  D get(K k);
  void remove(K k);
  D max_data();
  K max_key();
  D min_data();
  K min_key();
  K successor(K k);
  string to_string();
  string BST<D, K>::in_order(Node<D, K>* x);
  string in_order();
  void trim(K low, K high);
private:
  void transplant(Node<D, K>* u, Node<D, K>* v);
  Node<D, K>* min(Node<D, K>* node);
  
  Node<D, K>* root;
};

#include "BST.cpp"

#endif
