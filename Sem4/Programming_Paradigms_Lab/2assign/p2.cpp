#include<iostream>
using namespace std;

namespace growingStack{
	struct mystack{
		int* data;
		int top;
		int count;
		int maxSize;
	};
	
	struct mystack* initialise(mystack &s,int maxSize){
		s.data = new int[maxSize];
		s.top = 0;
		s.count = 0;
		s.maxSize = maxSize;
		return s;
	}

	int isEmpty(mystack &s){
		return (s.count == 0);
	}

	int isFull(mystack &s){
		return (s.maxSize == count);
	}

	int getMaxSize(mystack &s){
		return s.maxSize;
	}

	int currentSize(mystack &s){
		return s.count;
	}
	
	void push(mystack &s,int data){
		s.data = data;
		s.top++;
		s.count++;
	}


}
int main(){

	return 0;
}
