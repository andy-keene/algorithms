#include <iostream>
#include <random>
#include <fstream>
#include "quicksort.h"
#include "mergesort.h"
#include "helpers.h"

using namespace std;

int main(){
    random_device device;                                //psuedo-random number generator                     
    mt19937 generator(device());
    uniform_int_distribution<int> size_dist(0,0);

    clock_t runTime;                                     //timing variables
    int runTimeAve = 0;                                  
    int runTimeTotal = 0;

    int * arr = NULL;                                    //data collection parameters
    int maxLen = 50;   
    int startLen = 15;
    int aveSetSize = 1;
    int stepSize = 5;

    arr = new int[7];
    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 10;
    arr[3] = 6;
    arr[4] = 7;
    arr[5] = 7;
    arr[6] = 7;

    cout << "--Before sort: ";
    printArr(arr, 7);

    quickSort(arr, 0, 6);

    cout << "--After sort: ";
    printArr(arr, 7);

/*
    ofstream dataFile;                                     //file
    dataFile.open("/Users/andykeene/Downloads/mergesortData.csv");                   
    
    if (!dataFile.is_open()){
        cout << "Failed to open file\n";
        exit(-1);
    } else {
        dataFile << "\"length\"," << "\"ticks\"," << "\"seconds\"\n";
    }

    for (int currLen = startLen; currLen < maxLen; currLen += stepSize){        //begin data collection
        
        cout << "running length: " << currLen << "...\n";                       //progress indicator
        for (int set = 1; set <= aveSetSize; set++){              

            arr = initRandArr(currLen, size_dist, generator);     
            if(!arr){     
                cout << "error: allocation failed for " << currLen << endl;             
                exit(-1);
            }

            cout << "--Before sort: ";
            printArr(arr, currLen);


            runTime = clock();
            //mergeSortWrapper(arr, currLen);                                     //time merge sort
            quickSort(arr, 0, currLen-1);                                     //time quick sort
            runTime = clock() - runTime;

            if (!isSorted(arr, currLen)){
                cout << "error: sort failed\n";
                exit(-1);
            }

            cout << "--After sort: ";
            printArr(arr, currLen);


            delete[] arr;
            runTimeTotal += runTime;
        }


        runTimeAve = runTimeTotal / aveSetSize;
        dataFile << currLen << "," << runTimeAve << "," << ticksToSec(runTimeAve) << endl;         //Print length, ticks, seconds to file
        runTimeTotal = 0;
    }
    
    dataFile.close();

*/
    return 0;
}


/* LOL http://www.algolist.net/Algorithms/Sorting/Quicksort
void aaquickSort(int arr[], int left, int right) {
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];
 
   
      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };
 
  
      if (left < j)
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}
*/