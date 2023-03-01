Create some tests (at least one per function) that you want your Binary Search Tree (BST) to pass before you start coding.
TEST ADD:
add multiple of the same number, negative values, 0, and perhaps a character. see if the nodes are in the proper place by printing out a taversal before and after

ADD FUNCTION:
_N *_add(T val, _N *cur) { //log(n)
    if (cur) {
      if (val <= cur->data) cur->left  =_add(val, cur->left);
      else                  cur->right =_add(val, cur->right);
      return cur;
    }
    return new _N(val);
  }

TEST REMOVE:
try to delete a number that doesn't exist in the binary tree. try to delete; the root, a branch node, a branch node with only a left branch, a branch node with only a right branch, a leaf node.

REMOVE FUNCTION:
  void _delete(_N *cur) { //top down deletion log(n)
    if (cur) {
       _delete(cur->left);
       _delete(cur->right);
       delete cur; 
    }
  }

TEST TRAVERSAL
print after removing and adding, try printing a traversal with no nodes, try printing a traversal with many of the same values, 

TRAVERSAL FUNCTIONS:
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
  
Implement a binary search tree that includes:

nodes to store values, 

an add function that adds a new value in the appropriate location based on our ordering rules,
(I likely used less than or equal to going to the left and greater than values going to the right)

a remove function that finds and removes a value and then picks an appropriate replacement node
(successor is a term often used for this)

we have at least one tree traversal function (I recommend starting with an in-order traversal!)
Bonus if you implement the three common traversals (pre-order, post-order, in-order)
More Bonus if you also include a breadth-first traversal (sometimes called a level-order search)

Analyze and compare the complexity of insert and search as compared to a binary tree without any order in its nodes.
With a BALANCED ordered binary tree the insert and search are O(logn), (note: an unbalanced tree could be a straight up linked list which would mean that worst case scenerio you have O(n). ),because it is proportional to the height of the tree as opposed to the unordered O(n).

Once you have implemented and tested your code, add to the README file what line(s) of code or inputs and outputs show your work meeting each of the above requirements (or better, include a small screen snip of where it meets the requirement!).
