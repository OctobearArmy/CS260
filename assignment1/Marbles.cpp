#include <stdio.h>
#include <stdlib.h>

#define BAG_SIZE 20
#define GET_SIZE  5

class Marble { //source help: https://www.w3schools.com/cpp/cpp_classes.asp
private:
    const char *color_; //aspect

public:
    Marble()                { } //default constructor needed for bag creation
    Marble(const char *color)    { color_ = color; }
    const char *getColor() const { return color_; } //technically method
};

class Bag {
private:
    Marble bag_[BAG_SIZE];
    int    cnt_;

public:
    Bag() { cnt_ = 0; }

    bool  is_empty() const { return cnt_ == 0; }
    bool  is_full () const { return cnt_ == BAG_SIZE; }
    bool not_empty() const { return cnt_ >  0; }
    bool add_marble(Marble marble) {
        if (!is_full()) {
            bag_[cnt_] = marble;
            cnt_++;
            return true;
        }
        return false;
    }

    Marble get_marble() {//Don't call if bad  is empty
        int num = cnt_;

        if (num > GET_SIZE) num = GET_SIZE;

	    // Get a random number
	    int idx = rand() % num;

        Marble marble = bag_[idx];

        cnt_--;
        if (idx < cnt_) bag_[idx] = bag_[cnt_];//takes marble from top position and puts it in idx
        return marble;
    } 
};

int main(){
    Bag bag;
    const char *colors[] = {"Red", "Blue", "Green", "Yellow"};

    for (int i = 0; i < BAG_SIZE; ++i) {
	    int color = rand() % 4;
        Marble marble(colors[color]);
        printf("Adding '%s' marble to bag.\n", marble.getColor());
        bag.add_marble(marble);
    }

    while (bag.not_empty()) { //perhapse add a function that lets a user pull a single marble ifthere's time in the future
        Marble marble = bag.get_marble();
        printf("Removing '%s' marbled from bag.\n", marble.getColor());
    }
}
