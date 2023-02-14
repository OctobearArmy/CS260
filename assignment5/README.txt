Follow along with the in-class exercise on this, do your best to get it working, and turn in what you come up with here!

Be sure to include at least one test for each function or piece of functionality that should verify that your code is working! you should start writing some tests before you write your implementations (just spend a few minutes thinking about the design and then write a few tests using natural language (English is preferred for me to be able to read it. ))
SORT TEST BOTH:  run through a list of #'s to see if the desired outcome happens make sure to include intagers, 0, large numbers, and multiple #s of the same value.


SEARCH TEST BOTH: search for #'s that do, and do not exist in the list. Print list to make sure position is correct.

Create an array-based list or a linked-list (and a bonus for attempting both) that:

1. automatically inserts values in the correct position based on some order of sorting (perhaps ascending integers or lexicographical sorting of words)
    ARRAY:
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
    
    
    LINKED LIST:
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

2. efficiently searches for elements (likely binary search for the array list, but what about the linked-list?)
    ARRAY:
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
    
    
    LINKED LIST:
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
    

Make a chart to compare the algorithmic complexity (use Big-O notation) of your insert, remove, and search algorithms you used for your structures
 -ARRAY:               -LINKED LIST:                                     are these for the last assignment?
 1. insert              1. insert
  -O(n)                   - O(n)
 2. remove              2. remove
  -O(n)                   - O(n)
 3. search              3. search
  - O(log(n))(if sorted)  - O(n)
 4. sort                 4. sort
   -O(n^2)                 -O(n^2)
                             

Once you have implemented and tested your code, add to the README file what line(s) of code or inputs and outputs show your work meeting each of the above requirements (or better, include a small screen snip of where it meets the requirement!).
