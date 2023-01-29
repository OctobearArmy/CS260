-I would like to design a hold line like the ones they have for the doctors or dentists office when you call them
(of course it isn't a perfect simulation because in real life people can choose to hang up at any point in the line)
  -CLASSES:
  1. Node class(could also be a struct)
    - variable (phone number string (or i guess *list of ch))
    - pointer to next node (=NULL) 
    -default consructor
    -functions
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
      7.newCaller- creates a new node with new data to get readt to push it to the front
