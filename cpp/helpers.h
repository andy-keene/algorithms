#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <random>
using namespace std;

int * initSortArr(int);
int * initMergeWorst(int);
bool isSorted(int *, int);
float ticksToSec(int);
//both must be passed by refference to avoid reseeding
int * initRandArr(int, uniform_int_distribution<int>&, mt19937&);
void printArr(int *, int);

#endif