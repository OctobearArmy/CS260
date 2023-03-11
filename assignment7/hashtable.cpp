#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Student {
public:
    string name;
    int age;
    string major;
    string id;

    Student(string name, int age, string major, string id) {
        this->name = name;
        this->age = age;
        this->major = major;
        this->id = id;
    }
};

class Hashtable {
private:
    static const int MAX_SIZE = 100;
    Student* data[MAX_SIZE];

public:
    Hashtable() {
        for (int i = 0; i < MAX_SIZE; i++) {
            data[i] = nullptr;
        }
    }

    int hash(string id) {
        int sum = 0;
        for (int i = 0; i < id.length(); i++) {
            sum += id[i];
        }
        return sum % MAX_SIZE;
    }

    void insert(Student* student) {
        int index = hash(student->id);
        while (data[index] != nullptr && data[index]->id != student->id) {
            index = (index + 1) % MAX_SIZE;
        }
        data[index] = student;
    }

    Student* find(string id) {
        int index = hash(id);
        while (data[index] != nullptr && data[index]->id != id) {
            index = (index + 1) % MAX_SIZE;
        }
        return data[index];
    }
};

int main() {
}
