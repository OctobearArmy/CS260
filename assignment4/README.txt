Create a linked-list that allows:

1. an add function that takes a value and inserts it into a given position into the list(example: myList.add(someValue, somePosition) )
INPUT:    list.addAtPosition(1,10);
          list.addAtPosition(1,11);
          list.addAtPosition(1,15);
          list.addAtPosition(1,16);
          list.addAtPosition(1,19);
          list.printList();
OUTPUT:   1 : 19
          2 : 16
          3 : 15
          4 : 11
          5 : 10

2. a remove function that takes a position and removes the value stored at that position of the list and returns it(example: myList.remove(somePosition) )
INPUT:  using same list as in prev test
        list.removeAtPosition(1);
        list.removeAtPosition(1);
        list.removeAtPosition(1);
        list.printList();
OUTPUT:1 : 11
       2 : 10
3. a get function that takes a position and returns that value without removing it(example: myList.get(somePosition) )
INPUT:  using same list as in prev test
        cout << list.getValAtPos(1) << endl;
        cout << list.getValAtPos(2) << endl;
OUTPUT: 11
        10
Be sure to include at least one test function for each piece of functionality that should verify that your code is working!  This should be at least one test per behavior, likely more.  You can make these tests in a source file with a main where your tests are either directly in the main or inside their own standalone functions (please do not neglect the importance of testing!)
TEST 1
I tried to add 3 vallues to the same position
RESULT: they were added with each succesive one taking the first position.(This was the intended result)

TEST 2
I tried to remove out of bounds
RESULT: since the position I put in was greater than the length of the list it removed the last value iin the list instead. (This was the intended result)

TEST3
I tried to get a value from an empty list
RESULT: It crashed(I may add an exception later)

Once you have implemented and tested your code, add to the README file what line(s) of code or inputs and outputs show your work meeting each of the above requirements (or better, include a small screen snip of where it meets the requirement!).

(Note: we will cover the analysis of some of this in class next week, then we will have you analyze the next ones!)
Attempt to analyze the complexity of your implementation with line-by-line analysis,

Note: This assignment is to get you to think about the trade-offs that we may have to weigh before using one structure over another
