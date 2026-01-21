#include<iostream>
#include<string>
using namespace std;

namespace StudSpace{
	struct student{
		string name;
		int age;
		string dep;
		int year;
	};
	void ReadStudentData(student &s){
		cout << "Enter name: ";
		getline(cin>>ws, s.name);
		cout << "Enter age: ";
		cin >> s.age;
		cout << "Department: ";
		getline(cin>>ws,s.dep);
		cout << "Year: ";
		cin >> s.year;
		cout<< endl;
	}

	void PrintStudentData(student &s){
		cout << "Name: "<<s.name <<endl;
		cout << "Age: "<<s.age << endl;
		cout << "Department: "<<s.dep << endl;
		cout << "Year: "<< s.year <<endl<<endl;
	}
}

using namespace StudSpace;

int main(){
	int n;
	cout << "Enter number of students: ";
	cin >> n;

	student* Arr = new student[n];
	for(int i=0; i<n; i++){
		cout << "Enter student's details: "<<endl;
		ReadStudentData(Arr[i]);
	}
	for(int i=0 ; i<n ;i++){
		PrintStudentData(Arr[i]);
	}

	return 0;
}
