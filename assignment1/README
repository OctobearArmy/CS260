-I would represent the marbles by a CLASS 
     -they would probobly be recognized by color or something color so say we have three colors (red, yellow, and  blue) they might also have multiple sizes (small medium or large.
     METHOD = marble constructing function(chosen by user or random)

-adding a marble to the marble bag consists of simply adding a FUNCTION that pushes the newest marble to another class(MARBLES) (also am I supposed to use python or C++?) I would set a limit for the class' capacity to 20 or so because a marble bag doesn't have an infanite capacity.
     VARIABLES= Array of marbles
              bag capacity
              marble count
     METHODS= add marble
              remove marble
              is empty
              is full
-Tests I could do would be trying to add more marbles than the bags limit, try to remove from an empty bag, test wether the marbles pulled out are the right color.
 NOTE: This code was NOT simple. I missunderstood the assignment. This actually took me forever.
 1.representing marbles: (lines 7-15)
           class Marble { 
           private:
               const char *color_; //aspect

           public:
               Marble()                { } //default constructor needed for bag creation
               Marble(const char *color)    { color_ = color; }
               const char *getColor() const { return color_; } //technically method
          };
2. add marbles to bag(lines 28-35)
          bool add_marble(Marble marble) {
             if (!is_full()) {
                 bag_[cnt_] = marble;
                 cnt_++;
                 return true;
             }
             return false;
         }
3. remove marbles from bag(lines 64-67)
         while (bag.not_empty()) { 
             Marble marble = bag.get_marble();
             printf("Removing '%s' marbled from bag.\n", marble.getColor());
         }
4. tests 
     I have solutions to combat all of the problems I thought up by making my tests and as for the testing color thing I have a screenshot for that should be in this folder
     
5 and 6. As for implementation I uploaded an image  that shows it working on my computer

ALTERNITAVELY
-I could represent the marbles with a struct (same attributes as in the first) 
    I would have to make a
-marble bag would be an arrray that would get added to using a function. I could use a function to keep track of how many marbles have been added/removed to make sure it isn't over capacity
