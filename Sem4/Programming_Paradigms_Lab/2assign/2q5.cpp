#include <iostream>

template <typename T>
class GrowingStack {
    T* data;
    int capacity;
    int top;

public:
    GrowingStack(int size = 2) : capacity(size), top(-1) {
        data = new T[capacity];
    }

    void push(T val) {
        if (top == capacity - 1) {
        }
        data[++top] = val;
    }

    T pop() { return data[top--]; }
};

int main() {
    GrowingStack<int> iStack;
    GrowingStack<float> fStack;
    GrowingStack<char*> sStack;   
    sStack.push((char*)"Hello"); 
    return 0;
}