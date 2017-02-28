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
//i.e. [8, 4, 6, 2, 7, 3, 5, 1] causes (n-1) compairsons
// at each level
int * initMergeWorst(int length)
{
    if (length == 1){
        int * baseArr = new int[1];
        baseArr[0] = 1;
        return baseArr;
    } else {
        int parity = (length % 2 == 0) ? 0 : 1;
        int half = length / 2;
        int * bottom = initMergeWorst(half);
        int * top = initMergeWorst(half + parity);

        int * arr = new int[length];
        for(int i = 0; i < half; i ++){         //fill worst-case array of length n
            arr[i] = bottom[i] * 2;             //evens on left
            arr[i+half] = (top[i] * 2) - 1;     //odds on right
        }
        if (parity){                            //for our odd lengthed arrays!
            arr[length-1] = top[half + parity - 1];
        }
        delete [] bottom;
        delete [] top;
        return arr;
    }
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