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

        N_ *addBefore(T newData) { //O(1)
            N_ *node = new N_(newData, this, prev); // Create new node with next and prev pointers.
            if (prev) {
                prev->next = node;
            } 
            prev = node;
            return node;
        }
        N_ *addAfter(T newData) { //O(1)
            N_ *node = new N_(newData, next, this);
            if (next) {
                next->prev = node;
            }
            next = node;
            return node;
        }
        void unlink() { //O(1)
            if (prev) {
                prev->next = next;
            }
            if (next) {
                next->prev = prev;
            }
            next = prev = nullptr;
        }

        ~Node() { unlink(); }//deconstructor helpful: https://www.tutorialspoint.com/cplusplus/cpp_constructor_destructor.htm
};
//============================================================================//

template <typename T>
class LinkedList {
    typedef Node<T> N_;

    private:
        N_  head_;
        N_ *tail_;
        int length_;

        N_ *first_() { return head_.next; }

    public:
        //--------------------------------------------------------------------//
        LinkedList() {
            tail_= &head_;
            length_= 0;
        }
        //--------------------------------------------------------------------//
        bool isEmpty() { return (first_() == nullptr); } //O(1)
        //--------------------------------------------------------------------//
        void printList() { //O(n)
            N_ *node = first_();

            for (int idx = 0; node != nullptr; ++idx, node = node->next) {
                cout << idx << " : " << node->data << endl;
            }
        }
        //--------------------------------------------------------------------//
        void addFirst(T data) { //O(1)
            if (isEmpty()) {
                tail_ = head_.addAfter(data);
            }
            else {
                head_.addAfter(data);
            }
            length_++;
        }
        //--------------------------------------------------------------------//
        void addLast(T data) { //O(1)
            tail_= tail_->addAfter(data);
            length_++;
        }
        //--------------------------------------------------------------------//
        T getValAtPos(int idx) { //don't call if out of range of empty //O(1)
            if (idx <= 0) {
                return first_()->data;
            }
            else if (idx >= length_) {
                return tail_->data;
            }
            else {
                N_ *node = first_();
                for (int i = 0; i < idx; ++i) {
                    node = node->next;
                }
                return node->data;
            }
        }
        //--------------------------------------------------------------------//
        void addAtPosition(int idx, T data) { //O(n)
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
        //--------------------------------------------------------------------//
        void autoSort(T val) {
            N_ *node = &head_;

                while (node->next != nullptr && val > node->next->data) {
                    node = node->next;
                } 
                node->addAfter(val);
                length_++;
        }
        //--------------------------------------------------------------------//
        bool searchVal(T val) {
            N_ *node = first_();

            while (node != nullptr && val > node->data) {
                // cout << "Found: " << node->data << endl;
                node = node->next;
            }
            // if (node) cout << "Found: " << node->data << endl;
            // else cout << "Didn't find." << endl;
            return (node != nullptr && val == node->data);
        }
        //--------------------------------------------------------------------//
        int searchPos(T val) { //returns position which is = to idx 
            int pos  = 0;
            N_ *node = first_();
            
            while (node != nullptr && val < node->data) {
                node = node->next;
                pos++;
            }
            if (node != nullptr && val == node->data) return pos;
            return 0; 
        }
        //--------------------------------------------------------------------//
        
};

//============================================================================//
template <typename T>
class Array {
    private:
    T *data_;     // Array of data elements.
    int size_;    // Current array capacity.
    int length_;  // Current # of used elements.

    void _resize() {
        if (length_ == size_) {
            size_ *= 2;
            T *data = new T[size_];

            memcpy(data, data_, length_ * sizeof(T));
            delete[] data_;
            data_ = data;
        }
    }

    public:
    Array() { size_ = 8;  data_ = new T[size_];  length_ = 0; }
    //--------------------------------------------------------------------//
    void addSorted(T data) {
        _resize();
        int idx = length_;
        while (idx > 0 && data_[idx-1] > data) {
            data_[idx] = data_[idx-1];
            idx--;
        }
        data_[idx] = data;
        length_++;
    }
    //--------------------------------------------------------------------//
    int binarySearch(T target) {
        int first = 0;
        int last = length_ -1;
        while (first <= last) {
            int mid = first + ((last - first) / 2);

            if (data_[mid] == target) {
                return mid;
            }
            if (data_[mid] < target) {
                first = mid + 1;
            }
            else {
                last = mid -1;
            }
        }
        return -1;
    }
    //--------------------------------------------------------------------//
    void printArr() {
        int i = 0;
        for (i; i < length_; i++) {
            cout << i << " : " << data_[i] << endl;
        }
    }
    


};

//============================================================================//

int main() {
    int val = 90;
    LinkedList<int> list;
    Array<int> array;
    list.autoSort(5);
    list.autoSort(100);
    list.autoSort(10);
    list.autoSort(-1);
    list.autoSort(1);
    list.autoSort(16);
    list.autoSort(3);
    list.autoSort(2);
    list.printList();
    if (list.searchVal(5)) {
        cout<< "5 exists in this list" << endl;
    }

    array.addSorted(5);
    array.addSorted(9);
    array.addSorted(1);
    array.addSorted(18);
    array.addSorted(-12);
    array.printArr();
    cout << "value " << val <<" is at idx: " << array.binarySearch(val) << endl;



    return 0;
}