#include <iostream>

// FEATURE: Namespace
// Encapsulates the utility functions to prevent naming conflicts
namespace Utility {

    // FEATURE: Template Function
    // This defines a generic method that works for ANY data type T.
    // FEATURE: Call by Reference (T &a, T &b)
    // We pass references so we can modify the original variables directly.
    // FEATURE: Inline Function
    // Small logic suitable for inlining to improve performance.
    template <typename T>
    inline void swapValues(T &a, T &b) {
        T temp = a;
        a = b;
        b = temp;
    }
}

// A custom struct to demonstrate that the swap works on user-defined types
struct Point {
    int x;
    int y;
};

// FEATURE: Static Polymorphism / Function Overloading
// We overload the print function to handle different data types cleanly.
// FEATURE: Default Parameter
// The 'label' parameter has a default value if not provided.

// Overload for Double
void print(double val, std::string label = "Value") {
    std::cout << label << ": " << val << std::endl;
}

// Overload for Point (Struct)
void print(Point p, std::string label = "Point") {
    std::cout << label << ": (" << p.x << ", " << p.y << ")" << std::endl;
}

// FEATURE: Template for printing other simple types (int, short, float)
template <typename T>
void print(T val, std::string label = "Value") {
    std::cout << label << ": " << val << std::endl;
}

using namespace std;
using namespace Utility; // Bring our namespace into scope

int main() {
    cout << "=== Generic Swap Demonstration ===" << endl;

    // 1. Demonstrate INT
    int i1 = 10, i2 = 99;
    cout << "\n--- Integer Swap ---" << endl;
    print(i1, "Before A"); print(i2, "Before B");
    swapValues(i1, i2); // Calls template specialized for <int>
    print(i1, "After  A"); print(i2, "After  B");

    // 2. Demonstrate SHORT
    short s1 = 5, s2 = 20;
    cout << "\n--- Short Swap ---" << endl;
    print(s1, "Before A"); print(s2, "Before B");
    swapValues(s1, s2); // Calls template specialized for <short>
    print(s1, "After  A"); print(s2, "After  B");

    // 3. Demonstrate FLOAT
    float f1 = 1.5f, f2 = 4.5f;
    cout << "\n--- Float Swap ---" << endl;
    print(f1, "Before A"); print(f2, "Before B");
    swapValues(f1, f2); // Calls template specialized for <float>
    print(f1, "After  A"); print(f2, "After  B");

    // 4. Demonstrate DOUBLE
    double d1 = 100.123, d2 = 999.987;
    cout << "\n--- Double Swap ---" << endl;
    print(d1, "Before A"); print(d2, "Before B");
    swapValues(d1, d2); // Calls template specialized for <double>
    print(d1, "After  A"); print(d2, "After  B");

    // 5. Demonstrate STRUCT
    Point p1 = {1, 1};
    Point p2 = {10, 10};
    cout << "\n--- Struct Swap ---" << endl;
    print(p1, "Before A"); print(p2, "Before B");
    
    // The compiler automatically generates code to bitwise copy/swap the struct
    swapValues(p1, p2); 
    
    print(p1, "After  A"); print(p2, "After  B");

    return 0;
}
