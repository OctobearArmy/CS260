#pragma once
template <typename T> 
class BinaryNode {
  typedef BinaryNode<T> N_;

  public:
    T  data;
    N_ *right;
    N_ *left;

    BinaryNode() { right = left = nullptr; } 
    BinaryNode(T newData, N_ *newLeft = nullptr, N_ *newRght = nullptr) {
        data  = newData;
        left  = newLeft;
        right = newRght;
    }

  // N_ *addLeft(T newData) { //O(1)
  //   N_ *node = new N_(newData, this, left); // Create new node with next and prev pointers.
  //   if (left) {
  //       left->right = node;
  //   } 
  //   left = node;
  //   return node;
  // }
  // N_ *addAfter(T newData) { //O(1)
  //   N_ *node = new N_(newData, right, this);
  //   if (right) {
  //       right->left = node;
  //   }
  //   right = node;
  //   return node;
  // }
  void unlink() { //O(1)
    if (left) {
        left->right = right;
    }
    if (right) {
        right->left = left;
    }
    right = left = nullptr;
  }

  ~BinaryNode() { unlink(); }
};