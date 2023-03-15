#ifndef NODE_H__
#define NODE_H__

//============================================================================//
template <typename T> //O(1)
class Node {
    public:
        T value;
        Node *next;

        Node() { next = nullptr; } // Constructor.
        Node(T new_val, Node *new_next=nullptr) {
            value = new_val;
            next  = new_next;
        }

        T *operator->() { return &value; }
};
//============================================================================//

#endif // ifndef NODE_H__
