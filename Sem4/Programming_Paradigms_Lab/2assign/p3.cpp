#include <iostream>
using namespace std;

namespace myNamespace {
    template <typename T>
    inline void swapValues(T &a, T &b) {
        T temp = a;
        a = b;
        b = temp;
    }
}
using namespace myNamespace;

struct Point {
    int x;
    int y;
};

void print(double val, string label = "Value") {
    cout << label << ": " << val << endl;
}

void print(Point p, string label = "Point") {
    cout << label << ": (" << p.x << ", " << p.y << ")" << endl;
}

template <typename T>
void print(T val, string label = "Value") {
    cout << label << ": " << val << endl;
}

int main() {
    int i1, i2;
    cout << "Enter two integers: ";
    cin >> i1 >> i2;

    cout << "\nInteger Swap" << endl;
    print(i1, "Before A"); print(i2, "Before B");
    swapValues(i1, i2); 
    print(i1, "After  A"); print(i2, "After  B");

    short s1, s2;
    cout << "\nEnter two short integers: ";
    cin >> s1 >> s2;

    cout << "\nShort Swap" << endl;
    print(s1, "Before A"); print(s2, "Before B");
    swapValues(s1, s2); 
    print(s1, "After  A"); print(s2, "After  B");

    float f1, f2;
    cout << "\nEnter two floats: ";
    cin >> f1 >> f2;

    cout << "\nFloat Swap" << endl;
    print(f1, "Before A"); print(f2, "Before B");
    swapValues(f1, f2); 
    print(f1, "After  A"); print(f2, "After  B");

    double d1, d2;
    cout << "\nEnter two doubles: ";
    cin >> d1 >> d2;

    cout << "\nDouble Swap" << endl;
    print(d1, "Before A"); print(d2, "Before B");
    swapValues(d1, d2); 
    print(d1, "After  A"); print(d2, "After  B");

    Point p1, p2;
    cout << "\nEnter x and y for Point 1: ";
    cin >> p1.x >> p1.y;
    cout << "Enter x and y for Point 2: ";
    cin >> p2.x >> p2.y;

    cout << "\nStruct Swap" << endl;
    print(p1, "Before A"); print(p2, "Before B");
    
    swapValues(p1, p2); 
    
    print(p1, "After  A"); print(p2, "After  B");

    return 0;
}
