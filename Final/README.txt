(20%) Create a design before you start coding that describes or shows how a graph structure could be used to store some kinds of data and solve some kind of problem (yes, this can be a game that needs a graph to represent a map!),
I plan to make a connect 4 like game that creates the board by adding vertexes and edges in to create a structure like this
    +---+---+---+---+---+---+---+     
    |\ /|\ /|\ /|\ /|\ /|\ /|\ /|                       
    |/ \|/ \|/ \|/ \|/ \|/ \|/ \| 
    +---+---+---+---+---+---+---+    
    |\ /|\ /|\ /|\ /|\ /|\ /|\ /|
    |/ \|/ \|/ \|/ \|/ \|/ \|/ \| 
    +---+---+---+---+---+---+---+
    |\ /|\ /|\ /|\ /|\ /|\ /|\ /|
    |/ \|/ \|/ \|/ \|/ \|/ \|/ \| 
    +---+---+---+---+---+---+---+
    |\ /|\ /|\ /|\ /|\ /|\ /|\ /|
    |/ \|/ \|/ \|/ \|/ \|/ \|/ \| 
    +---+---+---+---+---+---+---+
    
    the ( ---, \   , | ,  /  ) symbols represent the pointers to the neigbor nodes.  
                 \   |  /
I want the nodes to be able to keep track of 8 neigbors (unless they represent the corners/edges of the board)
I want it to work like a regular connect 4  game with X, O symbols representing different players
Unlike regular connect 4, when the user picks a top node (representing the top of the board where you drop in your little discs) I will make a spanning tree algorithm function that looks for the 'shortest path' (I hope combining the two is ok!) from that top node to all other nodes in the graph. The player piece/symbol will be placed at the end of the shortest path. Every time someone puts a piece in, the edges along the minimum path will increase in cost. Since I will be giving different costs to each edge it should shake things up! 


For this program I will create a 
 - a node class that stores 
     -the positions of the node neighbors
     - a node identifier (location, id, #, etc)
     -symbol
     
FUNCTIONS: computing distance from one node to another
           return neighbor (for a given direction)
           return the identifier
           return position
 
 - a graph class to keep track of the positions of the nodes
 FUNCTIONS: add nodes
            add edges
            find shortest path
            check matching symbol
  
  
  
IMPORTANT NOTE!!!: As I was coding I changed several things so this design is more of a rough draft really. It functions the same as I wanted it too but I added some things. For example, I added an edge class to keep track of the edge costs between nodes, which allowed me to dynically update the edge costs. I also added a path element class to use in conjuction with a std::priority_queue during the minimum path spanning tree computation.

(20%) Create some tests (at least two for each piece of functionality) before you start coding...
ADD NEW VERTEX 
  TEST 1:
   Add a vertex and check if it can be accessed correctly
  TEST 2:
   Add a vertex and check if its neighbors are updated correctly
   
ADD NEW EDGE 
  TEST 1:
   Test to ensure that the edges are connected correctly
  TEST 2:
   Test to ensure that each node has expected # of edges
  TEST 3:
   Test to ensure that the cost of each edge is correct
   
SHORTEST PATH 
  TEST 1:
   Test to ensure that it gives the expexted output on multiple posistions in the smaller graph
  TEST 2:
   Test to ensure that it gives the expexted output on multiple posistions in the updated/bigger graph
   
SPANNING TREE 
  TEST 1:
   Test to ensure that the total weight of the edges matches the expected weight
  TEST 2:
   Test to ensure that it gives the expexted output from multiple posistions (nodes) to make sure it is spanning to the expected nodes
    

(40%) Implement a graph class with at least the following below (this category effectively combines implementation and specification, partly to emphasize getting the algorithms working!):

(5%) a function to add a new vertex to the graph (perhaps add_vertex(vertex_name)),
          GraphNode *Graph::_addNode() {//O(1)
            size_t size =_node.size();

            // if (size ==_node.capacity()) {
            //   _node.reserve(size + COLS);
            // }
            _node.resize(size + 1);
            return &(_node[size]);
          }
(5%) a function to add a new edge between two vertices of the graph (perhaps add_edge(source, destination) or source.add_edge(destination)),
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
(15%) a function for a shortest path algorithm (perhaps shortest_path(source, destination)),
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
(15%) a function for a minimum spanning tree algorithm (example min_span_tree()).
  Same as above it combines the two functionalitues to look for the shortest path from the chosen top node to either an available bottom node or a node where the node in the downward direction of it already has a symbol.
  
(10%) Analyze the complexity of all of your graph behaviors (effectively a part of our documentation for grading purposes),
    I have added a comment with complexity next to each function in the code
(10%) Once you have implemented and tested your code, add to the README file what line(s) of code or inputs and outputs show your work meeting each of the above requirements (or better, include a small screen snip of where it meets the requirement!).


IMPORTANT NOTE 2: While I may have bitten off a lot for this project idea, the functions above work and have been tested with the expected results! 
