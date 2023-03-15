Create a design before you begin to code that describes or shows how we can store data in a hash table and what kind of problem we could solve with a hash table.
  A hash table is essentially an array key value pairs. I'm not sure how in depth you want this design to go without me literally just making a hashtable. Each spot in the array holds a key to a value. The good thing about hash tables is that they have a constant speed of access thanks to the array and being able to index into it. Because of this hash tables can be used for many things. Anything you want to be able to organize and access the information quickly for would be able to make use of a hash table. In my example I will be storing a student class in the indexes of my hashtable. For my complex hashtable I decided on using chaining as a way to deal with collisions.

Create some tests (at least one per piece of functionality) before you begin coding that you want your hashtable to pass before you start coding.
INSERT:test insert on an empy and full table. check for expected results and collisions. Intentionally put two of the same value in to test the replacement/chaining. 
FIND: With the find, test for values that exist within the table and those that dont. Try to find nothing. make sure you can find something in the chain at the front and back.
Create a hashtable that resolves collisions by simply overwriting the old value with the new value, including at least:

Describe the way that you decide on hashing a value 
(this can be simple or complex based on how interesting you find the topic)
to make the indicies as unique as possible I took the value of the characters and multipleid it by the index +1

An insert function that places the value at the appropriate location based on its hash value
 INSERT:
  void insert(Student *student)
  {
    int idx = hash(student);

    delete data[idx];
    data[idx] = student;
  }
A contains function that returns whether the value is already in the hashtable
 CONTAINS:
   Student *find(const string &id)
  {
    return data[hash(id)];
  }
(optional) A delete function that removes a value based on its hash and then returns that value…

Then create a smarter hashtable (double hashing or chaining) including at least the same functions as the simple hashtable

INSERT:
void insert(Student &student)
  {
    int index = hash(student);
    N_ *node  = data[index];
    
    data[index] = new N_(student, node);
  }
  
 CONTAINS:
  Student *find(const string &key)
  {
    N_ *node  = data[::hash(key)];
    while (node != nullptr && node->value.key() != key)
    {
      node = node->next;
    }
    return (node ? &(node->value) : nullptr);
  }
Compare some information relating to collisions (frequency) and their effect on complexity (of insert and contains methods)
collisions frequency are the same the difference is how they're treated. In the simple one we're overwriting the value but in the complex one we're chaining.The complexity for the inserts are the same in my code. For the contains method however, the chaining one is a higher comlexity. In the worst case it can be O(n) because there is a small chance you could have all yourvalues in the same linked list.
