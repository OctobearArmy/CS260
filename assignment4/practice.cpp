#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

template <typename T>
class Node {
    typedef Node<T> N_;

    public:
        T  data;
        N_ *next;
        N_ *prev;

        Node() { next = prev = nullptr; }
        Node(T newData, N_ *newNext = nullptr, N_ *newPrev = nullptr) {
            data = newData;
            next = newNext;
            prev = newPrev;
        }

        N_ *addBefore(T newData) {
            N_ *node = new N_(newData, this, prev); // Create new node with next and prev pointers.
            if (prev) {
                prev->next = node;
            } 
            prev = node;
            return node;
        }
        N_ *addAfter(T newData) {
            N_ *node = new N_(newData, next, this);
            if (next) {
                next->prev = node;
            }
            next = node;
            return node;
        }
        void unlink() {
            if (prev) {
                prev->next = next;
            }
            if (next) {
                next->prev = prev;
            }
            next = prev = nullptr;
        }

        ~Node() { unlink(); }
};

template <typename T>
class LinkedList {
    typedef Node<T> N_;

    private:
        N_  head_;
        N_ *tail_;
        int length_;

        N_ *first_() { return head_.next; }

    public:
        LinkedList() {
            tail_= &head_;
            length_= 0;
        }

        bool isEmpty() const { return (first_() == nullptr); }

        void printList() {
            N_ *node = first_();

            for (int idx = 1; node != nullptr; ++idx, node = node->next) {
                cout << idx << " : " << node->data << endl;
            }
        }

        void addFirst(T data) {
            if (isEmpty()) {
                tail_ = head_.addAfter(data);
            }
            else {
                head_.addAfter();
            }
            length_++;
        }
        void addLast(T data) {
            tail_= tail_->addAfter(data);
            length_++;
        }

        void addAtPosition(int pos, T data) {
            int idx = pos - 1;

            if (idx <= 0) {
                addFirst(data);
            }
            else if (idx >= length_) {
                addLast(data);
            }
            else {
                N_ *node = first_();

                for (int i = 0; i < idx; ++i) {
                    node = node->next;
                }
                node->addBefore(data);
                length_++;
            }
        }

        bool removeAtPosition(int pos) {
            int idx = pos - 1;

            if (idx < 0 || idx >= length_) {
                return false;
            }

            N_ *node = first_();

            for (int i = 0; i < idx; ++i) {
                node = node->next;
            }
            delete node;  // Unlink node (in destructor) and delete.
            length_--;
        }

};
int main(){
    LinkedList<int> list;
    list.addAtPosition(1,10);
    list.addAtPosition(1,11);
    list.addAtPosition(1,15);
    list.addAtPosition(1,16);
    list.addAtPosition(1,19);
    list.printList();
    list.removeAtPosition(1);
    list.removeAtPosition(1);
    list.removeAtPosition(1);

return 0;
}