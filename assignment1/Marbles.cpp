#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using std:: cout;

#define BAG_SIZE 20
#define GET_SIZE  5
enum option{ADD =1, SELECT, VIEW, EXIT};

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

    int   count() const {return cnt_; }
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
//clears buffer
void clear_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
/*-----------------------------------------------------------------------------------------------------------*/
// Get intager value from input line (with verification).
int get_int(void) {
    int val = 0;

    while (scanf("%d", &val) != 1) {
        puts("Please enter an integer.");
        clear_buffer();
    }
    clear_buffer(); // eat the \n so that you don't have to press enter twice in future
    return val;
}
/*-----------------------------------------------------------------------------------------------------------*/
int get_option(const char *options[], int num_options,const char *header, const char *footer) {
    int option;

    while (true) {
        if (header != NULL && *header != 0) puts(header);
        for (int i = 0; i < num_options; ++i) {
            puts(options[i]);
        }
        if (footer != NULL && *footer != 0) puts(footer);
        printf("Choose an option: ");
        option = get_int();
        if (option >= 1 && option <= num_options) return option;
        printf("Invalid option: must enter an integer between 1 and %d.\n", num_options);
        // printf("Option chosen: %d\n", option);        
    }
    return 0;
}
/*-----------------------------------------------------------------------------------------------------------*/
int get_menu_option() {
    const char *header    = "\n\t------------------- Main Menu -------------------\n",
         *footer    = "\t-------------------------------------------------\n";
    const char *options[] = {"\t*\t\t1: Add Marble                               *",//array of pointers/strings
                             "\t*\t\t2: Remove Marble                            *",
                             "\t*\t\t3: Show Number of Marbles in the Bag        *",
                             "\t*\t\t4: Exit                                     *"};
    return get_option(options, 4, header, footer);  
}
/*-----------------------------------------------------------------------------------------------------------*/
int main(){
    Bag bag;
    const char *colors[] = {"Red", "Blue", "Green", "Yellow"};
    int option = 0;
    do {
        option = get_menu_option();    
        switch(option){
            case(ADD):
                if (bag.count()< BAG_SIZE) {
                    int color = rand() % 4;
                    Marble marble(colors[color]);
                    printf("Adding '%s' marble to bag.\n", marble.getColor());
                    bag.add_marble(marble);
                    break;
                }
                else{
                    cout <<"Bag is full.\n";
                    break;};
                            
            case(SELECT):
                if(!bag.is_empty()){
                Marble marble = bag.get_marble();
                printf("Removing '%s' marble from bag.\n", marble.getColor());}
                else{cout<<"Bag is empty.\n";}
                break;
                
                case(VIEW):
                    cout <<"You have "<< bag.count() <<" marbles in the bag\n";
                    break; //Yay I fixed the c++ library problem!
                    
                case(EXIT): return 0;
                default: cout << "Improper input.";
            }
    }while (option != 4);
}