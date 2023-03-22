#include <iostream>
#include <string>
#include <vector>
#include <queue>

// #include "graphNode.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::priority_queue;

typedef unsigned int uint;

const  int ROWS  = 6;
const  int COLS  = 7;
const  int NODES = ((ROWS) * (COLS));
const  int EDGES = (((NODES) * 8 - ((ROWS-2) + (COLS-2)) * 3 - 4 * 5) / 2); // Formula for the # of edges.

const uint MAX_COST    = (uint)-1;
const uint NUM_MATCHES = 4;

/*
 GraphNode neighbor indices:
    0 (AboveLeft)    1 (Above)    2 (AboveRight)

    3 (Left)                      4 (Right)

    5 (BelowLeft)    6 (Below)    7 (BelowRight)
*/
enum NghbrDir {NghbrUpLeft = 0, NghbrUp,   NghbrUpRght,
               NghbrLeft,                  NghbrRght,
               NghbrDownLeft,   NghbrDown, NghbrDownRght};

const char *__dirStr[] = {"UpLeft",   "Up",   "UpRight",
                          "Left",             "Right",
                          "DownLeft", "Down", "DownRight", ""};
const char *__dirSym   = "\\|/--/|\\"; 

const int __oppDir[] = {NghbrDownRght, NghbrDown, NghbrDownLeft,
                        NghbrRght,                NghbrLeft,
                        NghbrUpRght,   NghbrUp,   NghbrUpLeft};

const int __deltaX[] = {-1,  0,  1,
                        -1,      1,
                        -1,  0,  1};
const int __deltaY[] = {-1, -1, -1,
                         0,      0,
                         1,  1,  1};

const int __dirCost[] = {-1, -1, -1,   // Edge direction costs.
                          3,      3,
                          2,  1,  2};

class GraphEdge;
class GraphNode;
class Graph;

//============================================================================//
class GraphEdge {
friend GraphNode;
friend Graph;

private:
  GraphNode *_n0, *_n1;
  int        _val;

  void _set(GraphNode *n0, GraphNode *n1, int val) { //O(1)
    _n0  = n0;
    _n1  = n1;
    _val = val;
  }

public:
  GraphEdge() :_n0(nullptr),_n1(nullptr),_val(0) { }//O(1)
  GraphEdge(GraphNode *n0, GraphNode *n1, int val) :_n0(n0),_n1(n1),_val(val) { }//O(1)

  GraphNode *to(const GraphNode *from) const {
    if (from ==_n0) return _n1;
    if (from ==_n1) return _n0;
    return nullptr;
  }

  int cost() const { return _val; }
};
//============================================================================//

//============================================================================//
class GraphNode {
friend class Graph;

private:
  GraphEdge *_edge[8];
  int        _id;
  int        _minDir;
  uint       _cost;
  char       _symbol;

  void _setEdge(int direction, GraphEdge *edge) {//O(1)
    _edge[direction] = edge;
    // { GraphNode *to = edge->to(this);
    //   printf("Set edge: from=%2d  to=%2d  val=%d  dir=%s(%d)\n",_id, (to ? to->_id : -1), edge->_val, __dirStr[direction], direction);
    //   for (int i = 0; i < 8; i++) {
    //     GraphEdge *e =_edge[i];
    //     if (e) printf("       %d: %2d - %2d (%d) '%s'\n", i, (e->_n0 ? e->_n0->_id : -1), (e->_n1 ? e->_n1->_id : -1), e->_val, __dirStr[i]);
    //     else   printf("       %d: No edge\n", i);
    //   }
    // }
  }

public:
  GraphNode() {//O(1)
    static int id = 0;

    for (int i = 0; i < 8; i++) {
      _edge[i] = nullptr;
    }
    _id     = id++;
    _minDir = -1;
    _cost   = MAX_COST;
    _symbol = ' ';
    // printf("Created node: id=%2d  symbol='%c'\n",_id,_symbol);
  }

  bool   isEmpty() const { return _symbol == ' '; }//O(1)
  char getSymbol() const { return _symbol; }//O(1)

  void     reset()       {_minDir = -1; _cost = MAX_COST; }//O(1)
  int    minPath() const { return _minDir; }//O(1)
  uint   minCost() const { return _cost; }//O(1)

  bool hasNeighbor(int direction) const {//O(1)
    GraphEdge *edge =_edge[direction];

    return (edge ?_edge[direction]->to(this) != nullptr : false);
  }

  GraphNode *getNeighbor(int direction) const {//O(1)
    GraphEdge *edge =_edge[direction];

    return (edge ? edge->to(this) : nullptr);
  }

  GraphNode *setSymbol(char s) {_symbol = s; return this; }//O(1)

  int countMatches(int direction, char symbol) const;

  int matches(int need);
};
//----------------------------------------------------------------------------//
// GraphNode* GraphNode::setSymbol(char s) {
//   if (!isEmpty()) return nullptr;

//   GraphNode *down = _nghbr[_downIdx];

//   if (down && down->isEmpty()) {
//     return down->setSymbol(s);
//   }
//   _symbol = s;
//   return this;
// }
//----------------------------------------------------------------------------//
int GraphNode::countMatches(int direction, char symbol) const {//O(sqrt(n))
  if (_symbol != symbol) return 0;

  GraphEdge *edge  =_edge[direction];
  GraphNode *nghbr = (edge ? edge->to(this) : nullptr);
  int        cnt   = 1;

  if (nghbr) {
    cnt += nghbr->countMatches(direction, symbol);
  }
  return cnt;
}
//----------------------------------------------------------------------------//
int GraphNode::matches(int need) {//O(sqrt(n))
  int max =  0,
      cnt =  0; 
  int dir = -1;

  for (int i = NghbrUpLeft; i <= NghbrLeft; ++i) {
    cnt = countMatches(i,_symbol) + countMatches(__oppDir[i],_symbol) + 1;
    if (cnt > max) {
      max = cnt;
      dir = i;
    }
  }
  if (max >= need) return dir;
  return -1;
}
//============================================================================//

//============================================================================//
struct PathElem {//O(1)
  GraphNode *node;
  uint       cost;
  int        dir;

  PathElem()                           : node(nullptr), cost(-1), dir(-1) { }
  PathElem(GraphNode *n, int c, int d) : node(n), cost(c), dir(d) { }
};
//============================================================================//

//============================================================================//
// Needed for std::priority_queue comparison:
// https://www.geeksforgeeks.org/custom-comparator-in-priority_queue-in-cpp-stl/
class Compare {//O(1)
public:
  bool operator()(const PathElem &e0, const PathElem &e1) {
    return (e0.cost > e1.cost);
  }
};
//============================================================================//


//============================================================================//
class Graph {
friend int main();

private:
  vector<GraphNode> _node;   // Board nodes.
  vector<GraphEdge> _edge;
  GraphNode *_enter[COLS];
  int _rows, _cols;

  // GraphNode *_grid(int row, int col) {
  //     return &(_node[row * COLS + col]);
  // }

  // void _addEdge(size_t idx, GraphNode *n0, GraphNode *n1, int val) {
  //   if (idx <_edge.size()) _edge[idx]._set(n0, n1, val);
  // }

  GraphNode *_addNode();
  GraphEdge *_addEdge(GraphNode *n0, GraphNode *n1, int direction);

  void _addTop();
  void _init();

  void       _resetNodes();
  GraphNode *_findMinPath(GraphNode *beg);

public:
    Graph() :_node(0),_edge(0),_rows(0),_cols(COLS) {_init(); }

    void showBoard(bool showCost=false);

    bool addSymbol(char sym, char col);
};
//----------------------------------------------------------------------------//
GraphNode *Graph::_addNode() {//O(1)
  size_t size =_node.size();

  // if (size ==_node.capacity()) {
  //   _node.reserve(size + COLS);
  // }
  _node.resize(size + 1);
  return &(_node[size]);
}
//----------------------------------------------------------------------------//
GraphEdge *Graph::_addEdge(GraphNode *n0, GraphNode *n1, int direction) {//O(1)
  if (n0 == nullptr || n1 == nullptr) return nullptr;

  size_t idx =_edge.size();

  // printf("Add edge (before): idx=%3d  n0=%2d  n1=%2d\n", (int)idx, n0->_id, n1->_id);

  // printf("Edge vector (before): size=%4llu:%4llu  capacity=%4llu\n",_edge.size(), idx,_edge.capacity());
  // for (int i = 0; i < (int)(_edge.size()); i++) {
  //   GraphEdge *e = &(_edge[i]);
  //   printf("    Edge %4d: %2d - %2d -> %2d\n", i, (e->_n0 ? e->_n0->_id: -1), (e->_n1 ? e->_n1->_id: -1), e->_val);
  // }

  _edge.push_back(GraphEdge{n0, n1, __dirCost[direction]});

  GraphEdge *edge = &(_edge[idx]);

  n0->_setEdge(         direction,  edge);
  n1->_setEdge(__oppDir[direction], edge);
  // printf("Add edge (after ): idx=%3d  n0=%2d  n1=%2d\n", (int)idx, n0->_id, n1->_id);

  // printf("Edge vector (after ): size=%4llu:%4llu  capacity=%4llu\n",_edge.size(), idx,_edge.capacity());
  // for (int i = 0; i < (int)(_edge.size()); i++) {
  //   GraphEdge *e = &(_edge[i]);
  //   printf("    Edge %4d: %2d - %2d -> %2d\n", i, (e->_n0 ? e->_n0->_id: -1), (e->_n1 ? e->_n1->_id: -1), e->_val);
  // }
  return edge;
}
//----------------------------------------------------------------------------//
void Graph::_addTop() {   //O(sqrt(n))
  GraphNode *prev = nullptr;
  GraphNode *left = nullptr,
            *down =_enter[0];

  // puts("******** ADDING TOP ROW ********");
  // for (int col = 0; col <_cols; col++)
  //   printf("Enter[%d]: %2d\n", col, (_enter[col] ?_enter[col]->_id : (int)(-1)));
  for (int col = 0; col <_cols; col++) {
    GraphNode *node =_addNode(),
              *rght = (col + 1 <_cols ?_enter[col + 1] : nullptr);

    // printf("%2d(0): Enter: %2d  Prev: %2d  Node: %2d  Left: %2d  Down: %2d  Rght: %2d\n", col,
    //       (_enter[col] ?_enter[col]->_id : -1), (prev ? prev->_id : -1), node->_id, (left ? left->_id : -1),
    //       (down ? down->_id : -1), (rght ? rght->_id : -1));

    _addEdge(node, prev, NghbrLeft);
    if (down) {
      _addEdge(node, left, NghbrDownLeft);
      _addEdge(node, down, NghbrDown);
      _addEdge(node, rght, NghbrDownRght);
    }
    prev =_enter[col] = node;
    left = down;
    down = rght;
    // printf("%2d(6): Enter: %2d  Prev: %2d  Node: %2d  Left: %2d  Down: %2d  Rght: %2d\n", col,
    //       (_enter[col] ?_enter[col]->_id : -1), (prev ? prev->_id : -1), node->_id, (left ? left->_id : -1),
    //       (down ? down->_id : -1), (rght ? rght->_id : -1));
  }
  _rows++;
}
//----------------------------------------------------------------------------//
void Graph::_init() { //O(n)
  // Need to pre-allocate the full vector array for nodes and edges to avoid
  //   stale node & edge pointers.
  _node.reserve(NODES);
  _edge.reserve(EDGES);

  for (int col = 0; col < COLS; col++) _enter[col] = nullptr;
  for (int row = 0; row < ROWS; row++) _addTop();
}
//----------------------------------------------------------------------------//
void Graph::_resetNodes() { //O(n)
  for (size_t i = 0; i <_node.size(); i++) _node[i].reset();
}
//----------------------------------------------------------------------------//
GraphNode *Graph::_findMinPath(GraphNode *beg) { //O(n*log(n))
  GraphNode *minNode = nullptr;
  uint       minCost = MAX_COST;

  priority_queue<PathElem, vector<PathElem>, Compare> tree;

  tree.push(PathElem(beg, 0, -1));
  while (!tree.empty()) {
    PathElem elem = tree.top();

    tree.pop();
    
    GraphNode *node = elem.node;
    uint       base = elem.cost;

    if (node->_cost < MAX_COST) continue;

    node->_cost   = base;
    node->_minDir = elem.dir;
    for (int dir = NghbrLeft; dir <= NghbrDownRght; dir++) {
      GraphEdge *edge = node->_edge[dir];
      bool       push = false;

      if (edge) {
        GraphNode *next = edge->to(node);
        int        cost = edge->cost() + base;
        if (next && next->_symbol == ' ') {
          tree.push(PathElem(next, cost, __oppDir[dir]));
          push = true;
        }
      }
      if (dir == NghbrDown && !push && base < minCost) {
        minNode = node;
        minCost = base;
      }
    }
  }
  return minNode;
}
//----------------------------------------------------------------------------//
void Graph::showBoard(bool showCost) { //O(n)
  GraphNode *row =_enter[0];

  printf("Connect 4 Game Board: %d rows x %d cols\n",_rows,_cols);
  printf("    ");
  for (int c = 0; c <_cols; c++) printf("  %c ", (char)('A' + c));
  printf("\n    ");
  for (int c = 0; c <_cols; c++) printf("+---");
  puts("+");
  for (int r = 0; row && r <_rows; r++) {
    GraphNode *nxt = row->getNeighbor(NghbrDown);
    printf("    ");
    for (int c = 0; c <_cols; c++) {
      if (row) {
        char sym = row->getSymbol();
        if (showCost && sym == ' ') {
          uint cost = row->minCost();
          int  dir  = row->minPath();
          if (dir >= NghbrUpLeft && dir <= NghbrDownRght)
            sym = __dirSym[dir];
          if (cost > 99) cost = 99;
          if (dir <= NghbrLeft) printf("|%c%2d", sym, cost);
          else                  printf("|%2d%c", cost, sym);
        }
        else printf("| %c ", row->getSymbol());
        row = row->getNeighbor(NghbrRght);
      }
      else printf("| - ");
    }
    printf("|\n    ");
    for (int c = 0; c <_cols; c++) printf("+---");
    puts("+");
    row = nxt;
  }
}
//----------------------------------------------------------------------------//
bool Graph::addSymbol(char sym, char col) { //O(n * log(n))
  col -= 'A';
  if (col < 0 || col >=_cols) {
    puts("ERROR: Invalid column specified.");
    return false;
  }
  
  _resetNodes();

  GraphNode *beg =_enter[(uint)col],
            *end =_findMinPath(beg);
  
  if (end) {
    GraphNode *cur = end;
    while (cur != beg) {
      GraphEdge *edge = cur->_edge[cur->minPath()];
      edge->_val += 2;
      cur = edge->to(cur);
    }
    end->setSymbol(sym);
    return end->matches(NUM_MATCHES);
  }
  return false;
}
//============================================================================//

int main() {
  Graph graph;

  graph.showBoard();

  graph.addSymbol('x', 'D');  graph.showBoard(true);
  graph.addSymbol('o', 'A');  graph.showBoard(true);
  graph.addSymbol('x', 'D');  graph.showBoard(true);
  graph.addSymbol('o', 'A');  graph.showBoard(true);
  graph.addSymbol('x', 'D');  graph.showBoard(true);
  graph.addSymbol('o', 'A');  graph.showBoard(true);
  graph.addSymbol('x', 'D');  graph.showBoard(true);
  graph.addSymbol('o', 'A');  graph.showBoard(true);

  return 0;
}