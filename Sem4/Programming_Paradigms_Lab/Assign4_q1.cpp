#include <iostream>
#include <string>

using namespace std;

namespace Academy {

    class Student {
    private:
        string name;
        int age;
        string department;
        int year;

    public:
        Student() {
            name = "Unknown";
            age = 0;
            department = "None";
            year = 0;
        }

        void ReadStudentData() {
            cout << "Name: ";
            getline(cin >> ws, name);
            
            cout << "Age: ";
            cin >> age;
            
            cout << "Department: ";
            getline(cin >> ws, department);
            
            cout << "Year: ";
            cin >> year;
        }

        void PrintStudentData() const {
            cout << "Student:    " << name << endl;
            cout << "Age:        " << age << endl;
            cout << "Department: " << department << endl;
            cout << "Year:       " << year << endl;
        }
    };
}

int main() {
    int n;
    cout << "Enter the total number of students to record: ";
    cin >> n;

    Academy::Student* studentArray = new Academy::Student[n];

    for (int i = 0; i < n; ++i) {
        cout << "\nInputting data for Student #" << (i + 1) << ":" << endl;
        studentArray[i].ReadStudentData();
    }

    cout << "\nREGISTERED STUDENT LIST" << endl;
    for (int i = 0; i < n; ++i) {
        studentArray[i].PrintStudentData();
    }

    delete[] studentArray;
    
    return 0;
}
