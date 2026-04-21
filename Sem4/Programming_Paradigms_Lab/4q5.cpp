#include <iostream>
#include <string>

using namespace std;

class Shape {
public:
    virtual ~Shape() {}
    virtual double getArea() = 0;
    virtual void display() = 0;
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    double getArea() override { return 3.14159 * radius * radius; }
    void display() override { cout << "Circle (Radius: " << radius << ")"; }
};

class Rectangle : public Shape {
    double w, h;
public:
    Rectangle(double width, double height) : w(width), h(height) {}
    double getArea() override { return w * h; }
    void display() override { cout << "Rectangle (" << w << "x" << h << ")"; }
};

class Triangle : public Shape {
    double b, h;
public:
    Triangle(double base, double height) : b(base), h(height) {}
    double getArea() override { return 0.5 * b * h; }
    void display() override { cout << "Triangle (Base: " << b << ", Height: " << h << ")"; }
};

class ShapeStack {
private:
    Shape** stackArray;
    int capacity;
    int top;

    ShapeStack(const ShapeStack&) = delete;
    ShapeStack& operator=(const ShapeStack&) = delete;

public:
    ShapeStack(int size) {
        capacity = size;
        stackArray = new Shape*[capacity];
        top = -1;
    }

    ~ShapeStack() {
        while (top != -1) {
            delete stackArray[top--];
        }
        delete[] stackArray;
    }

    void Push(Shape* s) {
        if (s == nullptr) return;

        if (top < capacity - 1) {
            stackArray[++top] = s;
        } else {
            cout << "Stack Overflow: Cannot add more shapes." << endl;
            delete s;
        }
    }

    Shape* Pop() {
        if (top == -1) {
            cout << "Stack Underflow" << endl;
            return nullptr;
        }
        Shape* temp = stackArray[top];
        stackArray[top--] = nullptr; 
        return temp;
    }

    void Display() {
        if (top == -1) {
            cout << "Stack is empty." << endl;
            return;
        }
        for (int i = top; i >= 0; i--) {
            stackArray[i]->display();
            cout << " - Area: " << stackArray[i]->getArea() << endl;
        }
    }

    double TotalAreaCovered() {
        double total = 0;
        for (int i = 0; i <= top; i++) {
            total += stackArray[i]->getArea();
        }
        return total;
    }
};

int main() {
    ShapeStack myStack(4);

    myStack.Push(new Circle(5));
    myStack.Push(new Rectangle(4, 5));
    myStack.Push(new Triangle(3, 6));
   
    myStack.Push(new Circle(10));

    cout << "Current Stack" << endl;
    myStack.Display();

    cout << "\nTotal Area: " << myStack.TotalAreaCovered() << endl;

    cout << "\nPopping top element..." << endl;
    Shape* removed = myStack.Pop();
    if (removed != nullptr) {
        cout << "Removed: ";
        removed->display();
        cout << endl;
        delete removed; 
    }

    return 0;
}