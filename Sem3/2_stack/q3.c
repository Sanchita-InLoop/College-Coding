#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *arr;  
    int count;
    int maxSize;
} stack;

int initStack(stack *s, int size) {
    s->count = 0;
    s->maxSize = size;
    s->arr = (char *)malloc(sizeof(char) * size);
    return 1;
}

int isStackFull(stack *s) {
    return (s->count == s->maxSize);
}

int isStackEmpty(stack *s) {
    return (s->count == 0);
}

int push(stack *s, char ch) {
    if (isStackFull(s)) return 0;
    s->arr[++s->count] = ch;
    return 1;
}

int pop(stack *s, char *ch) {
    if (isStackEmpty(s)) return 0;
    *ch = s->arr[--s->count];
    return 1;
}

void freeStack(stack *s) {
    free(s->arr);
    s->arr = NULL;
}

int isMatchingPair(char open, char close) {
    if((open == '(' && close == ')') ||(open == '{' && close == '}') ||(open == '[' && close == ']')){
        return 1;
    }
    return 0;
}

int checkBalancedParentheses(const char *expr) {
    stack s;
    initStack(&s, strlen(expr));
    for (int i = 0; i < strlen(expr); i++) {
        char ch = expr[i];
        if (ch == '(' || ch == '{' || ch == '[') {
            push(&s, ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            char top;
            if (!pop(&s, &top) || !isMatchingPair(top, ch)) {
                freeStack(&s);
                return 0;
            }
        }
    }
    int balanced = isStackEmpty(&s);
    freeStack(&s);
    return balanced;
}
int main() {
    char expr[100];
    printf("Enter a mathematical expression: ");
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = '\0'; //remove newline
    if (checkBalancedParentheses(expr)) {
        printf("Expression is correct (balanced parentheses).\n");
    } else {
        printf("Expression is incorrect (unbalanced parentheses).\n");
    }

    return 0;
}
