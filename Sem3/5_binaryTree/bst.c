#include<stdio.h>
#include<stdlib.h>

typedef struct treenode {
    int data;
    struct treenode *parent;
    struct treenode *left, *right;
} treenode;

int isEmpty(treenode *t) {
    return (t == NULL);
}

treenode* createNode(int val) {
    treenode* newNode = (treenode*)malloc(sizeof(treenode));
    newNode->data = val;
    newNode->parent = NULL;
    newNode->left = newNode->right = NULL;
    return newNode;
}

treenode* insertNode(treenode *t, int val) {
    if (t == NULL)
        return createNode(val);

    if (val < t->data)
        t->left = insertNode(t->left, val);
    else if (val > t->data)
        t->right = insertNode(t->right, val);
    return t;
}

int getCount(treenode *t) {
    if (t == NULL)
        return 0;
    return 1 + getCount(t->left) + getCount(t->right);
}

// Inorder Traversal (Left, Root, Right)
int inorder(treenode *t) {
    if (isEmpty(t))
        return 0;

    inorder(t->left);
    printf("%d ", t->data);
    inorder(t->right);
    return 1;
}

// Preorder Traversal (Root, Left, Right)
int preorder(treenode *t) {
    if (isEmpty(t))
        return 0;

    printf("%d ", t->data);
    preorder(t->left);
    preorder(t->right);
    return 1;
}

// Postorder Traversal (Left, Right, Root)
int postorder(treenode *t) {
    if (isEmpty(t))
        return 0;

    postorder(t->left);
    postorder(t->right);
    printf("%d ", t->data);
    return 1;
}

// Height of the Tree
int height(treenode* t){
    if (t == NULL)
        return -1;
    if(t->left == NULL && t->right == NULL)
	    return 0;
    int lh = height(t->left);
    int rh = height(t->right);
    if(lh>rh) return (lh +1);
    else return(rh+1);
}

// Minimum value
int min(treenode *t){
    if (t == NULL){
        printf("Tree is empty.\n");
        return -1;
    }
    while(t->left != NULL){
        t = t->left;
    }
    return t->data;
}

// Maximum value
int max(treenode *t){
    if (t == NULL){
        printf("Tree is empty.\n");
        return -1;
    }
    while(t->right != NULL){
        t = t->right;
    }
    return t->data;
}

// Check if two trees are equal
int equal(treenode* t1, treenode* t2){
    if (t1 == NULL && t2 == NULL)
        return 1;
    if (t1 == NULL || t2 == NULL)
        return 0;
    return (t1->data == t2->data) && equal(t1->left, t2->left) && equal(t1->right, t2->right);
}

// Returns the minimum node
treenode* minNode(treenode* node) {
    treenode* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

treenode* searchNode(treenode* t,int key){
	if(t==NULL|| t->data == key){
		return t;}
	else if(key > t->data){
		return searchNode(t->right,key);}
	else return searchNode(t->left, key);
	return NULL;
}

treenode* insucc(treenode* t, int key){
	treenode* curr = searchNode(t,key);
	if(curr == NULL) return NULL;
	else if(curr->right != NULL){
		return minNode(curr->right);
	}
	else{
		treenode* temp = curr->parent;
		while(temp!=NULL && curr == temp->right){
			curr = temp;
			temp = temp->parent;
		}
		return temp;
	}
}

treenode* deleteNode(treenode *t, int val) {
    if (t == NULL) return NULL;

    if (val < t->data)
        t->left = deleteNode(t->left, val);
    else if (val > t->data)
        t->right = deleteNode(t->right, val);
    else {
        // Node found
        //case1: no child
        if (t->left == NULL && t->right == NULL) {
            free(t);
            return NULL;
        }
        //case2 : 1 child
        else if (t->left == NULL || t->right == NULL) {
            treenode *child = (t->left) ? t->left : t->right;
            child->parent = t->parent;
            free(t);
            return child;
        }
        // case 3: 2 child
        else {
            treenode *succ = minNode(t->right);
            t->data = succ->data;
            t->right = deleteNode(t->right, succ->data);
        }
    }
    if (t->left)  t->left->parent  = t;
    if (t->right) t->right->parent = t;
    return t;
}

int main() {
    treenode* root = NULL;
    treenode* root2 = NULL; 
    int choice, val;
    int loop = 1;

    while(loop){
        printf("\nBinary Search Tree Menu:\n");
        printf("1. Insert Node\n");
        printf("2. Check if Tree is Empty\n");
        printf("3. Count Nodes\n");
        printf("4. Inorder Traversal\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Height of the tree\n");
        printf("8. Minimum value\n");
        printf("9. Maximum value\n");
        printf("10. Check Equality of Two Trees\n");
        printf("11. Find Inorder Successor\n");
        printf("12. Delete a Node\n");
        printf("13. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                root = insertNode(root, val);
                printf("%d inserted into BST.\n", val);
                break;

            case 2:
                if (isEmpty(root))
                    printf("Tree is Empty\n");
                else
                    printf("Tree is Not Empty\n");
                break;

            case 3:
                printf("Total nodes in BST: %d\n", getCount(root));
                break;

            case 4:
                if (!inorder(root))
                    printf("Tree is Empty\n");
                else
                    printf("\nInorder traversal complete\n");
                break;

            case 5:
                if (!preorder(root))
                    printf("Tree is Empty\n");
                else
                    printf("\nPreorder traversal complete\n");
                break;

            case 6:
                if (!postorder(root))
                    printf("Tree is Empty\n");
                else
                    printf("\nPostorder traversal complete\n");
                break;

            case 7:
                printf("Height of tree: %d\n", height(root));
                break;

            case 8:
                printf("Minimum value: %d\n", min(root));
                break;

            case 9:
                printf("Maximum value: %d\n", max(root));
                break;

            case 10:
                printf("Enter values for second tree (end with -1):\n");
                root2 = NULL;
                while(1){
                    scanf("%d", &val);
                    if(val == -1) break;
                    root2 = insertNode(root2, val);
                }
                if(equal(root, root2))
                    printf("The two trees are EQUAL.\n");
                else
                    printf("The two trees are NOT equal.\n");
                break;

            case 11:
                printf("Enter key to find inorder successor: ");
                scanf("%d", &val);
                treenode *succ = insucc(root, val);
                if(succ != NULL)
                    printf("Inorder successor of %d is %d\n", val, succ->data);
                else
                    printf("No inorder successor found.\n");
                break;

            case 12:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                root = deleteNode(root, val);
                printf("%d deleted (if it existed).\n", val);
                break;

            case 13:
                printf("Exiting program.\n");
                loop = 0;
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}	
