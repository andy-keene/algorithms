#include "helpers.h"


// prints array as "Length[n]: 1, 2, 3, ... n"
void printArr(int * arr, int length)
{
    //cout << "Length [" << length << "]: ";

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

//Returns a sorted array, arr[0...length-1]
int * initSortArr(int length)
{
    int * arr = new (nothrow) int[length];
    if(!arr){
        return NULL;
    }
    for (int i = 0; i < length; i++){
        arr[i] = i;
    }
    return arr;
}

//returns an array which induces mergesorts worst-case
//i.e. [2, 4, 6, 8, 1, 3, 5, 7]
//     [2, 4, 6] [1, 3, 7] 
int * initMergeWorst(int length)
{
    int * arr = new (nothrow) int[length];
    if(!arr){
        return NULL;
    }

    int half = length / 2;
    int num = 1;
    for (int i = 0; i < half; i++){
        arr[i] = num * 2;               //evens sorted
        arr[i+half] = (num * 2) - 1;    //odds sorted
        num +=1;
    }
    if(length % 2 != 0){        //if not even, last element was not filled
        arr[length-1] = (num*2) - 1;
    }
    return arr;
}

// Converts tick-time to seconds
float ticksToSec(int t)
{
    return ((float)t)/CLOCKS_PER_SEC;
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