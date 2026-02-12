#include <iostream>
#include <string>

using namespace std;

namespace StackLibrary {
    template <typename T>
    struct GrowingStack {
        T* data;        
        int top;        
        int capacity;   
        int maxLimit;   
    };

    template <typename T>
    inline bool isEmpty(const GrowingStack<T>& s) {
        return s.top == -1;
    }

    template <typename T>
    inline int currentSize(const GrowingStack<T>& s) {
        return s.top + 1;
    }
    template <typename T>
    void initialize(GrowingStack<T>& s, int initialSize, int maxSize = 100) {
        if (initialSize > maxSize) {
            cerr << "Error: Initial size cannot exceed max limit." << endl;
            initialSize = maxSize;
        }
        s.data = new T[initialSize]; 
        s.top = -1;
        s.capacity = initialSize;
        s.maxLimit = maxSize;
    }

    template <typename T>
    bool inflate(GrowingStack<T>& s) {
        const int limit = s.maxLimit;

        if (s.capacity >= limit) {
            return false;
        }

        int newCapacity = s.capacity * 2;
        if (newCapacity > limit) {
            newCapacity = limit;
        }

        cout << "[System]: Inflating capacity from " << s.capacity 
                  << " to " << newCapacity << ".\n";

        T* newData = new T[newCapacity];
        
        for (int i = 0; i <= s.top; i++) {
            newData[i] = s.data[i];
        }

        delete[] s.data; 
        s.data = newData;
        s.capacity = newCapacity;
        
        return true;
    }

    template <typename T>
    void push(GrowingStack<T>& s, T value) {
        if (s.top == s.capacity - 1) {
            if (!inflate(s)) {
                cout << "Error: Stack Overflow (Max limit reached).\n";
                return;
            }
        }
        s.data[++(s.top)] = value;
    }

    template <typename T>
    void push(GrowingStack<T>& s, const T* arr, int size) {
        for(int i = 0; i < size; i++) {
            push(s, arr[i]);
        }
    }

    template <typename T>
    T pop(GrowingStack<T>& s) {
        if (isEmpty(s)) {
            cout << "Error: Stack Underflow.\n";
            return T(); 
        }
        return s.data[(s.top)--];
    }

    template <typename T>
    void destroy(GrowingStack<T>& s) {
        if (s.data != nullptr) {
            delete[] s.data; 
            s.data = nullptr;
        }
        s.top = -1;
    }

    template <typename T>
    void printStack(const GrowingStack<T>& s) {
        cout << "[ ";
        for (int i = 0; i <= s.top; i++) {
            cout << s.data[i] << " ";
        }
        cout << "] (Size: " << currentSize(s) << "/" << s.capacity << ")\n";
    }
}
using namespace StackLibrary;

template <typename T>
void performStackDemo(string dataTypeName) {
    GrowingStack<T> stack;
    int initSize, maxLimit, count;

    cout << "\nGrowingStack for type: " << dataTypeName << "\n";

    cout << "Enter initial size and max limit: ";
    cin >> initSize >> maxLimit;
    initialize(stack, initSize, maxLimit);

    cout << "Enter the number of elements: ";
    cin >> count;

    cout << "Enter " << count << " elements ";
    if (dataTypeName == "Student Struct") cout << "(Format: ID Name): \n";
    else cout << ":\n";

    for (int i = 0; i < count; i++) {
        T val;
        cin >> val;
        push(stack, val);
    }

    cout << "Current Stack: ";
    printStack(stack);

    if (!isEmpty(stack)) {
        T val = pop(stack);
        cout << "Popped one element: " << val << endl;
        cout << "Stack after pop: ";
        printStack(stack);
    }

    destroy(stack);
}

int main() {
    //Integer
    performStackDemo<int>("int");

    //Float
    performStackDemo<float>("float");

    //String
    performStackDemo<string>("string");

    return 0;
}
