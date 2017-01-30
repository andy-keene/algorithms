#include <iostream>
#include <random>
#include <fstream>

using namespace std;

void mergeSort(int *, int, int);
void merge(int  *, int, int, int);
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
    //int * arr = initRandArr(length, size_dist, generator);   //new (nothrow) int[length];    
    int * arr = NULL;
    int * barr = initRandArr(length, size_dist, generator);
    


    int maxLength = 1000;                          //Data collection variables
    int startLength = 5;
    int averageSize = 7;
    int stepSize = 5;


    
    //Data collection
    for (int i = startLength; i < maxLength; i += stepSize){

        arr = initRandArr(i, size_dist, generator);     //init array of length i

        if(arr == NULL){                                //in case memory can't be allocated
            return -1;
        }

        //printArr(arr, i);                               //print for testing
        
        t = clock();                                    //time algorithm Merge Sort
        mergeSort(arr, 0, i-1);
        t = clock() - t;

        if (!isSorted(arr, i)){
            cout << "error: sort failed\n";
            exit(-1);
        }

        cout << "Mergesort for length " << i << " took " << t << " clicks, "
             << ticksToSec(t) << " seconds\n";

        msFile << i << "," << t << "," << ticksToSec(t) << endl;         //Print length, ticks, seconds to file

        delete[] arr;                                   //free mem
    }
    

    msFile.close();
    //delete[] arr;
    //printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
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

    -- print array
    for (int i = 0; i < length; i++){
        cout << arr[i] << endl;
    }

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
//Note: Ave of O( n*log(n) )
void mergeSort(int * arr, int b, int t)
{
    if (b < t){
        int m = (b + t) / 2;
        mergeSort(arr, b, m);
        mergeSort(arr, m+1, t);
        merge(arr, b, m, t);

    } //else { array of one is already sorted }
}

//Precondition: Given sorted sub-arrays [b..m] and [m+1..t] of Array arr
//Postcondition: Sorted sub-array [b...t]
void merge(int * arr, int b, int m, int t)
{
    int * barr = new (nothrow) int[t-b+1];          //allocate mem for array b s.t it can hold elements b through t
    if (barr == NULL){
        exit(-1);
    }
    int i = b;                                      //left sub array base index
    int j = m + 1;                                  //right sub array base index
    int k = 0;                                      //new array 'b' index


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

    k = 0;

    for(int l = b; l <= t; l++){                //Return elements to arr in sorted order
        arr[l] = barr[k++];
    }

    delete[] barr;                             //free array b mem
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