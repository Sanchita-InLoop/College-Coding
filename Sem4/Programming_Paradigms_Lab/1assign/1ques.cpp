#include<iostream>
#include<stdbool.h>
using namespace std;

int length (char str[]){
    int count = 0;
    while(str[count] != '\0'){
    count ++;
    }
    return count;
}

int stringcomparison(char s1[] , char s2[], int index){
    if(index == length(s1)){    
        return 0;
    }
    if(s1[index] == s2[index]){
        stringcomparison(s1,s2, index+1 );
    }
    else if(s1[index] >s2[index]){
        return 1;
    }
    return -1;
}

int largest(int nums[], int n){
    if(n == 1){
        return nums[0];
    }
    int max = largest(nums, n-1);
    if(max > nums[n-1]){
        return max;
    }
    else{
        return nums[n-1];
    }
    return 0;
}

bool search(int arr[],int n, int num, int i){
    if(i == n){
        return false;
    }
    if(arr[i] == num){
        return true;}
    else{
    search(arr,n,num, i+1);
    }
    return false;
}

void printReverse(int arr[],int n){
    if(n == 0){
        return;}
    cout<<arr[n-1]<<"\t";
    printReverse(arr,n-1);
}

bool palindrome(char str[],int n, int i){
    if(i >= n/2){
        return true;}
    if(str[i] == str [n-i-1]){
        return palindrome(str,n,i+1);
    }
    else{
        return false;
    }
}

int replaceChars(char str[], char c1,char c2,int i){
    if(i == length(str)){
        cout<<str<<"\n";
        return 1;}
    if(str[i] == c1){
        str[i] = c2;
    }
    return replaceChars(str,c1,c2,++i);
}

int sum(int arr[],int n){
    int ans =0;
    if(n == 0){
        return ans;
    }
    ans = arr[n-1] + sum(arr,n-1);
    return ans;
}

char lexicoSmallest(char str[], int i) {
    // base case
    if (i == length(str) - 1) {
        return str[i];
    }
    char smallestRest = lexicoSmallest(str, i + 1);
    if (str[i] < smallestRest) {
        return str[i];
    } else {
        return smallestRest;
    }
}

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
