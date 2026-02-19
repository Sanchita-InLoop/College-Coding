#include <iostream>

using namespace std;

namespace MemoryManagement
{
    class GrowingStack
    {
    private:
        int *data;
        int top_index;
        int current_bound;
        int limit;

        bool full() const {
            return top_index == current_bound - 1;
        }

    public:
        GrowingStack(int max_len, int start_size)
        {
            limit = max_len;
            current_bound = start_size;
            top_index = -1;
            data = new int[current_bound];
        }

        ~GrowingStack()
        {
            if (data != nullptr) {
                delete[] data;
            }
        }

        GrowingStack(const GrowingStack &source)
        {
            limit = source.limit;
            current_bound = source.current_bound;
            top_index = source.top_index;
            
            data = new int[current_bound];
            for (int i = 0; i <= top_index; i++) {
                data[i] = source.data[i];
            }
            cout << "Event: Copy Constructor Triggered" << endl;
        }

        GrowingStack& operator=(const GrowingStack &source)
        {
            if (this != &source) 
            {
                delete[] data; 

                limit = source.limit;
                current_bound = source.current_bound;
                top_index = source.top_index;

                data = new int[current_bound];
                for (int i = 0; i <= top_index; i++) {
                    data[i] = source.data[i];
                }
            }
            cout << "Event: Assignment Operator Triggered" << endl;
            return *this;
        }

        bool inflate()
        {
            if (current_bound >= limit) {
                return false; 
            }

            int expanded_size = current_bound + 5; 
            if (expanded_size > limit) {
                expanded_size = limit;
            }

            int *temp_buffer = new int[expanded_size];
            for (int i = 0; i <= top_index; ++i) {
                temp_buffer[i] = data[i];
            }

            delete[] data;
            data = temp_buffer;
            current_bound = expanded_size;

            cout << "Expansion: Capacity increased to " << current_bound << endl;
            return true;
        }

        void push(int value)
        {
            if (full()) {
                if (!inflate()) {
                    cout << "Overflow: Cannot push " << value << ". Limit reached." << endl;
                    return;
                }
            }
            data[++top_index] = value;
        }

        void push(int values[], int total)
        {
            for (int i = 0; i < total; i++) {
                push(values[i]);
            }
        }

        int pop()
        {
            if (isEmpty()) {
                cout << "Underflow: Stack is empty" << endl;
                return -1;
            }
            return data[top_index--];
        }

        bool isEmpty() const {
            return top_index == -1;
        }

        int currentSize() const {
            return top_index + 1;
        }

        int getMaxSize() const {
            return limit;
        }
    };
}

int main()
{
    using MemoryManagement::GrowingStack;

    int mSize, iSize, numCount;

    cout << "Setting up Stack A:" << endl;
    cout << "Max Limit: "; cin >> mSize;
    cout << "Starting Size: "; cin >> iSize;
    GrowingStack* stack1 = new GrowingStack(mSize, iSize);

    cout << "Elements to add to Stack A: "; cin >> numCount;
    if (numCount > 0) {
        int* buffer = new int[numCount];
        cout << "Enter values: ";
        for (int i = 0; i < numCount; i++) cin >> buffer[i];
        stack1->push(buffer, numCount);
        delete[] buffer;
    }

    cout << "\nSetting up Stack B:" << endl;
    cout << "Max Limit: "; cin >> mSize;
    cout << "Starting Size: "; cin >> iSize;
    GrowingStack* stack2 = new GrowingStack(mSize, iSize);

    cout << "Elements to add to Stack B: "; cin >> numCount;
    if (numCount > 0) {
        int* buffer = new int[numCount];
        cout << "Enter values: ";
        for (int i = 0; i < numCount; i++) cin >> buffer[i];
        stack2->push(buffer, numCount);
        delete[] buffer;
    }

    GrowingStack* stack3 = new GrowingStack(stack1->getMaxSize() + stack2->getMaxSize(), 5);

    cout << "\nMerging A and B into Stack C..." << endl;
    int turn = 1;
    while (!stack1->isEmpty() && !stack2->isEmpty()) {
        if (turn % 2 != 0) {
            stack3->push(stack1->pop());
        } else {
            stack3->push(stack2->pop());
        }
        turn++;
    }

    while (!stack1->isEmpty()) stack3->push(stack1->pop());
    while (!stack2->isEmpty()) stack3->push(stack2->pop());

    cout << "\nDemonstrating Copy Semantics:" << endl;
    GrowingStack stack4 = *stack3;
    cout << "Created Stack 4 via Copy. Top of 4: " << stack4.pop() << endl;

    GrowingStack stack5(50, 5);
    stack5 = stack4;
    cout << "Assigned 4 to 5. Top of 5: " << stack5.pop() << endl;

    cout << "\nEmptying Stack C: ";
    while (!stack3->isEmpty()) {
        cout << stack3->pop() << " ";
    }
    cout << endl;

    delete stack1;
    delete stack2;
    delete stack3;

    return 0;
}
