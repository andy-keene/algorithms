#include <iostream>
#include <random>
#include <fstream>

using namespace std;

void quickSort(int *, int, int);                                              //Quicksort
int hoarePartition(int*, int, int);
int lomutoPartition(int * arr, int, int);

bool mergeSortWrapper(int *, int);      
void mergeSort(int *, int *, int, int);                                              //Mergesort
void merge(int  *, int *, int, int, int);
bool isSorted(int *, int);
float ticksToSec(clock_t);
int * initRandArr(int, uniform_int_distribution<int>&, mt19937&);             //must be passed by refference 
void printArr(int *, int);



int main(){

    //Non deterministic random number generator & instantiation
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> size_dist(0,1000);
    clock_t t;


    ofstream msFile;
    msFile.open("/Users/andykeene/Downloads/mergesortData.csv");                              //msFile = mergesort File
    if (!msFile.is_open()){
        cout << "Failed to open file";
        exit(-1);
    } else {
        msFile << "\"Length\"," << "\"Ticks\"," << "\"Seconds\"\n"; 
    }

    
    int length = 20;
    int * arr = NULL;
    


    int maxLength = 25;                          //Data collection variables
    int startLength = 2;
    int averageSize = 7;
    int stepSize = 2;


    
    //Data collection
    for (int i = startLength; i < maxLength; i += stepSize){

        arr = initRandArr(i, size_dist, generator);     //init array of length i

        if(!arr){                                       //in case memory can't be allocated
            return -1;
        }

        //cout << "Before sort -- ";
        //printArr(arr, i);                                 //print for testing

        t = clock();                                      //time algorithm Merge Sort
        //mergeSort(arr, 0, i-1);
        //mergeSortWrapper(arr, i);
        quickSort(arr, 0, i-1);
        t = clock() - t;

        if (!isSorted(arr, i)){
            cout << "error: sort failed\n";
            printArr(arr, i);
            //exit(-1);
        }

        //cout << "After sort -- ";
        //printArr(arr, i);                                 //print for testing
        cout << "Mergesort for length " << i << " took " << t << " clicks, "
             << ticksToSec(t) << " seconds\n";

        msFile << i << "," << t << "," << ticksToSec(t) << endl;         //Print length, ticks, seconds to file

        delete[] arr;                                   //free mem
    }
    

    msFile.close();
    return 0;
}


// prints array as "Length[n]: 1, 2, 3, ... n"
void printArr(int * arr, int length)
{
    cout << "Length [" << length << "]: ";

    for (int i = 0; i < length; i++){
        cout << arr[i] << ", ";
    }

    cout << endl;
}



//Precondition: Given length of array to create, a device and mt19937 psuedo-random number generator 
//Post-condition: Retuns pointer to an array initialized with random integers for the given length 
//                (size_dist and generator MUST be passed by refference to avoid psuedo-random path repetition)
int * initRandArr(int length, uniform_int_distribution<int> &size_dist, mt19937 &generator)
{
    int * arr = new (nothrow) int[length];

    if (!arr){                       //failed to generate list of length n
        return NULL;
    } else {
        
        for(int i = 0; i < length; i++){
            arr[i] = size_dist(generator);
        }

        return arr;
    }
}


// Converts clock object's tick-time to seconds
float ticksToSec(clock_t t)
{
    return ((float)t)/CLOCKS_PER_SEC;
}

/* --- Holding Tank ----


    -- test different array allocations
    if( arr ){

        cout << "Array A\n";

        for (int i = 0; i < length; i++){
            cout << arr[i] << endl;
        }

        cout << "Array B\n";
        for (int i = 0; i < length; i++){
            cout << barr[i] << endl;
        }
    } else {
        cout << "init array FAILED";
    }


*/


//Precondition: Arrary arr[b...t]
//Postcondition: Array arr is sorted in ascending order
//Note: Ave-case O( n*log(n) ), Worst-case O(n^2)
void quickSort(int * arr, int b, int t)
{
    if(b < t){
        //p = hoarePartition(arr, b, t)         //Partition
        //quickSort(arr, b, p-1)                //Sort b..p-1
        //quickSort(arr, p+1, t)                //sort p+1, t
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

//Precondition: Initialized array, arr[0...length-1]
//Postcondition: True if arr is sorted, flase if else
bool isSorted(int * arr, int length)
{

    for(int i = 0; i < length - 1; i++){

        if( !(arr[i] <= arr[i+1]) ){
            return false;
        }
    }

    return true;
}