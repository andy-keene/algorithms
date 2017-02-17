#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
using namespace std;

void quickSort(int *, int, int);                                              //Quicksort

//Hoare Partition is incorrect
int hoarePartition(int*, int, int);
int lomutoPartition(int * arr, int, int);

#endif