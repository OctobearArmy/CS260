#pragma once
#include <iostream>
#include <string>


#include "node.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;


//============================================================================//
template <typename T>
class binaryTree {
  typedef BinaryNode<T> _N;

private:
  _N *_root;

  _N  *_add       (T val, _N *cur);
  void _delete    (_N *cur);
  void _deleteNode(_N **cur);

  void _printInOrder   (_N *cur, string prefix);
  void _printPreOrder  (_N *cur);
  _N  *_printLevelOrder(_N *cur, _N *level=nullptr);

  _N **_find(T val, _N **cur);
  _N **_findMin(_N **cur);
  _N **_findMax(_N **cur);

//----------------------------------------------------------------------------//

  // int _max(T a, T b) { return a > b ? a : b; }

  // int _height(_N *cur) {
  //   if (cur) return _max(_height(cur->left), _height(cur->right)) + 1;
  //   else     return -1;
  // }
//----------------------------------------------------------------------------//

public:
  binaryTree() {_root = nullptr; }

  void addValue(T val) {_root =_add(val,_root); } //Ologn()

  void deleteValue(T val) {_deleteNode(_find(val, &_root)); } //Ologn()
  
  void printInOrder() {_printInOrder(_root, ""); } //O(n)
  
  void printPreOrder() {_printPreOrder(_root); } //O(n)

  void printLevelOrder() { //O(n)
    _N *tree =_printLevelOrder(_root);

    _printPreOrder(tree);
    _delete(tree);
  }

//----------------------------------------------------------------------------//

  // int height() { return _height(_root); }
  

  ~binaryTree() {_delete(_root); _root = nullptr; }

};
//============================================================================//

#include <iostream>
#include <string>

#include "binaryTree.hpp"

#include "node.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

//----------------------------------------------------------------------------//
template <typename T>
BinaryNode<T> *binaryTree<T>::_add(T val, BinaryNode<T> *cur) { //O(logn) if balanced otherwise worst case scenerio O(n)
    if (cur) {
      if (val <= cur->data) cur->left  =_add(val, cur->left);
      else                  cur->right =_add(val, cur->right);
      return cur;
    }
    return new BinaryNode<T>(val);
  }
//----------------------------------------------------------------------------//
template <typename T>
void binaryTree<T>::_delete(BinaryNode<T> *cur) { //top down deletion 
    if (cur) {
       _delete(cur->left);
       _delete(cur->right);
       delete cur; 
    }
  }
//----------------------------------------------------------------------------//
template <typename T>
void binaryTree<T>::_printInOrder(BinaryNode<T> *cur, string prefix) { //O(n)
    if (cur) {
      _printInOrder(cur->left, prefix);
      cout << prefix << cur->data << endl;
      _printInOrder(cur->right, prefix);
    }
  }
//----------------------------------------------------------------------------//
template <typename T>
void binaryTree<T>::_printPreOrder(BinaryNode<T> *cur) { //O(n)
    if (cur) {
      cout << cur->data << endl;
      _printPreOrder(cur->left);
      _printPreOrder(cur->right);
    }
  }
//----------------------------------------------------------------------------//
template <typename T>
  BinaryNode<T> *binaryTree<T>::_printLevelOrder(BinaryNode<T> *cur, BinaryNode<T> *level)
  {
    if (!cur) return level;

    BinaryNode<T> *down = nullptr;
    
    if (level) {
      down = level->right;
      level->right = nullptr;
    }

    down =_printLevelOrder(cur->right, down);
    down =_printLevelOrder(cur->left , down);
    return new BinaryNode<T>(cur->data, level, down);
  }
  //----------------------------------------------------------------------------//
template <typename T>
  BinaryNode<T> **binaryTree<T>::_find(T val, BinaryNode<T> **cur) { //O(logn) if balanced otherwise worst case scenerio O(n)
    if (cur && *cur) {
      T data = (*cur)->data;
      if (val == data) return cur;
      cur = (val < data ? &((*cur)->left) : &((*cur)->right));
      return _find(val, cur);
    }
    return nullptr;
  }
//----------------------------------------------------------------------------//
template <typename T>
  BinaryNode<T> **binaryTree<T>::_findMin(BinaryNode<T> **cur) { //O(logn) if balanced otherwise worst case scenerio O(n)
    while ((*cur)->left) cur = &((*cur)->left);
    return cur;
  }
//----------------------------------------------------------------------------//
template <typename T>
  BinaryNode<T> **binaryTree<T>::_findMax(BinaryNode<T> **cur) { //O(logn) if balanced otherwise worst case scenerio O(n)
    while ((*cur)->right) cur = &((*cur)->right);
    return cur;
  }
//----------------------------------------------------------------------------//
template <typename T>
  void binaryTree<T>::_deleteNode(BinaryNode<T> **cur) { //O(logn) if balanced
    if (!(*cur)->left && !(*cur)->right) {
      delete *cur;
      *cur = nullptr;
      return;
    }
    BinaryNode<T> **node = ((*cur)->left ?_findMax(&((*cur)->left))
                              :_findMax(&((*cur)->right)));
    (*cur)->data = (*node)->data;
    _deleteNode(node);
  }
//----------------------------------------------------------------------------//