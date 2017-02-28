#include "mergesort.h"
#include "helpers.h"

//Precondition: Arrary arr[0...length-1] of integers
//Postcondition: Array arr is sorted in ascending order
//Note: Wrapper is responsible for allocation of second array barr[0...length-1]
//      and call to mergeSort() to minimize space efficiency to O(n)

// ----- ADD NOTES HERE
// should I make them give indices so that I can sort any sub array?
bool mergeSortWrapper(int * arr, int length)
{
    int * barr = new (nothrow) int[length];

    if(!barr){
        return false;                       //failed to allocate second array
    } else {
        mergeSort(arr, barr, 0, length-1);        //kick off merge sort 
        delete[] barr;
        return true;
    }
}

//Precondition: Arrary arr[b...t], Array barr[b...t]
//Postcondition: Array arr[b...t] sorted in ascending order
//Note: Ave of O( n*log(n) )
void mergeSort(int * arr, int * barr, int b, int t)
{
    if (b < t){
        int m = (b + t) / 2;
        mergeSort(arr, barr, b, m);
        mergeSort(arr, barr, m+1, t);
        merge(arr, barr, b, m, t);

    } //else { array of one is already sorted }
}

//Precondition: Given sorted sub-arrays [b..m] and [m+1..t] of Array arr
//Postcondition: Sorted sub-array [b...t]
void merge(int * arr, int * barr, int b, int m, int t)
{
    int i = b;                                      //left sub array base index i
    int j = m + 1;                                  //right sub array base index j
    int k = b;                                      //new array 'b' index k

    while(i <= m && j <= t)
    {
        if (arr[i] < arr[j]){
            barr[k++] = arr[i++];
        } else {
            barr[k++] = arr[j++];                 //optionally, could be barr[k++] = arr[i] < arr[j] ? arr[i++] : arr[j++]; (ternary operator)
        }
    }

    while(i <= m){ barr[k++] = arr[i++];}
    while(j <= t){ barr[k++] = arr[j++];}
    k = b;                                      //reset barr index to original base

    for(int l = b; l <= t; l++){                //Return elements to arr in sorted order
        arr[l] = barr[k++];
    }

}
