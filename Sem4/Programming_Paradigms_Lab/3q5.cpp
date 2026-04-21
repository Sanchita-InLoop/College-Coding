#include <iostream>
#include <stdexcept>

using namespace std;

namespace StackSystem {
    class GrowingStack {
    private:
        int *elements;
        int top;
        int capacity;
        int max_capacity;


        static int stackCount;
        static const int MAX_STACKS = 3;

        bool isFull() const { return top == capacity - 1; }

    public:

        GrowingStack(int max_limit, int initial_size) {

            if (stackCount >= MAX_STACKS) {
                cout << "Error: Maximum number of stacks reached!\n";
                exit(1);
            }

            this->max_capacity = max_limit;
            this->capacity = initial_size;
            this->top = -1;
            this->elements = new int[this->capacity];

            stackCount++;
            cout << "Stack created. Current stack count: " << stackCount << endl;
        }

        ~GrowingStack() {
            if (elements != nullptr) {
                delete[] elements;
                elements = nullptr;
                stackCount--;
                cout << "Stack destroyed. Current stack count: " << stackCount << endl;
            }
        }

        GrowingStack(const GrowingStack &other) {
            if (stackCount >= MAX_STACKS) {
                cout<< "Error: Cannot copy. Max stacks reached!\n";
                exit(1);
            }
            this->max_capacity = other.max_capacity;
            this->capacity = other.capacity;
            this->top = other.top;
            this->elements = new int[this->capacity];
            for (int i = 0; i <= this->top; i++) {
                this->elements[i] = other.elements[i];
            }
            stackCount++;
            cout << ">> Copy Constructor called. Count: " << stackCount << endl;
        }

        GrowingStack& operator=(const GrowingStack &other)
        {
            if (this != &other)
            {
                delete[] elements;

                this->max_capacity = other.max_capacity;
                this->capacity = other.capacity;
                this->top = other.top;

                this->elements = new int[this->capacity];
                for (int i = 0; i <= this->top; i++) {
                    this->elements[i] = other.elements[i];
                }
            }
            cout << ">> Assignment Operator called.\n";
            return *this;
        }

        bool inflate()
        {
            if (capacity >= max_capacity) {
                return false;
            }

            int new_capacity = capacity * 2;
            if (new_capacity > max_capacity) {
                new_capacity = max_capacity;
            }

            int *new_elements = new int[new_capacity];

            for (int i = 0; i <= top; ++i) {
                new_elements[i] = elements[i];
            }

            delete[] elements;
            elements = new_elements;
            capacity = new_capacity;

            cout << "!!! Stack inflated. New Capacity: " << capacity << "\n";
            return true;
        }

        void push(int val)
        {
            if (isFull()) {
                if (!inflate()) {
                    cout << "Error: Stack Overflow (Max limit of " << max_capacity << " reached)\n";
                    return;
                }
            }
            elements[++top] = val;
        }

        void push(int inputs[], int count)
        {
            for (int i = 0; i < count; i++) {
                push(inputs[i]);
            }
            cout << "Pushed " << count << " elements.\n";
        }

        int pop()
        {
            if (isEmpty()) {
                cout << "Error: Stack Underflow\n";
                return -1;
            }
            return elements[top--];
        }

        bool isEmpty() const {
            return top == -1;
        }

        int currentSize() const {
            return top + 1;
        }

        int getMaxSize() const {
            return max_capacity;
        }

        static int getCount() { return stackCount; }
    };

    int GrowingStack::stackCount = 0;
}

int main() {
    using namespace StackSystem;
        GrowingStack s1(100, 10);
        GrowingStack s2(100, 10);
        GrowingStack s3(100, 10);

        GrowingStack s4(100, 10);
    return 0;
}
