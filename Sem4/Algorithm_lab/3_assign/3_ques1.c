#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparison_count = 0;

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// using the last element as pivot
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = (low - 1); 
  
    for (int j = low; j <= high - 1; j++) {
        comparison_count++; // Count comparison
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Randomized partition: picks random pivot and swaps with high and perform partition
int randomized_partition(int arr[], int low, int high) {
    srand(time(NULL));
    int random = low + rand() % (high - low + 1);
    swap(&arr[random], &arr[high]);
    return partition(arr, low, high);
}

// Randomized Quicksort
void randomized_quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = randomized_partition(arr, low, high);
        randomized_quicksort(arr, low, pi - 1);
        randomized_quicksort(arr, pi + 1, high);
    }
}

// Inputs
void sorted_input(int arr[], int n) {
    for(int i=0; i<n; i++) arr[i] = i;
}

void reverse_input(int arr[], int n) {
    for(int i=0; i<n; i++) arr[i] = n-i;
}

void random_input(int arr[], int n) {
    for(int i=0; i<n; i++) arr[i] = rand() % n;
}

int main() {
    int n = 100000;
    int *arr = (int*)malloc(n * sizeof(int));
    clock_t start, end;
    double cpu_time_used;

    printf("\n=================================================================\n");
    printf("PROBLEM 1: RANDOMIZED QUICKSORT PERFORMANCE\n");
    printf("Input Size: %d\n", n);
    printf("=================================================================\n");
    printf("%-20s | %-15s | %-15s\n", "Scenario", "Time (s)", "Comparisons");
    printf("-----------------------------------------------------------------\n");

    // 1.1 Sorted
    sorted_input(arr, n);
    comparison_count =0;
    start = clock();
    randomized_quicksort(arr, 0, n - 1);
    end = clock();
    printf("%-20s | %-15f | %-15lld\n", "Sorted (Best)", ((double)(end - start)) / CLOCKS_PER_SEC, comparison_count);

    // 1.2 Reverse
    reverse_input(arr, n);
    comparison_count =0;
    start = clock();
    randomized_quicksort(arr, 0, n - 1);
    end = clock();
    printf("%-20s | %-15f | %-15lld\n", "Reverse (Worst)", ((double)(end - start)) / CLOCKS_PER_SEC, comparison_count);

    // 1.3 Random
    random_input(arr, n);
    comparison_count =0;
    start = clock();
    randomized_quicksort(arr, 0, n - 1);
    end = clock();
    printf("%-20s | %-15f | %-15lld\n\n", "Random (Avg)", ((double)(end - start)) / CLOCKS_PER_SEC, comparison_count);
    
    free(arr);
    return 0;
}