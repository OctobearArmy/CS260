#include <iostream>
#include <string>

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

  Student(string name, int age, string major, string id)
  {
    this->name = name;
    this->age = age;
    this->major = major;
    this->id = id;
  }

  int hash() { return ::hash(id); }
};
//============================================================================//

//============================================================================//
class Hashtable
{
private:
  static const int MAX_SIZE = 101;
  Student *data[MAX_SIZE];

public:
  Hashtable()
  {
    for (int i = 0; i < MAX_SIZE; i++)
    {
      data[i] = nullptr;
    }
  }
//----------------------------------------------------------------------------//

  int hash(Student *student)
  {
    return student->hash() % MAX_SIZE;
  }
//----------------------------------------------------------------------------//

  int hash(const string &key)
  {
    return ::hash(key) % MAX_SIZE;
  }
//----------------------------------------------------------------------------//

  void insert(Student *student)
  {
    int idx = hash(student);

    delete data[idx];
    data[idx] = student;
  }
//----------------------------------------------------------------------------//

  Student *find(const string &id)
  {
    return data[hash(id)];
  }
//----------------------------------------------------------------------------//

  void printAll() {
    for (int idx = 0; idx < MAX_SIZE; idx++) {
      Student *s = data[idx];
      if (s) {
        printf("Hash index: %d\n", idx);
        printf("   Student: name='%-32s' id=%s\n", s->name.c_str(), s->id.c_str());
      }
    }
  }
};
//============================================================================//
//----------------------------------------------------------------------------//

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
    do
    {
    print_menu();
    cin >> choice;

    switch (choice)
    {
        case 1:
        {
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

            Student *student = new Student(name, age, major, id);
            table.insert(student);
            cout << "Student added to hashtable" << endl;

            break;
        }
        case 2:
        {
            string id;
            cout << "Enter student ID to find: ";
            cin >> id;

            Student *student = table.find(id);
            if (student)
            {
                cout << "Student found:" << endl;
                cout << "Name: " << student->name << endl;
                cout << "Age: " << student->age << endl;
                cout << "Major: " << student->major << endl;
                cout << "ID: " << student->id << endl;
            }
            else
            {
                cout << "Student not found" << endl;
            }

            break;
        }
        case 3: {
        table.printAll();
        break;
        }
        case 4:
        {
            cout << "Goodbye!" << endl;
            break;
        }
        default:
        {
            cout << "Invalid choice" << endl;
            break;
        }
    }

    } while (choice != 4);
 
  return 0;
}
