#include <iostream>
#include <string>

using namespace std;

namespace GenericSystems
{
    template <typename T>
    class GrowingStack
    {
    private:
        T *container;
        int index;
        int current_limit;
        int absolute_max;

        bool is_full() const {
            return index == current_limit - 1;
        }

    public:
        GrowingStack(int max_len, int start_size)
        {
            absolute_max = max_len;
            current_limit = start_size;
            index = -1;
            container = new T[current_limit];
        }

        ~GrowingStack()
        {
            if (container != nullptr) {
                delete[] container;
            }
        }

        GrowingStack(const GrowingStack &src)
        {
            absolute_max = src.absolute_max;
            current_limit = src.current_limit;
            index = src.index;
            
            container = new T[current_limit];
            for (int i = 0; i <= index; i++) {
                container[i] = src.container[i];
            }
            cout << "Copying Stack Instance" << endl;
        }

        GrowingStack& operator=(const GrowingStack &src)
        {
            if (this != &src) 
            {
                delete[] container; 

                absolute_max = src.absolute_max;
                current_limit = src.current_limit;
                index = src.index;

                container = new T[current_limit];
                for (int i = 0; i <= index; i++) {
                    container[i] = src.container[i];
                }
            }
            cout << "Assigning Stack Content" << endl;
            return *this;
        }

        bool inflate()
        {
            if (current_limit >= absolute_max) {
                return false; 
            }

            int next_size = current_limit + 2; 
            if (next_size > absolute_max) {
                next_size = absolute_max;
            }

            T *new_buffer = new T[next_size];
            for (int i = 0; i <= index; ++i) {
                new_buffer[i] = container[i];
            }

            delete[] container;
            container = new_buffer;
            current_limit = next_size;

            cout << "Stack expanded to " << current_limit << endl;
            return true;
        }

        void push(T val)
        {
            if (is_full()) {
                if (!inflate()) {
                    cout << "Overflow: Max limit reached" << endl;
                    return;
                }
            }
            container[++index] = val;
        }

        T pop()
        {
            if (isEmpty()) {
                cout << "Underflow: Stack is empty" << endl;
                return T(); 
            }
            return container[index--];
        }

        bool isEmpty() const {
            return index == -1;
        }

        int currentSize() const {
            return index + 1;
        }

        int getMaxSize() const {
            return absolute_max;
        }
    };
}

int main()
{
    using GenericSystems::GrowingStack;

    GrowingStack<double> stack1(10, 2);
    GrowingStack<double> stack2(10, 2);

    stack1.push(10.5);
    stack1.push(20.5);
    stack1.push(30.5);

    stack2.push(100.1);
    stack2.push(200.2);

    GrowingStack<double> stack3(20, 5);

    int counter = 1;
    while (!stack1.isEmpty() && !stack2.isEmpty()) {
        if (counter % 2 != 0) {
            stack3.push(stack1.pop());
        } else {
            stack3.push(stack2.pop());
        }
        counter++;
    }

    while (!stack1.isEmpty()) stack3.push(stack1.pop());
    while (!stack2.isEmpty()) stack3.push(stack2.pop());

    cout << "\nCreating Stack 4 via Copy Constructor" << endl;
    GrowingStack<double> stack4 = stack3;

    cout << "\nCreating Stack 5 and using Assignment Operator" << endl;
    GrowingStack<double> stack5(50, 5);
    stack5 = stack4;

    cout << "\nFinal Stack 3 Content: ";
    while (!stack3.isEmpty()) {
        cout << stack3.pop() << " ";
    }
    cout << endl;

    return 0;
}
