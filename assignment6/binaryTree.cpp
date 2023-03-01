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

  _N *_add(T val, _N *cur) {
    if (cur) {
      if (val <= cur->data) cur->left  =_add(val, cur->left);
      else                  cur->right =_add(val, cur->right);
      return cur;
    }
    return new _N(val);
  }

  void _delete(_N *cur) { //top down deletion
    if (cur) {
       _delete(cur->left);
       _delete(cur->right);
       delete cur; 
    }
  }

  void _printInOrder(_N *cur, string prefix) {
    if (cur) {
      _printInOrder(cur->left, prefix + "\t");
      cout << prefix << cur->data << endl;
      _printInOrder(cur->right, prefix + "\t");
    }
  }

  void _printPreOrder(_N *cur) {
    if (cur) {
      cout << cur->data << endl;
      _printPreOrder(cur->left);
      _printPreOrder(cur->right);
    }
  }

  _N **_find(T val, _N **cur) {
    if (cur && *cur) {
      T data = (*cur)->data;
      if (val == data) return cur;
      cur = (val < data ? &((*cur)->left) : &((*cur)->right));
      return _find(val, cur);
    }
    return nullptr;
  }

  _N **_findMin(_N **cur) {
    while ((*cur)->left) cur = &((*cur)->left);
    return cur;
  }

  _N **_findMax(_N **cur) {
    while ((*cur)->right) cur = &((*cur)->right);
    return cur;
  }

  void _deleteNode(_N **cur) {
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

  void addValue(T val) {_root =_add(val,_root); }

  void deleteValue(T val) {_deleteNode(_find(val, &_root)); }

  void printInOrder() {_printInOrder(_root, ""); }

  ~binaryTree() {_delete(_root); _root = nullptr; }
};

int main() {
  binaryTree<int>tree;
  tree.addValue(20);
  tree.addValue(25);
  tree.addValue(25);
  tree.addValue(16);
  tree.addValue(45);
  tree.addValue(12);
  tree.addValue(11);
  tree.addValue(30);

  tree.printInOrder();
  tree.deleteValue(20);
  tree.printInOrder();



  return 0;
}
