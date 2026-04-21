#include<iostream>
using namespace std;

class ComplexNum{
        private:
        double real,imag;

        public:
        ComplexNum(double r = 0, double i = 0):real(r),imag(i){}

        ComplexNum operator +(const ComplexNum &obj){
                return ComplexNum(real + obj.real , imag + obj.imag);
        }
        friend ComplexNum operator -(const ComplexNum &obj1,const ComplexNum &obj2){
                return ComplexNum(obj1.real - obj2.real , obj1.imag - obj2.imag);
        }

        void display(){
                cout<<real<< (imag >= 0?"+" :"-")<<(imag>=0? imag :-imag)<<"i"<<endl;
        }

};

int main(){
        ComplexNum n1(9);
        ComplexNum n2(5,4);
        ComplexNum result;
        int choice;
        n1.display();
        n2.display();

        do{
                cout<<"1. Addition"<<endl;
                cout<<"2. Subtraction"<<endl;
                cout<<"3. Exit"<<endl;
                cout<< "Enter your choice: "<<endl;
                cin>> choice;

                switch(choice){
                        case 1:
                                result = n1 + n2;
                                result.display();
                                break;
                        case 2:
                                result = n1-n2;
                                result.display();
                                break;
                        case 3:
                                cout<<"Exiting Program"<<endl;
                                break;
                        default:
                                cout<<"Invalid choice"<<endl;
                }
        }while(choice != 3);

        return 0;
}
