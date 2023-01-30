#ifndef QUEUE_H__
#define QUEUE_H__

#include <exception>

//============================================================================//
template <typename T> 
class Node {
    public:
        T value;
        Node *next;

        Node() { next = nullptr; } // Constructor.
        Node(T new_val, Node *new_next=nullptr) {
            value = new_val;
            next  = new_next;
        }
};
//============================================================================//

//============================================================================//
template <typename T>
class Queue {
    typedef Node<T> _N;
    
    private:
        // Create a templated node of type T.
        _N *_head,
           *_tail;

        _N  *_first()         { return _head->next; } // gets pointer to first valid node
        void _first(_N *node) { _head->next = node; } // sets pointer to first valid node
    
    public:
        Queue() {_head =_tail = new _N(); }

        bool isEmpty() const { return _head ==_tail; }

        void enqueue(T value) {
            _tail->next = new _N(value);
            _tail       = _tail->next;
        }

        T peek() {      // Return first element data in queue (throws logic error exception if queue is empty).
            if (isEmpty()) {
                throw std::logic_error("Empty queue.");  // https://cplusplus.com/reference/stdexcept/logic_error/
            }
            return _first()->value;
        }

        T dequeue() {      // Removes first element from queue and returns its data (throws logic error exception if queue is empty).
            if (isEmpty()) {
                throw std::logic_error("Empty queue.");  // https://cplusplus.com/reference/stdexcept/logic_error/
            }

           _N node =_first();     // Pointer to node at the front of the queue.
           _N next = node->next;  // Copy of pointer to next node.
            T copy = node->value; // Copy of data in node.

            delete node;
            _first(next);  // Update first valid node.
            if (next == nullptr) { // If queue is now empty:
                _tail = _head;     //   reset tail pointer.
            }
            return copy;
        }
        
};
//============================================================================//

#define MAX_SIZE 64

//============================================================================//
template <typename T>
class QueueArr {
    private:
        T   arr[MAX_SIZE];  //pointer to first element
        int beg;  // Index of first element in queue.
        int end;  // Index of next available spot in queue.
        int size; // Current size.
        int max = MAX_SIZE;

        bool _empty() { return size == 0; }
        bool _full () { return size == max; }

        int  _incr(int idx) { return (++idx % max); }  // Compute next index by incrementing array index and wrapping around to 0 if necessary.
        
    public:
        QueueArr() {
             beg = end = 0;
             size = 0;
             max = MAX_SIZE;
        }

        // Queue is empty if the front and back are in the same spot
        bool isEmpty() { return _empty(); }

        bool isFull() { return _full(); }

        void enqueque(T value) {
            if(_full()) {
                throw std::logic_error("Full queue.");  // https://cplusplus.com/reference/stdexcept/logic_error/
            }
            arr[end] = value;
            end =_incr(end);
            size++;
        }

        T peek() {
            if (isEmpty()) {
                throw std::logic_error("Empty queue.");  // https://cplusplus.com/reference/stdexcept/logic_error/
            }            
            return arr[beg];
        }

        T dequeue() {
            T value = peek();

            beg =_incr(beg);
            size--;
            return value;
        }
};
//============================================================================//

#endif // ifndef QUEUE_H__
