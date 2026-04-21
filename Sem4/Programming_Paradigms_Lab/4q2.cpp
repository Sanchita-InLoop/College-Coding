#include <iostream>
#include <string>

using namespace std;

class Staff {
protected:
    string name;
    int age;
    string gender;

public:
    Staff(string n, int a, string g) : name(n), age(a), gender(g) {}
    virtual ~Staff() {}
    
    virtual void displayProfile() const {
        cout << "Name: " << name << "\nAge: " << age << "\nGender: " << gender << endl;
    }
};

class EmployeeDetails : public Staff {
protected:
    string empID;
    double money; // (Salary or Stipend)

public:
    EmployeeDetails(string n, int a, string g, string id, double m)
        : Staff(n, a, g), empID(id), money(m) {}
};

class TechDept : public EmployeeDetails {
protected:
    string department;
    string skillSet;

public:
    TechDept(string n, int a, string g, string id, double m, string dept, string skills)
        : EmployeeDetails(n, a, g, id, m), department(dept), skillSet(skills) {}
};

class Developer : public TechDept {
private:
    string project;
    int yoe;

public:
    Developer(string n, int a, string g, string id, double sal, string dept, string skills, string proj, int exp)
        : TechDept(n, a, g, id, sal, dept, skills), project(proj), yoe(exp) {}

    void displayProfile() const override {
        cout << "Developer Profile: \n" << endl;
        Staff::displayProfile();
        cout << "EmpID: " << empID << " | Dept: " << department << endl;
        cout << "Salary: $" << money << " | Skills: " << skillSet << endl;
        cout << "Project: " << project << " | Experience: " << yoe << " yrs" << endl << endl;
    }
};

class SystemAdmin : public EmployeeDetails {
private:
    string workLoad;

public:
    SystemAdmin(string n, int a, string g, string id, double sal, string load)
        : EmployeeDetails(n, a, g, id, sal), workLoad(load) {}

    void displayProfile() const override {
        cout << "System Admin Profile: \n" << endl;
        Staff::displayProfile();
        cout << "EmpID: " << empID << " | Salary: $" << money << endl;
        cout << "Workload: " << workLoad << endl << endl;
    }
};

class Trainee : public TechDept {
private:
    string duration;

public:
    Trainee(string n, int a, string g, string dept, string skills, string dur, double stip)
        : TechDept(n, a, g, "N/A", stip, dept, skills), duration(dur) {}

    void displayProfile() const override {
        cout << "Trainee Profile: \n" << endl;
        Staff::displayProfile();
        cout << "Dept: " << department << " | Stipend: $" << money << endl;
        cout << "Duration: " << duration << " | Skills: " << skillSet << endl << endl;
    }
};

int main() {
    const int MAX_STAFF = 3;
    Staff* directory[MAX_STAFF];

    directory[0] = new Developer(
        "Sizuka", 32, "Female", "DEV-8842", 125000, 
        "FinTech Core", "Java, Spring Boot, PostgreSQL", "Global Payment Gateway", 9
    );

    directory[1] = new SystemAdmin(
        "Jordan Jakhar", 28, "Male", "SYS-1029", 92000, 
        "Critical (AWS Cluster Management & On-call)"
    );

    directory[2] = new Trainee(
        "Sanchita Gupta", 22, "Female", 
        "Web Dev", "HTML, CSS, JS", "6 Months", 5500
    );
    
    cout << "\nHIERARCHICAL MANAGEMENT SYSTEM\n" << endl;

    for (int i = 0; i < MAX_STAFF; i++) {
        directory[i]->displayProfile();
    }

    for (int i = 0; i < MAX_STAFF; i++) {
        delete directory[i];
    }

    return 0;
}