#ifndef CALLER_H__
#define CALLER_H__

#include <string>

using std::string;

//============================================================================//
class Caller {
    private:
        string name_;
        string phone_;

    public:
        Caller() { }
        Caller(string name, string phone) {
            name_  = name;
            phone_ = phone;
        }
        
        string name () { return name_; };
        string phone() { return phone_; };
};
//============================================================================//

#endif // ifndef CALL_H__