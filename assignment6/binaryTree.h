#pragma once
#include <iostream>
#include <string>

#include "node.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

template <typename T>
class binaryTree {
  typedef BinaryNode<T> _N;

private:
  _N *_root;

  _N *_add(T val, _N *cur) { //log(n)
    if (cur) {
      if (val <= cur->data) cur->left  =_add(val, cur->left);
      else                  cur->right =_add(val, cur->right);
      return cur;
    }
    return new _N(val);
  }

  void _delete(_N *cur) { //top down deletion log(n)
    if (cur) {
       _delete(cur->left);
       _delete(cur->right);
       delete cur; 
    }
  }

  void _printInOrder(_N *cur, string prefix) { //O(n)
    if (cur) {
      _printInOrder(cur->left, prefix);
      cout << prefix << cur->data << endl;
      _printInOrder(cur->right, prefix);
    }
  }

  void _printPreOrder(_N *cur) { //O(n)
    if (cur) {
      cout << cur->data << endl;
      _printPreOrder(cur->left);
      _printPreOrder(cur->right);
    }
  }

  // O(n)
  // Backwards post order traversal to build a new binary tree where 
  // right points down to next level and left points to next node in
  // same level.
  _N *_printLevelOrder(_N *cur, _N *level=nullptr)
  {
    if (!cur) return level;

    _N *down = nullptr;
    
    if (level) {
      down = level->right;
      level->right = nullptr;
    }

    down =_printLevelOrder(cur->right, down);
    down =_printLevelOrder(cur->left , down);
    return new _N(cur->data, level, down);
  }

  // int _max(T a, T b) { return a > b ? a : b; }

  // int _height(_N *cur) {
  //   if (cur) return _max(_height(cur->left), _height(cur->right)) + 1;
  //   else     return -1;
  // }


  _N **_find(T val, _N **cur) { //logn()
    if (cur && *cur) {
      T data = (*cur)->data;
      if (val == data) return cur;
      cur = (val < data ? &((*cur)->left) : &((*cur)->right));
      return _find(val, cur);
    }
    return nullptr;
  }

  _N **_findMin(_N **cur) { //logn()
    while ((*cur)->left) cur = &((*cur)->left);
    return cur;
  }

  _N **_findMax(_N **cur) { //logn()
    while ((*cur)->right) cur = &((*cur)->right);
    return cur;
  }

  void _deleteNode(_N **cur) { //logn()
    if (!(*cur)->left && !(*cur)->right) {
      delete *cur;
      *cur = nullptr;
      return;
    }
    _N **node = ((*cur)->left ?_findMax(&((*cur)->left))
                              :_findMax(&((*cur)->right)));
    (*cur)->data = (*node)->data;
    _deleteNode(node);
  }


public:
  binaryTree() {_root = nullptr; }

  void addValue(T val) {_root =_add(val,_root); } //logn()

  void deleteValue(T val) {_deleteNode(_find(val, &_root)); } //logn()
  
  void printInOrder() {_printInOrder(_root, ""); } //O(n)
  
  void printPreOrder() {_printPreOrder(_root); } //O(n)

//reverse pre or
  void printLevelOrder() { //O(n)
    _N *tree =_printLevelOrder(_root);

    _printPreOrder(tree);
    _delete(tree);
  }

  // int height() { return _height(_root); }

  ~binaryTree() {_delete(_root); _root = nullptr; }

};

