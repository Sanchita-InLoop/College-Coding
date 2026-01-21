#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linearComparision =0;
int BinaryComparision =0;

void genAndStoreRandValues(int arr[],int n) {
    srand(time(NULL));
    printf("Generating and storing %d random values...\n", n);
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }
    printf("Successfully generated and stored %d values.\n", n);
}

int LinearSearch(int arr[], int n, int elem){
    for (int i = 0; i < n; i++) {
        linearComparision++;
        if (arr[i] == elem){
            return i; 
        }
    }
    return -1;
}
//bubble sort
void SortArray(int arr[], int n){
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
int BinarySearch(int arr[], int n, int elem){
    int low = 0, high = n - 1;
    while (low <= high) {
        BinaryComparision++;
        int mid = low + (high - low) / 2;
        if (arr[mid] == elem)
            return mid;
        else if (arr[mid] < elem)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main(){
    int n = 50000;
    int arr[n];
    clock_t start, end;
    double BinaryTime, LinearTime;
    genAndStoreRandValues(arr,n);
    SortArray(arr,n);
    int elem;
    printf("Enter the element you want to search: ");
    scanf("%d",&elem);
    start = clock();
    int linearPos = LinearSearch(arr,n,elem);
    end = clock();
    LinearTime = (double)(end-start)/CLOCKS_PER_SEC;
    start = clock();
    int binaryPos = BinarySearch(arr,n,elem);
    end = clock();
    BinaryTime = (double)(end-start)/CLOCKS_PER_SEC;

    printf("Element = %d\n",elem);
    printf("Linear Search: \n");
    printf("Position: %d\n",linearPos);
    printf("Time Taken: %f seconds\n",LinearTime);
    printf("Comparision : %d\n", linearComparision);
    printf("Binary Search: \n");
    printf("Position: %d\n",binaryPos);
    printf("Time Taken: %f seconds\n",BinaryTime);
    printf("Comparision : %d\n", BinaryComparision);
    return 0;
}
