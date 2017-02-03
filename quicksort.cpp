#include "quicksort.h"


//Precondition: Arrary arr[b...t]
//Postcondition: Array arr is sorted in ascending order
//Note: Ave-case O( n*log(n) ), Worst-case O(n^2)
void quickSort(int * arr, int b, int t)
{
    if(b < t){
        int p = lomutoPartition(arr, b, t);
        quickSort(arr, b, p-1);
        quickSort(arr, p+1, t);
    }
}

int lomutoPartition(int * arr, int b, int t)
{
    int pivot = arr[b];
    int s = b;                          //Partition index, where arr[b..s-1] < arr[s] <= arr[s+1...t]
    int temp;

    for( int i = b + 1; i <= t; i++){

        if( arr[i] < pivot){
            s += 1;                     //increment partition index and swap arr[i] into 'less than' group
            temp = arr[i];              //... may result in unecessary swaps
            arr[i] = arr[s];
            arr[s] = temp;
        }
    }

    temp = arr[b];
    arr[b] = arr[s];                    //swap pivot into correct index
    arr[s] = temp;                     //... may result in unecessary swaps

    return s;                           //return partition index
}

//Precondition: ?
//Postcondition: Index p where subarray arr[b..t] is ordered | arr[b..s-1] <= b[s] <= arr[s+1...t] 
//Note: Ave-case O( n*log(n) ), Worst-case O(n^2)
int hoarePartition(int * arr, int b, int t)
{
    return 0;

}