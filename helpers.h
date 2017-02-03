#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <random>
using namespace std;

bool isSorted(int *, int);
float ticksToSec(int);
int * initRandArr(int, uniform_int_distribution<int>&, mt19937&);             //must be passed by refference 
void printArr(int *, int);


#endif