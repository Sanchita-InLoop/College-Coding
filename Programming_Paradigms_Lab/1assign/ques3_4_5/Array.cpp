#include"Array.h"
#include<iostream>
using namespace std;

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

int sum(int arr[],int n){
    int ans =0;
    if(n == 0){
        return ans;
    }
    ans = arr[n-1] + sum(arr,n-1);
    return ans;
}

