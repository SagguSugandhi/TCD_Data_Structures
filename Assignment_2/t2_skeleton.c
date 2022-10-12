#include <stdio.h> 
#include "t2.h"

int number_comparisons = 0;
int number_swaps = 0;


void selectionSort(int arr[], int size) 
{ 
  for(int i =0;i<size-1;i++) {
    int Min = i;
    for(int j=i+1;j<size;j++) {
      number_comparisons++;
      if(arr[j] < arr[Min]) {
        Min = j;
      }
    }
    int temp = arr[i];
    arr[i] = arr[Min];
    arr[Min] = temp;
    number_swaps++;
  }
} 

void insertionSort(int arr[], int size) 
{ 
  int value,k;
  for(int i=1;i<size;i++) {
    value = arr[i];
    k = i;
    while(k>0 && arr[k-1] > value) {
      arr[k] = arr[k-1];
      k--;
      number_comparisons++;
    }
    arr[k] = value;
    number_swaps++;
  }
  
}

void quickSort(int arr[], int size) {
	    int index = 0;
        int pivot = arr[size-1];
        int i;
        for ( i = 0; i < size-1; i++){
        	number_comparisons++;
        	if (arr[i] < pivot)
            {
                int temp = arr[i];
                arr[i] = arr[index];
                arr[index]  = temp;
                index++;
                number_swaps++;
                }
        }
        int temp = arr[index];
        arr[index] = arr[size-1];
        arr[size-1] = temp;
        if (index> 1)
                quickSort(arr, index);
        if (size-index-1 > 1)
                quickSort(arr+index+1, size-index-1);
}