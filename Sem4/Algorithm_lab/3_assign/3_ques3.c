#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparison_count = 0;
int max_depth = 0;
int current_depth = 0;

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

//Randomized quick sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = (low - 1); 
  
    for (int j = low; j <= high - 1; j++) {
        comparison_count++; 
        if (arr[j] <= pivot) { 
            i++; 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
}
int randomized_partition(int arr[], int low, int high) {
    int random = low + rand() % (high - low + 1);
    swap(&arr[random], &arr[high]);
    return partition(arr, low, high);
}

void randomized_quicksort(int arr[], int low, int high) {
    current_depth++;
    if (current_depth > max_depth) {
        max_depth = current_depth;
    }

    if (low < high) {
        int pi = randomized_partition(arr, low, high);
        randomized_quicksort(arr, low, pi - 1);
        randomized_quicksort(arr, pi + 1, high);
    }
    current_depth--;
}

// Merge Sort Implementation
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        comparison_count++; 
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L); free(R);
}

void mergeSort(int arr[], int l, int r) {
    current_depth++;
    if (current_depth > max_depth) max_depth = current_depth;
    
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
    current_depth--;
}

void generate_nearly_sorted(int arr[], int n) {
    for(int i=0; i<n; i++) arr[i] = i;
    
    int swap_count = (int)(n * 0.2); // 20%
    for(int k=0; k<swap_count; k++) {
        int i = rand() % n;
        int j = rand() % n;
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int main() {
    int n = 100000;
    int *arr = (int*)malloc(n * sizeof(int));
    int *temp = (int*)malloc(n * sizeof(int));
    srand(time(NULL));

    generate_nearly_sorted(arr, n);
    printf("\n========================================================\n");
    printf("PROBLEM 3: NEARLY SORTED DATA (80%% SORTED)\n");
    printf("Comparing Randomized Quicksort vs Merge Sort\n");
    printf("========================================================\n");
    printf("Algorithm\tTime(s)\t\tComparisons\tMax Depth\n");
    printf("--------------------------------------------------------\n");

    // Merge Sort
    for(int i=0; i<n; i++) temp[i] = arr[i]; // Copy
    comparison_count = 0; max_depth = 0; current_depth = 0;
    clock_t start = clock();
    mergeSort(temp, 0, n - 1);
    clock_t end = clock();
    printf("Merge Sort\t%.4f\t\t%lld\t\t%d\n", ((double)(end-start))/CLOCKS_PER_SEC, comparison_count, max_depth);

    // Randomized Quicksort
    for(int i=0; i<n; i++) temp[i] = arr[i];
    comparison_count = 0; max_depth = 0; current_depth = 0;
    start = clock();
    randomized_quicksort(temp, 0, n - 1);
    end = clock();
    printf("Rand Quick\t%.4f\t\t%lld\t\t%d\n\n", ((double)(end-start))/CLOCKS_PER_SEC, comparison_count, max_depth);

    free(arr); free(temp);
    return 0;
}