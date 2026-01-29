#include <iostream>
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

int main() {
    GrowingStack<int> stack1;
    GrowingStack<int> stack2;
    GrowingStack<int> stack3;

    initialize(stack1, 2, 10);
    initialize(stack2, 2, 10);
    initialize(stack3, 5, 20);

    cout << "\nPopulating Stack 1" << endl;
    push(stack1, 10);
    push(stack1, 20);
    push(stack1, 30); 
    push(stack1, 40);
    push(stack1, 50);
    cout << "Stack 1: "; printStack(stack1);

    cout << "\nPopulating Stack 2" << endl;
    int batch[] = {100, 200, 300};
    push(stack2, batch, 3); 
    cout << "Stack 2: "; printStack(stack2);

    cout << "\nMerging into Stack 3" << endl;
    
    int count = 1;
    while (!isEmpty(stack1) && !isEmpty(stack2)) {
        int val;
        if (count % 2 != 0) {
            val = pop(stack1); 
            cout << "Cnt " << count << " (Odd): Pop S1 (" << val << ") -> Push S3\n";
        } else {
            val = pop(stack2); 
            cout << "Cnt " << count << " (Even): Pop S2 (" << val << ") -> Push S3\n";
        }
        push(stack3, val);
        count++;
    }

    while (!isEmpty(stack1)) {
        int val = pop(stack1);
        cout << "Remaining S1 (" << val << ") -> Push S3\n";
        push(stack3, val);
    }

    while (!isEmpty(stack2)) {
        int val = pop(stack2);
        cout << "Remaining S2 (" << val << ") -> Push S3\n";
        push(stack3, val);
    }

    cout << "\n--- Final State ---" << endl;
    cout << "Stack 3: "; printStack(stack3);

    destroy(stack1);
    destroy(stack2);
    destroy(stack3);

    return 0;
}
