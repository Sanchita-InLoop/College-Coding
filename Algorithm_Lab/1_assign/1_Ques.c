#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
void genAndStoreRandValues(const char* fname, int n) {
    FILE *file = fopen(fname, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", fname);
        return;
    }
    srand(time(NULL));
    printf("Generating and storing %d random values in %s\n", n, fname);
    for (int i = 0; i < n; i++) {
        int randomValue = rand();
        fprintf(file, "%d\n", randomValue);
    }
    fclose(file);

    printf("Successfully generated and stored %d values.\n", n);
}

void readAndDisplay(char* fname){
    int num;
    FILE *file = fopen(fname, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", fname);
        return;
    }
    while (fscanf(file, "%d", &num) == 1) {
        printf("%d\n", num);
    }
    fclose(file);
}

void printMaxMin(char* fname){
    FILE *file = fopen(fname, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", fname);
        return;
    }
    int num;
    int min = INT_MAX; 
    int max = INT_MIN;
    int found = 0;
    while (fscanf(file, "%d", &num) == 1) {
        if(num > max){
            max = num;
        }
        if(num < min){
            min = num;
        }
        found = 1;
    }
    fclose(file);
    if (found) {
        printf("Minimum value: %d\n", min);
        printf("Maximum value: %d\n", max);
    } else {
        printf("The file was empty or contained no valid numbers.\n");
    }
}
int main() {
    int n;
    printf("Enter n: ");
    scanf("%d",&n);
    genAndStoreRandValues("random_numbers.txt", n);
    readAndDisplay("random_numbers.txt");
    printMaxMin("random_numbers.txt");
    return 0;
}
