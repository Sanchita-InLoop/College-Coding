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

// Standard Partition (Last element fixed pivot)
int standard_partition(int arr[], int low, int high) {
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

void standard_quicksort(int arr[], int low, int high) {
    current_depth++;
    if (current_depth > max_depth) max_depth = current_depth;

    if (low < high) {
        int pi = standard_partition(arr, low, high);
        standard_quicksort(arr, low, pi - 1);
        standard_quicksort(arr, pi + 1, high);
    }
    current_depth--;
}

// Randomized Partition
int randomized_partition(int arr[], int low, int high) {
    int random = low + rand() % (high - low + 1);
    swap(&arr[random], &arr[high]);
    return standard_partition(arr, low, high);
}

void randomized_quicksort(int arr[], int low, int high) {
    current_depth++;
    if (current_depth > max_depth) max_depth = current_depth;

    if (low < high) {
        int pi = randomized_partition(arr, low, high);
        randomized_quicksort(arr, low, pi - 1);
        randomized_quicksort(arr, pi + 1, high);
    }
    current_depth--;
}

void generate_with_duplicates(int arr[], int n, int percent_duplicates) {
    int unique_count = n * (100 - percent_duplicates) / 100;
    if (unique_count < 1) unique_count = 1;
    
    for(int i=0; i<n; i++) {
        arr[i] = rand() % unique_count; 
    }
}

void copy_array(int src[], int dest[], int n) {
    for(int i=0; i<n; i++) dest[i] = src[i];
}

int main() {
    int n = 100000;
    int *arr = (int*)malloc(n * sizeof(int));
    int *temp = (int*)malloc(n * sizeof(int));
    srand(time(NULL));

    FILE *fp = fopen("results.dat", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "# Dups StdTime RandTime StdComp RandComp StdDepth RandDepth\n");

    int percentages[] = {10, 50, 90}; 
    printf("\n=======================================================================\n");
    printf("PROBLEM 2: IMPACT OF DUPLICATE KEYS\n");
    printf("Comparing Standard vs Randomized Quicksort\n");
    printf("=======================================================================\n");
    printf("Type\t\tDups\tAlgo\t\tTime(s)\tComparisons\tMax Depth\n");
    printf("------------------------------------------------------------------------\n");

    for (int i = 0; i < 3; i++) {
        int pct = percentages[i];
        generate_with_duplicates(arr, n, pct);
        
        //1. Run Standard Quicksort 
        copy_array(arr, temp, n);
        comparison_count = 0; max_depth = 0; current_depth = 0;
        clock_t start = clock();
        standard_quicksort(temp, 0, n - 1);
        clock_t end = clock();
        
        double std_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        long long std_comp = comparison_count;
        int std_depth = max_depth;

        printf("Array-%d\t\t%d%%\tStandard\t%.4f\t%lld\t\t%d\n", i+1, pct, std_time, std_comp, std_depth);

        // 2. Run Randomized Quicksort
        copy_array(arr, temp, n);
        comparison_count = 0; max_depth = 0; current_depth = 0;
        start = clock();
        randomized_quicksort(temp, 0, n - 1);
        end = clock();

        double rand_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        long long rand_comp = comparison_count;
        int rand_depth = max_depth;

        printf("Array-%d\t\t%d%%\tRandomized\t%.4f\t%lld\t\t%d\n\n", i+1, pct, rand_time, rand_comp, rand_depth);

        // 3. Write Data Row to File
         fprintf(fp, "%d %f %f %lld %lld %d %d\n", pct, std_time, rand_time, std_comp, rand_comp, std_depth, rand_depth);
    }

    fclose(fp);
    printf("[SUCCESS] Data file 'results.dat' generated successfully.\n");

    free(arr); free(temp);
    return 0;
}