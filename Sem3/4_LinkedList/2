#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int data; 
    struct node *next; 
} node;

// descending order
node* addListNodeSorted(node *head, int elem) {
    node *temp = (node*)malloc(sizeof(node));
    temp->data = elem;
    temp->next = NULL;

    // Insert at beginning
    if (head == NULL || elem > head->data) {
        temp->next = head;
        return temp;
    }

    // Insert somewhere else
    node *ptr = head;
    node *prev = NULL;
    while (ptr != NULL && ptr->data >= elem) {
        prev = ptr;
        ptr = ptr->next;
    }
    temp->next = ptr;
    prev->next = temp;

    return head;
}
int isPresentListNodeSorted(node *head, int elem) {
    int position = 1;
    node *ptr = head;

    while (ptr != NULL) {
        if (ptr->data == elem) {
            return position;
        }
        if (ptr->data < elem) break;
        ptr = ptr->next;
        position++;
    }
    return 0; //not found
}
node* deleteListNodeSorted(node *head, int elem) {
	if(!isPresentListNodeSorted(head,elem)){
		printf("%d Not found!\n",elem);
		}
    // empty linked list
    if (head == NULL) return NULL;
    node *temp = head;

    //First node to delete
    if (head->data == elem) {
        head = head->next;
        free(temp);
        return head;
    }

    //Search in rest of list
    node *prev = NULL;
    while (temp != NULL && temp->data != elem) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return head; // not found
    prev->next = temp->next;
    free(temp);
    return head;
}
void printLinkedList(node *head) {
    node *ptr = head;
    printf("HEAD");
    while (ptr != NULL) {
        printf(" -> %d", ptr->data);
        ptr = ptr->next;
    }
    printf(" -> NULL\n");
}

node* freeListNodeSorted(node* head){
	node *ptr;
	while(head != NULL){
		ptr = head;
		head = head->next;
		free(ptr);
	}
	return NULL;	
}
node * reverseListNodeSorted(node* head) {
    node *prev = NULL;
    node *ptr = head;
    node *next_node = NULL; 
    while (ptr != NULL) {
        next_node = ptr->next;
        ptr->next = prev;
        prev = ptr;
        ptr = next_node;
    }
    return prev;
}

node* updateListNode(node *head) {
    node *ptr = head;
    while (ptr != NULL) {
        ptr->data += rand() % 10;  // add random number [0,9]
        ptr = ptr->next;
    }
    return head;
}

node* sortListNode(node* head) {
    node* sorted = NULL;  
    node* current = head;

    while (current != NULL) {
        node* nextNode = current->next;

        // Insert current node into the sorted list
        if (sorted == NULL || current->data > sorted->data) {
            current->next = sorted;
            sorted = current;
        } else {
            node* temp = sorted;
            while (temp->next != NULL && temp->next->data >= current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = nextNode;
    }

    return sorted;
}

node* mergeListNodeSorted(node *head1, node *head2) {
    node *merged = NULL, *tail = NULL;
    while (head1 != NULL && head2 != NULL) {
        node *temp = NULL;

        if (head1->data >= head2->data) {
            temp = head1;
            head1 = head1->next;
        } else {
            temp = head2;
            head2 = head2->next;
        }

        temp->next = NULL;
        if (merged == NULL) {
            merged = temp;
            tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }

    if (head1 != NULL) {
        if (merged == NULL) merged = head1;
        else tail->next = head1;
    } else if (head2 != NULL) {
        if (merged == NULL) merged = head2;
        else tail->next = head2;
    }
    return merged;
}


int main() {
    node *s1 = NULL,*s2=NULL;
    int n,val;
    int choice=0;
    int elem =0,running = 1;
    while(running){
	printf("Enter your choice: \n");
	printf("1. Add a element to the linked list\n");
	printf("2. Search a element\n");
	printf("3. Delete a element\n");
	printf("4. Print \n");
	printf("5. Free the Linked List\n");
    printf("6. Reverse the string \n");
	printf("7. Update the List and Sort in descending order \n");
    printf("8. Merge two linked list \n");
    printf("9. Exit\n");
	scanf("%d",&choice);
	switch (choice){
		case 1:
			printf("Enter the element : ");
			scanf("%d",&elem);
			s1 = addListNodeSorted(s1, elem);
			printf("Linked list: \n");
			printLinkedList(s1);
			break;			
		case 2:
		       printf("Enter the element: ");
	     		scanf("%d",&elem);
    			int pos = isPresentListNodeSorted(s1, elem);
    			if (pos) printf("%d found at position %d\n", elem, pos);
    			else printf("%d not found\n", elem);
			break;
		case 3: 
			printf("Enter the element: ");
			scanf("%d",&elem);
    			s1 = deleteListNodeSorted(s1, elem);
                printf("Present Linked List:\n", elem);
    			printLinkedList(s1);
			break;
		case 4:
			printLinkedList(s1);
			break;
		case 5:
			s1 = freeListNodeSorted(s1);
			break;
        case 6:
            s1 = reverseListNodeSorted(s1);
            printLinkedList(s1);
            break;
        case 7:
            s1 = updateListNode(s1);
            printf("The updated list: \n");
            printLinkedList(s1);
            s1 = sortListNode(s1);
            printf("The sorted list: \n");
            printLinkedList(s1);
            break;
        case 8:
            printf("Enter number of elements in second list: ");
            scanf("%d", &n);
            for (int i = 0; i < n; i++) {
                printf("Enter element %d: ", i + 1);
                scanf("%d", &val);
                s2 = addListNodeSorted(s2, val);
            }

            printf("First List:\n");
            printLinkedList(s1);
            printf("Second List:\n");
            printLinkedList(s2);

            s1 = mergeListNodeSorted(s1, s2);

            printf("Merged List (Descending):\n");
            printLinkedList(s1);

            break;
		case 9:
			running = 0;
			break;
		default:
			printf("Invalid choice!");
			break;
	}
    }
    return 0;
}
