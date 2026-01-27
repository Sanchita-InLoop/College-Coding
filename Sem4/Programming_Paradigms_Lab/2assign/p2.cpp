#include <iostream>

// FEATURE: Namespace
// Encapsulating the stack related code to avoid name collisions
namespace StackLibrary {

    // FEATURE: Template (Struct)
    // Using a template struct allows the stack to hold any data type, 
    // though we will use 'int' in main() as per requirements.
    template <typename T>
    struct GrowingStack {
        T* data;        // Pointer to dynamic array
        int top;        // Index of top element
        int capacity;   // Current memory size
        int maxLimit;   // Hard upper bound
    };

    // FEATURE: Inline Function
    // Inline functions for small, frequently called logic to reduce function call overhead.
    template <typename T>
    inline bool isEmpty(const GrowingStack<T>& s) {
        return s.top == -1;
    }

    template <typename T>
    inline int currentSize(const GrowingStack<T>& s) {
        return s.top + 1;
    }

    // FEATURE: Default Parameter
    // The maxSize has a default value of 100 if not provided by the caller.
    // FEATURE: Call by Reference
    // We pass the struct by reference to modify the actual object, not a copy.
    template <typename T>
    void initialize(GrowingStack<T>& s, int initialSize, int maxSize = 100) {
        if (initialSize > maxSize) {
            std::cerr << "Error: Initial size cannot exceed max limit." << std::endl;
            initialSize = maxSize;
        }

        // FEATURE: Standard Input/Output (std::cerr, std::cout - used throughout)
        // Memory allocation using 'new' (C++ style) instead of malloc
        s.data = new T[initialSize]; 
        s.top = -1;
        s.capacity = initialSize;
        s.maxLimit = maxSize;
    }

    // FEATURE: Reference variables (param 's')
    template <typename T>
    bool inflate(GrowingStack<T>& s) {
        // FEATURE: Constant
        // Using const to ensure safety of comparison variables
        const int limit = s.maxLimit;

        if (s.capacity >= limit) {
            return false;
        }

        int newCapacity = s.capacity * 2;
        if (newCapacity > limit) {
            newCapacity = limit;
        }

        std::cout << "[System]: Inflating capacity from " << s.capacity 
                  << " to " << newCapacity << ".\n";

        // C++ way to reallocate: new buffer -> copy -> delete old
        T* newData = new T[newCapacity];
        
        for (int i = 0; i <= s.top; i++) {
            newData[i] = s.data[i];
        }

        delete[] s.data; // Free old memory
        s.data = newData;
        s.capacity = newCapacity;
        
        return true;
    }

    // FEATURE: Static Polymorphism / Function Overloading (1 of 2)
    // Push a single element
    template <typename T>
    void push(GrowingStack<T>& s, T value) {
        if (s.top == s.capacity - 1) {
            // Try to inflate
            if (!inflate(s)) {
                std::cout << "Error: Stack Overflow (Max limit reached).\n";
                return;
            }
        }
        s.data[++(s.top)] = value;
    }

    // FEATURE: Static Polymorphism / Function Overloading (2 of 2)
    // Push an array of elements (Batch push)
    template <typename T>
    void push(GrowingStack<T>& s, const T* arr, int size) {
        for(int i = 0; i < size; i++) {
            push(s, arr[i]);
        }
    }

    template <typename T>
    T pop(GrowingStack<T>& s) {
        if (isEmpty(s)) {
            std::cout << "Error: Stack Underflow.\n";
            // Return a default constructed value (0 for int)
            return T(); 
        }
        return s.data[(s.top)--];
    }

    template <typename T>
    void destroy(GrowingStack<T>& s) {
        if (s.data != nullptr) {
            delete[] s.data; // Prevent memory leak
            s.data = nullptr;
        }
        s.top = -1;
    }

    // Helper to view stack
    template <typename T>
    void printStack(const GrowingStack<T>& s) {
        std::cout << "[ ";
        for (int i = 0; i <= s.top; i++) {
            std::cout << s.data[i] << " ";
        }
        std::cout << "] (Size: " << currentSize(s) << "/" << s.capacity << ")\n";
    }
}

// Using the namespace
using namespace StackLibrary;
using namespace std;

int main() {
    cout << "=== C++ GrowingStack Demo ===" << endl;

    // We instantiate the template for integers
    GrowingStack<int> stack1;
    GrowingStack<int> stack2;
    GrowingStack<int> stack3;

    // Initialize with different sizes
    // Stack 1: Start size 2, Max 10
    initialize(stack1, 2, 10);
    // Stack 2: Start size 2, Max 10
    initialize(stack2, 2, 10);
    // Stack 3: Start size 5, Max 20 (Using Default Param for Max? No, explicit here)
    initialize(stack3, 5, 20);

    // Populate Stack 1
    cout << "\n--- Populating Stack 1 ---" << endl;
    push(stack1, 10);
    push(stack1, 20);
    push(stack1, 30); // Triggers inflation
    push(stack1, 40);
    push(stack1, 50);
    cout << "Stack 1: "; printStack(stack1);

    // Populate Stack 2 using Overloaded Push (Batch)
    cout << "\n--- Populating Stack 2 ---" << endl;
    int batch[] = {100, 200, 300};
    push(stack2, batch, 3); // Triggers inflation
    cout << "Stack 2: "; printStack(stack2);

    // Logic: Merge into Stack 3
    // Odd count -> from Stack 1, Even count -> from Stack 2
    cout << "\n--- Merging into Stack 3 ---" << endl;
    
    int count = 1;
    while (!isEmpty(stack1) && !isEmpty(stack2)) {
        int val;
        if (count % 2 != 0) {
            val = pop(stack1); // Odd
            cout << "Cnt " << count << " (Odd): Pop S1 (" << val << ") -> Push S3\n";
        } else {
            val = pop(stack2); // Even
            cout << "Cnt " << count << " (Even): Pop S2 (" << val << ") -> Push S3\n";
        }
        push(stack3, val);
        count++;
    }

    // Handle remaining elements in Stack 1
    while (!isEmpty(stack1)) {
        int val = pop(stack1);
        cout << "Remaining S1 (" << val << ") -> Push S3\n";
        push(stack3, val);
    }

    // Handle remaining elements in Stack 2
    while (!isEmpty(stack2)) {
        int val = pop(stack2);
        cout << "Remaining S2 (" << val << ") -> Push S3\n";
        push(stack3, val);
    }

    cout << "\n--- Final State ---" << endl;
    cout << "Stack 3: "; printStack(stack3);

    // Cleanup to prevent memory leaks
    destroy(stack1);
    destroy(stack2);
    destroy(stack3);

    return 0;
}
