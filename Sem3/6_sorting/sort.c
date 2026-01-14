#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

int exchanges; // Global counter

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

//swapping
void swap(int *a , int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
//Insertion Sort 

//Default Algorithm
void insertionSort_default(int arr[], int n) {
    exchanges = 0;
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
            swap(&arr[j],&arr[j-1]);
            exchanges++;
        }
    }
}

//Avoiding Swap (using shifting)
void insertionSort_shift(int arr[], int n) {
    exchanges = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            exchanges++;
        }
        arr[j + 1] = key;
    }
}

//bubble sort

// Default Algorithm
void bubbleSort_default(int arr[], int n) {
    exchanges = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j],&arr[j+1]);
                exchanges++;
            }
        }
    }
}

// Flagged Bubble Sort
void bubbleSort_flagged(int arr[], int n) {
    exchanges = 0;
    int flag;
    for (int i = 0; i < n - 1; i++) {
        flag = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j],&arr[j+1]);
                exchanges++;
                flag = 1;
            }
        }
        if (!flag)
            break;
    }
}

// Range Limiting Bubble Sort
void bubbleSort_rangeLimit(int arr[], int n) {
    exchanges = 0;
    int lastExchange, limit = n - 1;
    while (limit > 0) {
        lastExchange = 0;
        for (int j = 0; j < limit; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j],&arr[j + 1]);
                exchanges++;
                lastExchange = j;
            }
        }
        limit = lastExchange;
    }
}

// Alternating Bubble Sort (Cocktail Sort)
void bubbleSort_alternating(int arr[], int n) {
    exchanges = 0;
    int start = 0, end = n - 1;
    int swapped = 1;
    while (swapped) {
        swapped = 0;
        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
             
               swap(&arr[i] , &arr[i + 1]);
                exchanges++;
                swapped = 1;
            }
        }
        if (!swapped)
            break;
        swapped = 0;
        end--;
        for (int i = end - 1; i >= start; i--) {
            if (arr[i] > arr[i + 1]) {
           
                swap(&arr[i] ,&arr[i+1]);
	    	exchanges++;
                swapped = 1;
            }
        }
        start++;
    }
}

//Merge Sort
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else {
            arr[k++] = R[j++];
            exchanges++;
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Quick Sort with Median of Three 

int medianOfThree(int arr[], int low, int high) {
    int mid = (low + high) / 2;
    if (arr[low] > arr[mid]) {
        int t = arr[low]; arr[low] = arr[mid]; arr[mid] = t;
    }
    if (arr[low] > arr[high]) {
        int t = arr[low]; arr[low] = arr[high]; arr[high] = t;
    }
    if (arr[mid] > arr[high]) {
        int t = arr[mid]; arr[mid] = arr[high]; arr[high] = t;
    }
    int t = arr[mid];
    arr[mid] = arr[high - 1];
    arr[high - 1] = t;
    return arr[high - 1];
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = medianOfThree(arr, low, high);
        int i = low, j = high - 1;
        while (1) {
            while (arr[++i] < pivot);
            while (arr[--j] > pivot);
            if (i < j) {
                int t = arr[i]; arr[i] = arr[j]; arr[j] = t; exchanges++;
            } else break;
        }
        int t = arr[i]; arr[i] = arr[high - 1]; arr[high - 1] = t; exchanges++;
        quickSort(arr, low, i - 1);
        quickSort(arr, i + 1, high);
    }
}

int main() {
    int list1[SIZE] = {1,16,12,26,25,35,33,58,45,42,56,67,83,75,74,86,81,88,99,95};
    int list2[SIZE] = {1,17,21,42,24,27,32,35,45,47,57,23,66,69,70,76,87,85,95,99};
    int list3[SIZE] = {22,20,81,38,95,84,99,12,79,44,26,87,96,10,48,80,1,31,16,92};
    int temp[SIZE];
    int choice, listChoice;

    while (1) {
        printf("\nSorting Algorithms Menu\n");
        printf("1. Insertion Sort (Default)\n");
        printf("2. Insertion Sort (Shift)\n");
        printf("3. Bubble Sort (Default)\n");
        printf("4. Bubble Sort (Flagged)\n");
        printf("5. Bubble Sort (Range Limit)\n");
        printf("6. Bubble Sort (Alternating / Cocktail Sort)\n");
        printf("7. Merge Sort\n");
        printf("8. Quick Sort (Median of Three)\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 9) {
            printf("\nExiting program...\n");
            break;
        }

        printf("\nSelect list:\n");
        printf("1. List 1\n2. List 2\n3. List 3\n");
        printf("Enter list number: ");
        scanf("%d", &listChoice);

        // Copy selected list into temp array
        switch (listChoice) {
            case 1: for (int i = 0; i < SIZE; i++) temp[i] = list1[i]; break;
            case 2: for (int i = 0; i < SIZE; i++) temp[i] = list2[i]; break;
            case 3: for (int i = 0; i < SIZE; i++) temp[i] = list3[i]; break;
            default: 
                printf("Invalid list choice.\n");
                continue;
        }

        printf("\nOriginal Array:\n");
        printArray(temp, SIZE);

        exchanges = 0;  // reset counter

        switch (choice) {
            case 1:
                insertionSort_default(temp, SIZE);
                printf("\nSorted using Insertion Sort (Default):\n");
                break;
            case 2:
                insertionSort_shift(temp, SIZE);
                printf("\nSorted using Insertion Sort (Shift):\n");
                break;
            case 3:
                bubbleSort_default(temp, SIZE);
                printf("\nSorted using Bubble Sort (Default):\n");
                break;
            case 4:
                bubbleSort_flagged(temp, SIZE);
                printf("\nSorted using Bubble Sort (Flagged):\n");
                break;
            case 5:
                bubbleSort_rangeLimit(temp, SIZE);
                printf("\nSorted using Bubble Sort (Range Limit):\n");
                break;
            case 6:
                bubbleSort_alternating(temp, SIZE);
                printf("\nSorted using Bubble Sort (Alternating / Cocktail):\n");
                break;
            case 7:
                mergeSort(temp, 0, SIZE - 1);
                printf("\nSorted using Merge Sort:\n");
                break;
            case 8:
                quickSort(temp, 0, SIZE - 1);
                printf("\nSorted using Quick Sort (Median of Three):\n");
                break;
            default:
                printf("\nInvalid choice.\n");
                continue;
        }

        printArray(temp, SIZE);
        printf("Exchanges: %d\n", exchanges);
    }

    return 0;
}
