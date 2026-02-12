#include <iostream>
#include <string>
using namespace std;

template <typename T>
//genericSort
void bubbleSort(T arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

template <typename T>
void printArray(T arr[], int n) {
    cout << "Sorted Array: [ ";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << " ]" << endl;
}

template <typename T>
void takeInput(T arr[], int n) {
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
}


int main() {
    int nInt;
    cout << "Integer Sort" << endl;
    cout << "Enter the number of integers: ";
    cin >> nInt;

    int* intArr = new int[nInt];

    takeInput(intArr, nInt);
    bubbleSort(intArr, nInt);
    printArray(intArr, nInt);

    delete[] intArr;
    cout << endl;

    int nDouble;
    cout << "Double Sort" << endl;
    cout << "Enter the number of doubles: ";
    cin >> nDouble;

    double* doubleArr = new double[nDouble];

    takeInput(doubleArr, nDouble);
    bubbleSort(doubleArr, nDouble);
    printArray(doubleArr, nDouble);

    delete[] doubleArr;
    cout << endl;

    int nString;
    cout << "String Sort" << endl;
    cout << "Enter the number of strings: ";
    cin >> nString;

    string* stringArr = new string[nString];

    takeInput(stringArr, nString);
    bubbleSort(stringArr, nString);
    printArray(stringArr, nString);

    delete[] stringArr;

    return 0;
}
