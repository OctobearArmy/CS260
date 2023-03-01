#include <iostream>
#include <string>

#include "node.h"
#include "binaryTree.h"



using std::cin;
using std::cout;
using std::endl;
using std::string;

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
  tree.addValue('b');

  cout << "Printing in order." << endl;
  tree.printInOrder();

  tree.deleteValue(20);

  cout << "Printing in order." << endl;
  tree.printInOrder();

  cout << "Printing pre order." << endl;
  tree.printPreOrder();

  cout << "Printing level order." << endl;
  tree.printLevelOrder();

  // cout << "Tree height: " << tree.height() << endl;
  return 0;
}
