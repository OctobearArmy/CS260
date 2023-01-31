-I would like to design a hold line like the ones they have for the doctors or dentists office when you call them
(of course it isn't a perfect simulation because in real life people can choose to hang up at any point in the line)
  -CLASSES:
  1. Node class(could also be a struct)
    - variable (phone number string (or i guess *list of ch))
    - pointer to next node (=NULL) 
    - default consructor
    - functions
      1.getNum- gets phone number information
  2. Queue class
    - default front and back
    - intager variable to represent # of elements currently in queue
    - head(node that is first in the queue)
    - last
    - functions
        1.back-	Returns a reference to the last and most recently added element at the back of the queue.
        2.front-	Returns a reference to the first element at the front of the queue.(can combine with remove)
        3.empty-	Tests if the queue is empty.
        4.remove-	Removes an element from the front of the queue.
        5.add-	Adds an element to the back of the queue.
        6.size-	Returns the number of elements in the queue.
    3.Caller Class- (holds the data that is entered in for)
      -name 
      -phone number
      -functions:
        1. maybe a function to display/return caller data (depending on how I decide to structure)
      
      
1. Based on what we know about linked lists, stacks, and queues, design a linked queue (a queue using a linked-list to store the data in the structure)
   -shown above

Design, implement, and test a Queue data structure that:

1.uses a linked-list to store values in the queue
TEST 1: STORE
  - enter vallues and enquque. (INPUT)
    Enter caller name:
    Sarah
    Enter caller number:
    1234567
  - use peek to verify the values have been entered (OUTPUT)
    Caller name : Sarah
    Caller phone: 1234567
 CODE:
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

2.has an enqueue method that will appropriately add a value to the back of the queue as an appropriate element
   - see TEST 1
3.has a dequeue method that will appropriately remove an element from the front of the queue and return its value
TEST 2: DEQUEUE
  - enter vallues and enquque. (INPUT)
    Enter caller name:
    Sarah
    Enter caller number:
    541-926-3443
  - use dequeue  (OUTPUT)
    Removed front  :
    Caller name : Sarah       
    Caller phone: 541-926-3443
CODE:
      T dequeue() {      // ( O(1)) Removes first element from queue and returns its data (throws logic error exception if queue is empty).
          if (isEmpty()) {
              throw std::logic_error("Empty queue.");  // https://cplusplus.com/reference/stdexcept/logic_error/
          }

         _N *node =_first();     // Pointer to node at the front of the queue.
         _N *next = node->next;  // Copy of pointer to next node.
          T  copy = node->value; // Copy of data in node.

          delete node;
          _first(next);  // Update first valid node.
          if (next == nullptr) { // If queue is now empty:
              _tail = _head;     //   reset tail pointer.
          }
          return copy;
      }

  4.Optionally has a peek method that returns the value at the front of the queue without removing it
  TEST 3: PEEK
  - enter vallues and enquque. (INPUT)
    Enter caller name:
    Sarah
    Enter caller number:
    541-926-3443
  - use peek to verify the values have been entered (OUTPUT)
    Caller at front:
    Caller name : Sarah       
    Caller phone: 541-926-3443
  CODE:
       T peek() {      // Return first element data in queue (throws logic error exception if queue is empty).
          if (isEmpty()) {
              throw std::logic_error("Empty queue.");  // https://cplusplus.com/reference/stdexcept/logic_error/
          }
          return _first()->value;
      }

5.Bonus if you also create an array based Queue!
  CODE:
  template <typename T> //Helpful site https://www.codesdope.com/course/data-structures-queue/
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

Analyze the complexity of your implementations (at least the run-time of the add, remove, and peek methods).
(Note that we will often consider operations not having to do with the structure as O(1), even if they might be expensive operations in terms of real-time or space used)
(Note that if you are not in class when we talk about Asymptotic Big-O notation, you can find tons of good examples online)


Tests: Be sure to include at least one test for each piece of functionality that should verify that your code is working!

Be sure to commit changes regularly to your git repo

Once you have implemented and tested your code, add to the README file what line(s) of code or inputs and outputs show your work meeting each of the above requirements (or better, include a small screen snip of where it meets the requirement!). (I am unsure what lines of code I would be submitting. would I be submitting the enque function or where I call it in main?)(can you tell me how to include a screen snip to this file?)
