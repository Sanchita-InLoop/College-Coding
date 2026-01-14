#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void copyArray(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}
void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand();
}

void bubbleSort(int arr[], int n) {
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

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

int main() {
    int sizes[10] = {5000, 10000, 15000, 20000, 25000,
                     30000, 35000, 40000, 45000, 50000};

    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        int n = sizes[i];

        int *original = (int *)malloc(n * sizeof(int));
        int *arr = (int *)malloc(n * sizeof(int));

        generateRandomArray(original, n);

        clock_t start, end;
        double bubbleTime, insertionTime, quickTime, mergeTime;

        copyArray(original, arr, n);
        start = clock();
        bubbleSort(arr, n);
        end = clock();
        bubbleTime = (double)(end - start) / CLOCKS_PER_SEC;

        copyArray(original, arr, n);
        start = clock();
        insertionSort(arr, n);
        end = clock();
        insertionTime = (double)(end - start) / CLOCKS_PER_SEC;

        copyArray(original, arr, n);
        start = clock();
        quickSort(arr, 0, n - 1);
        end = clock();
        quickTime = (double)(end - start) / CLOCKS_PER_SEC;

        copyArray(original, arr, n);
        start = clock();
        mergeSort(arr, 0, n - 1);
        end = clock();
        mergeTime = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\nArray Size: %d\n", n);
        printf("Bubble Sort Time     : %.6f seconds\n", bubbleTime);
        printf("Insertion Sort Time  : %.6f seconds\n", insertionTime);
        printf("Quick Sort Time      : %.6f seconds\n", quickTime);
        printf("Merge Sort Time      : %.6f seconds\n", mergeTime);
        free(original);
        free(arr);
    }
    printf("\n");

    return 0;
}
