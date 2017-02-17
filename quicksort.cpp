#include "quicksort.h"
#include "helpers.h"

//Precondition: Arrary arr[b...t]
//Postcondition: Array arr is sorted in ascending order
//Note: Ave-case O( n*log(n) ), Worst-case O(n^2)
void quickSort(int * arr, int b, int t)
{
    if(b < t){
        int p = hoarePartition(arr, b, t);
        quickSort(arr, b, p-1);
        quickSort(arr, p+1, t);
    }
}

//Precondition: Arrary arr[b...t]
//Postcondition: Index p of Array arr  arr[b...p-a] < arr[p] <= arr[p+1...t]
//Note: Ave-case O( n*log(n) ), Worst-case O(n^2)
int lomutoPartition(int * arr, int b, int t)
{
    int pivot = arr[b];                 //naive pivot selection
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

//Precondition: Arrary arr[b...t]
//Postcondition: Index p where subarray arr[b..t] is ordered | arr[b..p-1] <= b[p] <= arr[p+1...t] 
//Note: Ave-case O( n*log(n) ), Worst-case O(n^2)
int hoarePartition(int * arr, int b, int t)
{
    int i = b;                               //left->right index
    int j = t+1;                             //right->left index
    int temp;
    int pivot = arr[b];                      //naive pivot serves as sentinal in tradition Hoare partition

    do{

        do{                                  //scan right for elements greater than pivot
            i++;                             //using t, top, for sentinal
        } while( arr[i] < pivot && i < t);
        
        do {                                 //scan left for elements greater than pivot
            j--;
        } while(arr[j] > pivot);
      
        if( i <= j){                         //swap elements if indices haven't crossed
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }        
    } while (i < j);
                         
    temp = arr[j];                          // don't need to swap back due to i <= j in loop
    arr[j] = pivot;
    arr[b] = temp;

    return j;                               //partition is is always j
}


/** Original attempt


    cout << "[" << b << "..." << t << "]: ";
    printArr(arr, t+1);
    cout << endl << "i = " << i << "  j = " << j << endl << endl;


int i = b;                           //left->right index
    int j = t;                           //right->left index
    int temp;
    int pivot = arr[b];                  //naive pivot serves as sentinal in tradition Hoare partition

    while( i <= j){

        while(arr[i] < pivot && i < t){  //scan right for elements greater than pivot
            i++;                         //using t, top, for sentinal
        }
        while(arr[j] > pivot){           //scan left for elements greater than pivot
            j--;
        }
      
        
        if( i <= j){                     //swap elements if indices haven't crossed
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
        
    }

    //temp = arr[i];                    // don't need to swap back due to i <= j in loop
    //arr[i] = arr[j];
    //arr[j] = temp;

    temp = arr[j];
    arr[j] = pivot;
    arr[b] = temp;

    return j;                         //partition is is always j+1

**/