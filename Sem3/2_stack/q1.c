#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int count;
    int maxSize;
} stack;

int initIntegerStack(stack *s, int StackSize) {
    s->count = 0;
    s->maxSize = StackSize;
    s->arr = (int *)malloc(sizeof(int) * StackSize);
    return 1;
}

int isIntegerStackFull(stack *s) {
    if (!s || s->count == s->maxSize) return 1;
    return 0;
}

int isIntegerStackEmpty(stack *s) {
    if (!s || s->count == 0) return 1;
    return 0;
}

int pushIntegerStack(stack *s, int element) {
    if (isIntegerStackFull(s)) {
        printf("The stack is full\n");
        return 0;
    }
    s->arr[++s->count] = element;
    printf("Pushed element %d\n", element);
    return 1;
}

int popIntegerStack(stack *s, int *elementPopped) {
    if (isIntegerStackEmpty(s)) {
        printf("The stack is empty\n");
       return 0;
    }
    *elementPopped = s->arr[--s->count];
    printf("Popped element: %d\n", *elementPopped);
    return 1;
}

int freeIntegerStack(stack *s) {
    free(s->arr);
    s->arr = NULL;
    return 1;
}

int main() {
    stack s1, s2;
  	int N,M;
    int element = 0;
    printf("Enter the size of both the Stacks: ");
    scanf("%d %d",&N,&M);
    initIntegerStack(&s1, N);
    initIntegerStack(&s2, M);

    while (!isIntegerStackFull(&s1)) {
        printf("Enter the integer elements in stack 1: ");
        scanf("%d", &element);
        if (!pushIntegerStack(&s1, element)) {
            printf("Stack1 is full\n");
            break;
        }
    }
    while (!isIntegerStackFull(&s2)) {
        printf("Enter the integer elements in stack 2: ");
        scanf("%d", &element);
        if (!pushIntegerStack(&s2, element)) {
            printf("Both Stack1 and Stack2 are full\n");
            break;
        }
    }

    printf("Popping the elements from s2:\n");
    while (!isIntegerStackEmpty(&s2)) {
        popIntegerStack(&s2, &element);
        printf("Popped element from s2: %d\n", element);
    }

    printf("Popping the elements from s1:\n");
    while (!isIntegerStackEmpty(&s1)) {
        popIntegerStack(&s1, &element);
        printf("Popped element from s1: %d\n", element);
    }
    printf("All the elements are popped out!\n");
    freeIntegerStack(&s1);
    freeIntegerStack(&s2);

    return 0;
}
