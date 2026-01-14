#define MS 100
#include <stdio.h>
#include<stdlib.h>

typedef struct{
        int *arr;
        int count;
        int maxSize;
}stack;

stack* createIntStack(int size){
        stack *s=(stack*)malloc(sizeof(stack));
        if(!s)  return NULL;

        s->count= -1;
        s->maxSize=size;
        s->arr = (int*)malloc(sizeof(int));
        return s;
}

int initIntegerStack(stack *s,int StackSize){
        s->count= -1;
        s->maxSize=StackSize;
	s->arr = (int*)malloc(StackSize*sizeof(int));
        return 1;
}

int isIntegerStackFull(stack*s){
        if(!s || s->count+1 == s->maxSize) return 1;
        return 0;
}

int isIntegerStackEmpty(stack *s){
        if(!s || s->count+1 == 0) return 1;
        return 0;
}

int pushIntegerStack(stack *s,int element){
        if(isIntegerStackFull(s)){
                printf("The stack is full\n");
                return 0;
        }
        s->arr[++s->count]=element;
        printf("Pushed element %d\n",element);
        return 1;
}

int popIntegerStack(stack *s,int *elementPopped){
        if(isIntegerStackEmpty(s)){
                printf("The stack is empty\n");
                return 0;
        }
        *elementPopped=s->arr[s->count];
        printf("Popped element: %d\n",*elementPopped);
        s->count--;
        return 1;
}

int freeIntegerStack(stack*s){
        free(s-> arr);
        s->arr = NULL;
        return 1;
}

//Phase 1
int isoperator(char ch){
	if(ch =='+'||ch =='-' || ch == '/' || ch == '*'){
		return 1;
	}
	else{
	return 0;
	}
}

int operation(int op1, int op2, char ch){
	switch(ch){
		case '+': return (op1 + op2);
		case '-': return (op1 -op2);
		case '*': return (op1*op2);
		case '/': return (op1/op2);
		default: break;
	}
}

int main(){
	stack stk;
	int result = 0;
	char exp[100];
	initIntegerStack(&stk,MS);
	printf("Enter the expression\n");
	scanf("%s",exp);
	int i=0;
	while(exp[i]!='\0'){
		if(!(isoperator(exp[i]))){
			pushIntegerStack(&stk,exp[i]-'0');
			//popIntegerStack(&stk,&trial);
		}
		else{
			int op1,op2;
			int value =0;
			popIntegerStack(&stk,&op2);
			popIntegerStack(&stk,&op1);
			value = operation(op1,op2,exp[i]);
			pushIntegerStack(&stk,value);		
		}
		i++;
	}
	
	popIntegerStack(&stk,&result);
	printf("Final Value:%d\n",result);
	return 0;
}

