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
    return 0;
}
