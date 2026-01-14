#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} node;

// stored in reverse order
node* createNum(char *num) {
    node* head = NULL;
    for (int i = 0; i < strlen(num); i++) {
        node* temp = (node*)malloc(sizeof(node));
        temp->data = num[i] - '0';
        temp->next = head;
        head = temp;
    }
    return head;
}

node* reverseListNodeSorted(node* head) {
    node *prev = NULL, *ptr = head, *next_node = NULL;
    while (ptr != NULL) {
        next_node = ptr->next;
        ptr->next = prev;
        prev = ptr;
        ptr = next_node;
    }
    return prev;
}

// Print number in correct order
void printNum(node *head) {
    node* temp = reverseListNodeSorted(head);  // reverse copy
    node* ptr = temp;
    while (ptr != NULL) {
        printf("%d", ptr->data);
        ptr = ptr->next;
    }
    // restore original order
    reverseListNodeSorted(temp);
}

node* addition(node* n1, node* n2) {
    node* result = NULL;
    node* tail = NULL;
    int carry = 0;

    while (n1 != NULL || n2 != NULL || carry != 0) {
        int sum = carry;
        if (n1 != NULL) {
            sum += n1->data;
            n1 = n1->next;
        }
        if (n2 != NULL) {
            sum += n2->data;
            n2 = n2->next;
        }

        node* newNode = (node*)malloc(sizeof(node));
        newNode->data = sum % 10;
        newNode->next = NULL;
        carry = sum / 10;

        if (result == NULL) {
            result = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return result;
}

node* subtract(node* n1, node* n2){
    // assuming n1>n2
    node* result = NULL;
    node* tail = NULL;
    int borrow = 0;
    while(n1!=NULL || n2!=NULL){
        int diff;
        diff = (n1? n1->data:0) - borrow -(n2? n2->data:0);
        if(diff<0){
            diff = diff + 10;
            borrow= 1;
        }
        else{
            borrow=0;
        }
        node* temp = (node*)malloc(sizeof(node));
        temp->data = diff;
        temp->next = NULL;
        if(result == NULL){
            result = temp;
            tail = temp;
            temp->next = NULL;
        }
        else{
            tail->next = temp;
            tail = temp;
        }
         if (n1) n1 = n1->next;
        if (n2) n2 = n2->next;
    }
    return result;
}
int main() {
    char num1[100], num2[100];
    node* n1= NULL;
    node* n2= NULL;
    node* add= NULL;
    node* sub= NULL;
    int choice= 0;
    int loop = 1;
    while(loop){
    printf("Enter your choice:\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Exit\n");
    scanf("%d",&choice);
    switch (choice){
    case 1:
        printf("Addition: \n");
        printf("Enter the first number: ");
        scanf("%s", num1);
        n1 = createNum(num1);

        printf("Enter the second number: ");
        scanf("%s", num2);
        n2 = createNum(num2);

        printNum(n1);
        printf(" + ");
        printNum(n2);
        printf("\n= ");

        add = addition(n1, n2);
        printNum(add);
        printf("\n");
        break;
    case 2:
        printf("Substraction(num1 > num2): \n");
        printf("Enter the first number: ");
        scanf("%s", num1);
        n1 = createNum(num1);

        printf("Enter the second number: ");
        scanf("%s", num2);
        n2 = createNum(num2);

        printNum(n1);
        printf(" - ");
        printNum(n2);
        printf("\n= ");

        sub = subtract(n1, n2);
        printNum(sub);
        printf("\n");
        break;
    case 3:
        loop = 0;
        break;
    }
}
        return 0;
}
