#include <iostream>
#include <random>
#include <fstream>
#include "quicksort.h"
#include "mergesort.h"
#include "helpers.h"

using namespace std;

int qsAveRunTime(int, int);
int msAveRunTime(int, int);


int main(){
    //Non deterministic random number generator & instantiation
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> size_dist(0,1000);
    
    int msTimeAve = 0;                      //Both averages will hold ticks
    int qsTimeAve = 0;
    int msTimeTotal = 0;
    int qsTimeTotal = 0;
    //clock_t msTime;
    //clock_t qsTime;
    clock_t runTime;
    ofstream msFile;
    ofstream qsFile;

    int * arr = NULL;
    int maxLen = 25;                          //Data collection variables
    int startLen = 2;
    int aveSetSize = 7;
    int stepSize = 2;


    msFile.open("/Users/andykeene/Downloads/mergesortData.csv");                   //msFile = mergesort File
    qsFile.open("/Users/andykeene/Downloads/quicksortData.csv");                   //qsFile = quicksort File
    
    if (!msFile.is_open() || !qsFile.is_open()){
        cout << "Failed to open files\n";
        exit(-1);
    } 



    //Data collection
    for (int currLen = startLen; currLen < maxLen; currLen += stepSize){

        cout << "running length: " << currLen << "...\n";                       //progress indicator

        for (int set = 1; set <= aveSetSize; set++){                            // --- merge sort---
            arr = initRandArr(currLen, size_dist, generator);     
            if(!arr){     
                cout << "error: allocation failed for " << currLen << endl;             
                exit(-1);
            }

            runTime = clock();
            mergeSortWrapper(arr, currLen);                                     //time run
            runTime = clock() - runTime;

            if (!isSorted(arr, currLen)){
                cout << "error: sort failed\n";
                exit(-1);
            }
            delete[] arr;
            msTimeTotal += runTime;
        }

        for (int set = 1; set <= aveSetSize; set++){                            // --- merge sort---
            arr = initRandArr(currLen, size_dist, generator);     
            if(!arr){     
                cout << "error: allocation failed for " << currLen << endl;             
                exit(-1);
            }

            runTime = clock();
            quickSort(arr, 0, currLen-1);                                            //time run
            runTime = clock() - runTime;

            if (!isSorted(arr, currLen)){
                cout << "error: sort failed\n";
                exit(-1);
            }
            delete[] arr;
            qsTimeTotal += runTime;
        }


        


        
        msTimeAve = msTimeTotal / aveSetSize;
        qsTimeAve = qsTimeTotal / aveSetSize;
        msFile << currLen << "," << msTimeAve << "," << ticksToSec(msTimeAve) << endl;         //Print length, ticks, seconds to file
        qsFile << currLen << "," << qsTimeAve << "," << ticksToSec(qsTimeAve) << endl;         //Print length, ticks, seconds to file
    }
    

    qsFile << "Successful run\n";
    msFile << "Successful run\n";
    qsFile.close();
    msFile.close();
    return 0;
}


//cout << "Before sort -- ";
        //printArr(arr, i);                                 //print for testing


