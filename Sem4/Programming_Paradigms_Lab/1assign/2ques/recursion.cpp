#include<iostream>
#include"recursion.h"
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

