#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int *arr;
    int front,rear,size;
}queue;

queue* createIntQueue(int queueSize){
    if(queueSize<=0) return NULL;
    queue *q=(queue*)malloc(sizeof(queue));
    if (!q) return NULL;
    
    q->arr=(int*)malloc(queueSize*sizeof(int));
    q->size=queueSize;
    q->front= -1;
    q->rear = -1;

    return q;
}

int isIntegerQueueFull(queue *q){
    if(!q) return 0;
    return ((q->rear+1)%q->size == q->front);
}   

int isIntegerQueueEmpty(queue *q){
    if(!q) return 0;
    return (q->front == -1);
}

int enqueueInteger(queue *q,int element){
    if(isIntegerQueueFull(q)){
        printf("Queue is full\n");
        return 0;
    }
    if(q->front == -1) q->front = 0;

    q->rear = (q->rear+1)%q->size;
    q->arr[q->rear] = element;
    printf("Enqueued: %d\n",element);
    return 1;
}

int dequeueInteger(queue *q,int *element){
    if(!q || isIntegerQueueEmpty(q)){
        printf("Queue is empty\n");
        return 0;
    }
    *element = q->arr[q->front];
    if(q->front == q->rear){   
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front+1)%q->size;
    }
    printf("Dequeued the element %d\n",*element);
    return 1;
}

void display(queue *q){
    if (isIntegerQueueEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    int i = q->front;
    printf("Queue: ");
    while (1) {
        printf("%d ", q->arr[i]);
        if (i == q->rear) break;
        i = (i + 1) % q->size;
    }
    printf("\n");
}

int freeQueue(queue *q){
    if(!q) return 0;
    free(q->arr);
    free(q);
    return 1;   
}

int main(){
    int element = 0;
    int size;
    int choice;
    int running=1;
    queue *q = NULL;       
    queue *myQueue = NULL;     
    while(running){
        printf("\nEnter your choice: \n");
        printf("1. Create a queue\n");
        printf("2. Enqueue \n");
        printf("3. Dequeue\n");
        printf("4. Queue Implementation (with rValue)\n");
        printf("5. Exit\n");
        scanf("%d",&choice);
        switch(choice){
        case 1:
            printf("Enter the size of the queue: ");
            scanf("%d",&size);
            if(q) freeQueue(q);
            q = createIntQueue(size);
            printf("Queue created of size %d\n", size);
            break;            
        case 2:
            if(!q){ 
                printf("Create a queue first!\n"); 
                break; 
            }
            printf("Enter the element: ");
            scanf("%d",&element);
            enqueueInteger(q,element);
            break;
        case 3:
            if(!q){ 
                printf("Create a queue first!\n");
                break; 
            }
            element=0;
            dequeueInteger(q,&element);
            break;
        case 4: {
            int N, val;
            printf("Enter size of queue: ");
            scanf("%d", &N);
            if(myQueue) freeQueue(myQueue);
            myQueue = createIntQueue(N);

            printf("Enter positive integers to enqueue (queue fills until overflow):\n");
            while (1) {
                scanf("%d", &val);
                if (!enqueueInteger(myQueue, val)) {
                    printf("Queue overflow occurred!\n");
                    break;
                }
            }

            printf("Initial Queue:\n");
            display(myQueue);

            int rValue, qElement;
            printf("Enter the fixed rValue: ");
            scanf("%d",&rValue);
            printf("\nProcessing Queue with rValue = %d\n", rValue);

            while (!isIntegerQueueEmpty(myQueue)) {
                dequeueInteger(myQueue, &qElement);
                qElement = qElement - rValue;
                if (qElement > 0) {
                    enqueueInteger(myQueue, qElement);
                } else {
                    printf("Dropped element (<=0)\n");
                }   
                display(myQueue);
            }
            printf("Queue underflow (empty now)\n");
            break;
        }
        case 5:
            freeQueue(q);
            freeQueue(myQueue);
            running = 0;
            break;
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}
