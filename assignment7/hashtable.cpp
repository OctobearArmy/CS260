#include <iostream>
#include <string>

#include "node.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

//----------------------------------------------------------------------------//
int hash(const string &str)
{
  int sum = 0;
  for (int i = 0; i < (int)str.length(); i++)
  {
    sum += str[i] * (i + 1); // multiply by index to lessen collision chance
  }
  return sum;
}
//----------------------------------------------------------------------------//

//============================================================================//
class Student
{
public:
  string name;
  int age;
  string major;
  string id;

  Student() { }

  Student(string name, int age, string major, string id)
  {
    this->name = name;
    this->age = age;
    this->major = major;
    this->id = id;
  }

  string key() { return id; }

  int hash() { return ::hash(id); }
};
//============================================================================//

//============================================================================//
class Hashtable
{
private:
  typedef Node<Student> N_;

  static const int MAX_SIZE = 101;
  N_ *data[MAX_SIZE];
//  int num;

public:
  Hashtable()
  {
    for (int i = 0; i < MAX_SIZE; i++)
    {
      data[i] = nullptr;
    }
//    num = 0;
  }
//----------------------------------------------------------------------------//

  int hash(Student &student)
  {
    return student.hash() % MAX_SIZE;
  }
  
  int hash(const string &key)
  {
    return ::hash(key) % MAX_SIZE;
  }
//----------------------------------------------------------------------------//

  Student *find(const string &key) //only shows the latest value in the idx if you wanna see the chain use printAll.
  {
    N_ *node  = data[hash(key)];
    while (node != nullptr && node->value.key() != key)
    {
      node = node->next;
    }
    return (node ? &(node->value) : nullptr);
  }
//----------------------------------------------------------------------------//

  void insert(Student &student)
  {
    int index = hash(student);
    N_ *node  = data[index];
    
    data[index] = new N_(student, node);
  }
//----------------------------------------------------------------------------//

  void printAll() {
    for (int idx = 0; idx < MAX_SIZE; idx++) {
      N_ *node = data[idx];
      if (node) {
        printf("Hash index: %d\n", idx);
        while (node) {
          printf("   Student: name='%-32s' id=%s\n", node->value.name.c_str(), node->value.id.c_str());
          node = node->next;
        }
      }
    }
  }
/*
  void insert(Student *student)
  {
    int index = hash(student);
    int incr  = 1;
    while (data[index] != nullptr && data[index]->key() != student->key())
    {
      index = (index + incr) % MAX_SIZE;
      if (incr < MAX_SIZE / 2) incr *= 2;
    }
    data[index] = student;
//    num++;
  }
//----------------------------------------------------------------------------//

  Student *find(const string &key)
  {
    int index = ::hash(key);
    int incr  = 1;
    while (data[index] != nullptr && data[index]->key() != key)
    {
      index = (index + 1) % MAX_SIZE;
      if (incr < MAX_SIZE / 2) incr *= 2;
    }
    return data[index];
  }
*/
};
//============================================================================//

void print_menu() {
    cout << "Hashtable Menu:" << endl;
    cout << "1. Insert Student" << endl;
    cout << "2. Find Student" << endl;
    cout << "3. Show All" << endl;
    cout << "4. Quit" << endl;
    cout << "Choose an option: ";
}
//----------------------------------------------------------------------------//

int main()
{
  Hashtable table;

  int choice;
  do {
    print_menu();
    cin >> choice;

    switch (choice) {
      case 1: {
      string name, major, id;
      int age;

      cout << "Enter student name: ";
      cin >> name;
      cout << "Enter student age: ";
      cin >> age;
      cout << "Enter student major: ";
      cin >> major;
      cout << "Enter student ID: ";
      cin >> id;

      Student student(name, age, major, id);
      table.insert(student);
      cout << "Student added to hashtable" << endl;

      break;
      }
      case 2: {
        string id;
        cout << "Enter student ID to find: ";
        cin >> id;

        Student *student = table.find(id);
        if (student != nullptr) {
          cout << "Student found:" << endl;
          cout << "Name: " << student->name << endl;
          cout << "Age: " << student->age << endl;
          cout << "Major: " << student->major << endl;
          cout << "ID: " << student->id << endl;
        }
          else{cout << "Student not found" << endl; }

          break;
      }
      case 3: {
        table.printAll();
        break;
      }
      case 4: {
        cout << "Goodbye!" << endl;
        break;
      }
      default: {
        cout << "Invalid choice" << endl;
        break;
      }
    }

  } while (choice != 4);

return 0;
}
