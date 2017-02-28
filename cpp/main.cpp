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

    clock_t runTime;                                     //timing variables
    clock_t testTime = clock();
    int runTimeAve = 0;                                  
    int runTimeTotal = 0;

    int * arr = NULL;                                    //data collection parameters
    int maxLen = 25;   
    int startLen = 15;
    int aveSetSize = 3;
    int stepSize = 2000;

    ofstream dataFile;                                     //file
    dataFile.open("/Users/andykeene/Desktop/cs350-project/localdata/ms(1-2000000)_initMergeWorst.csv");                   
    
    if (!dataFile.is_open()){
        cout << "Failed to open file\n";
        exit(-1);
    } else {
        dataFile << "\"length\"," << "\"ticks\"," << "\"seconds\"\n";
    }

    for (int currLen = startLen; currLen < maxLen; currLen += stepSize){        //begin data collection
        uniform_int_distribution<int> size_dist(0,5*currLen);                   //even dist. for all sizes
        cout << "running length: " << currLen << "...\n";                       //progress indicator

        for (int set = 1; set <= aveSetSize; set++){              
            
            //arr = initSortArr(currLen);
            arr = initRandArr(currLen, size_dist, generator);
            printArr(arr, currLen);
            //arr = initMergeWorst(currLen);     
            if(!arr){     
                cout << "error: allocation failed for " 
                     << currLen << endl;             
                exit(-1);
            }
            runTime = clock();
            mergeSortWrapper(arr, currLen);                                     //time merge sort
            //quickSort(arr, 0, currLen-1);                                     //time quick sort
            runTime = clock() - runTime;
            
            if (!isSorted(arr, currLen)){
                cout << "error: sort failed on length "
                     << currLen << endl;
                exit(-1);
            }

            delete[] arr;
            runTimeTotal += runTime;
        }

        runTimeAve = runTimeTotal / aveSetSize;
        dataFile << currLen << "," << runTimeAve << "," << ticksToSec(runTimeAve) << endl;         //Print length, ticks, seconds to file
        runTimeTotal = 0;
    }
    dataFile << "Total test time: " << ticksToSec(clock() - testTime) << endl;
    dataFile.close();
    return 0;
}
