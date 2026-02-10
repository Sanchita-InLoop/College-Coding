#include <iostream>

class BaseData {
public:
    virtual ~BaseData() {}
};

class IntData : public BaseData { public: int val; IntData(int v) : val(v) {} };
class StringData : public BaseData { public: const char* val; StringData(const char* v) : val(v) {} };

class GrowingStack {
    BaseData** data;
    int top;
    int capacity;

public:
    GrowingStack(int size = 5) : capacity(size), top(-1) {
        data = new BaseData*[capacity];
    }

    void push(BaseData* item) { data[++top] = item; }
    
    BaseData* pop() { return data[top--]; }
};

int main() {
    GrowingStack genericStack;
    genericStack.push(new IntData(10));
    genericStack.push(new StringData("CS2273"));

    return 0;
}