#include <iostream>
#include <string>

#include "caller.h"
#include "queue.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

Queue<Caller> __queue;

//----------------------------------------------------------------------------//
void addCaller(string name, string phone) {
   __queue.enqueue(Caller(name, phone));
}
//----------------------------------------------------------------------------//
void addCaller() {
    string name;
    string phone;

    cout << "Enter new caller:" << endl;
    cout << "Enter caller name:"<< endl;
    cin  >> name; 
    cout << "Enter caller number:"<< endl;
    cin  >> phone;
    addCaller(name, phone);
} 
//----------------------------------------------------------------------------//
bool peekCaller() {
    if (__queue.isEmpty()) {
        cout << "ERROR: Queue is empty." << endl;
        return false;
    }
    Caller caller(__queue.peek());
    cout << "Caller at front:" << endl;
    cout << "   Caller name : " << caller.name () << endl;
    cout << "   Caller phone: " << caller.phone() << endl;
    return true;
}
//----------------------------------------------------------------------------//
bool removeCaller() {   // O(1)
    if (__queue.isEmpty()) {
        cout << "ERROR: Queue is empty." << endl;
        return false;
    }
    Caller caller(__queue.dequeue());
    cout << "Removed front  :" << endl;
    cout << "   Caller name : " << caller.name () << endl;
    cout << "   Caller phone: " << caller.phone() << endl;
    return true;
}
//----------------------------------------------------------------------------//
int main() {
    Caller caller;

    addCaller("Sarah", "541-926-3443");
    addCaller("Wendy", "208-453-1314");
    addCaller("Steve", "801-978-4356");
    
    peekCaller();
    addCaller();

    removeCaller();
    removeCaller();
    removeCaller();
    removeCaller();
    removeCaller();
    return 0;
}
//----------------------------------------------------------------------------//
