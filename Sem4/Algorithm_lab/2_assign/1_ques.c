#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

void generateRandomArray(int *arr, int n) {
	srand(time(NULL));
	for (int i = 0; i < n; i++){
        arr[i] = rand();
	}
}

int thirdSmallest(int* arr,int n){
	int S3rd = INT_MAX;
	int S2nd = INT_MAX;
	int S1st = INT_MAX;
	for(int i=0; i<n;i++){
		if(S1st > arr[i]){
			S1st = arr[i];
			S2nd = S1st;
			S3rd = S2nd;
		}
		else if(S2nd > arr[i]){
			S3rd = S2nd;
			S2nd = arr[i];
		}
		else if(S3rd > arr[i]){
			S3rd = arr[i];
		}
	}
	return S3rd;
	
}

void printArray(int *arr, int n){
	for(int i=0 ; i<n ; i++){
		printf("%d \t", arr[i]);
	}
}

int fourthLargest(int * arr, int n){
	int L1st = INT_MIN;
	int L2nd = INT_MIN;
	int L3rd = INT_MIN;
	int L4th = INT_MIN;

	for(int i = 0; i<n; i++){
		if(L1st < arr[i]){
			L1st = arr[i];
			L2nd = L1st;
			L3rd = L2nd;
			L4th = L3rd;
		}
		else if(L2nd < arr[i]){
			L4th = L3rd;
			L3rd = L2nd;
			L2nd = arr[i];
		}
		else if(L3rd < arr[i]){
			L4th = L3rd;
			L3rd = arr[i];
		}
		else if(L4th < arr[i]){
			L4th = arr[i];
		}	
	}
	return L4th;
}

int main(){
	int n;
	printf("Enter the size of array: ");
	scanf("%d", &n);
	int * arr = (int*)malloc(sizeof(int)*n);
	generateRandomArray(arr,n);
	printArray(arr,n);
	printf("\nFourth Largest element : %d\n", fourthLargest(arr,n));
	printf("Third Smallest element : %d\n\n",thirdSmallest(arr,n));
	return 0;
}
