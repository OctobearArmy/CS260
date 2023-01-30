#include <iostream>
#include <string>

#include "caller.h"
#include "queue.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

Caller addCaller() {
    string name;
    string phone;

    cout<< "Enter caller name"<< endl;
    cin >> name; 
    cout<< "Enter caller number"<< endl;
    cin >> phone;
    return Caller(name, phone);
}
    




int main() {
    Queue<Caller> queue;
    Caller caller(addCaller());
    
    queue.enqueue(caller);
    caller = queue.peek();
    cout << "Caller name : " << caller.name () << endl;
    cout << "caller phone: " << caller.phone() << endl;
    
    
    
    return 0;
}