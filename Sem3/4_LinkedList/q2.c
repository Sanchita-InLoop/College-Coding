#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
    int coeff; 
    int index;
    struct node *next; 
} node;
node* createTerms(int coeff,int index){
    node* temp = (node*)malloc(sizeof(node));
    temp->coeff = coeff;
    temp->index = index;
    temp->next = NULL;
    return temp;
}
node* createPoly(node* head, int coeff, int index) {
    node* temp = createTerms(coeff, index);
    if (head == NULL || index > head->index) {
        temp->next = head;
        head = temp;
        return head;
    }
    node* ptr = head;
    node* prev = NULL;
    while (ptr != NULL && ptr->index > index) {
        prev = ptr;
        ptr = ptr->next;
    }
    if (ptr != NULL && ptr->index == index) {
        ptr->coeff += coeff;
        free(temp);
    } else {
        temp->next = ptr;
        if (prev != NULL)
            prev->next = temp;
    }

    return head;
}
node* addition(node* poly1,node* poly2){
    node* add= poly1;
    node* temp = poly2;
    while(temp!= NULL){
    add = createPoly(add,temp->coeff,temp->index);
    temp = temp->next;
    }
    return add;
}
node* subtraction(node* poly1,node* poly2){
    node* sub = poly1;
    node* temp = poly2;
    while(temp!= NULL){
    sub = createPoly(sub,(-1)*temp->coeff,temp->index);
    temp = temp->next;
    }
    return sub;
}

void printPoly(node* head) {
    node* ptr = head;
    while (ptr != NULL) {
        printf("%dx^%d", ptr->coeff, ptr->index);
        ptr = ptr->next;
        if (ptr != NULL && ptr->coeff >= 0)
            printf(" + ");
    }
    printf("\n");
}

node* freeList(node* head){
	node *ptr;
	while(head != NULL){
		ptr = head;
		head = head->next;
		free(ptr);
	}
	return NULL;	
}
node* takeInput(node* head){
    int n, coeff, index;

    printf("\nEnter number of terms in the polynomial: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and power for term %d: ", i + 1);
        scanf("%d %d", &coeff, &index);
        head = createPoly(head, coeff, index);
    }

    printf("\nPolynomial is: ");
    printPoly(head);
    return head;
}

int main() {
    node* poly1= NULL;
    node* poly2= NULL;
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
        printf("Enter the first polynomial: ");
        poly1 = takeInput(poly1);

        printf("Enter the second polynomial: ");
        poly2 = takeInput(poly2);

        printPoly(poly1);
        printf(" + \n");
        printPoly(poly2);
        printf("\n= ");
        add = addition(poly1,poly2);
        printPoly(add);
        printf("\n");
        break;
    case 2:
        printf("Enter the first polynomial: ");
        poly1 = takeInput(poly1);

        printf("Enter the second polynomial: ");
        poly2 = takeInput(poly2);

        printPoly(poly1);
        printf(" - \n");
        printPoly(poly2);
        printf("\n= ");
        sub = subtraction(poly1,poly2);
        printPoly(sub);
        printf("\n");
        break;
    case 3:
        loop = 0;
        break;
    }
}
        return 0;

}
