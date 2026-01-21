#include<iostream>
#include"recursion.h"
using namespace std;

int main() {
    int choice;

    do {
        cout << "\n----- MENU -----\n";
        cout << "1. String comparison\n";
        cout << "2. Largest element in array\n";
        cout << "3. Search element in array\n";
        cout << "4. Print array in reverse\n";
        cout << "5. Check palindrome\n";
        cout << "6. Replace characters in string\n";
        cout << "7. Sum of array elements\n";
        cout << "8. Lexicographically smallest character\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {

            case 1: {
                char s1[100], s2[100];
                cout << "Enter first string: ";
                cin >> s1;
                cout << "Enter second string: ";
                cin >> s2;

                if (length(s1) != length(s2)) {
                    cout << "Strings are not equal\n";
                } else {
                    cout << "Comparison result = "
                         << stringcomparison(s1, s2, 0) << endl;
                }
                break;
            }

            case 2: {
                int n;
                cout << "Enter number of elements: ";
                cin >> n;
                int arr[100];
                cout << "Enter elements: ";
                for (int i = 0; i < n; i++)
                    cin >> arr[i];

                cout << "Largest element = "
                     << largest(arr, n) << endl;
                break;
            }

            case 3: {
                int n, key;
                cout << "Enter number of elements: ";
                cin >> n;
                int arr[100];
                cout << "Enter elements: ";
                for (int i = 0; i < n; i++)
                    cin >> arr[i];

                cout << "Enter element to search: ";
                cin >> key;

                cout << boolalpha
                     << search(arr, n, key, 0) << endl;
                break;
            }

            case 4: {
                int n;
                cout << "Enter number of elements: ";
                cin >> n;
                int arr[100];
                cout << "Enter elements: ";
                for (int i = 0; i < n; i++)
                    cin >> arr[i];

                printReverse(arr, n);
                cout << endl;
                break;
            }

            case 5: {
                char str[100];
                cout << "Enter string: ";
                cin >> str;
                cout << boolalpha
                     << palindrome(str, length(str), 0) << endl;
                break;
            }

            case 6: {
                char str[100], c1, c2;
                cout << "Enter string: ";
                cin >> str;
                cout << "Enter character to replace: ";
                cin >> c1;
                cout << "Enter new character: ";
                cin >> c2;

                replaceChars(str, c1, c2, 0);
                break;
            }

            case 7: {
                int n;
                cout << "Enter number of elements: ";
                cin >> n;
                int arr[100];
                cout << "Enter elements: ";
                for (int i = 0; i < n; i++)
                    cin >> arr[i];

                cout << "Sum = " << sum(arr, n) << endl;
                break;
            }

            case 8: {
                char str[100];
                cout << "Enter string: ";
                cin >> str;
                cout << "Lexicographically smallest character = "
                     << lexicoSmallest(str, 0) << endl;
                break;
            }

            default:
                cout << "Invalid choice\n";
        }

    } while (choice != 0);

    return 0;
}

