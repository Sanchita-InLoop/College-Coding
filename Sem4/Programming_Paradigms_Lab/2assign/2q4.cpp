#include <iostream>
#include <string>

template <typename T>
void genericSort(T arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        T temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

struct Student {
    int roll;
};

int main() {
    int intArr[] = {5, 2, 9, 1};
    genericSort(intArr, 4);

    double doubleArr[] = {3.5, 1.2, 7.8};
    genericSort(doubleArr, 3);

    Student stArr[2];
    genericSort(stArr, 2); // Compilation Error: operator< not defined
    return 0;
}