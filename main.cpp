#include <iostream>
#include <random>


void mergeSort(int *, int, int);
void merge(int  *, int, int, int);
bool isSorted(int *, int);
using namespace std;

int main(){

    //Non deterministic random number generator & instantiation
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<int> size_dist(0,10000);
    clock_t t;
    
    int length = 10000;
    int * arr = new (nothrow) int[length];    

    int maxLength = 0;                          //Data collection variables
    int startLength = 0;
    int averageSize = 0;
    int stepSize = 0;

    if(arr == NULL){                            //in case memory can't be allocated
        return -1;
    }

    for (int i = 0; i < length; i++){
    	arr[i] = size_dist(generator);
    }

    //Data collection

    cout << "--- Before sort --- \n";

    t = clock();

    mergeSort(arr, 0, length-1);

    t = clock() - t;

    if (!isSorted(arr, length)){
        cout << "Failed to sort";
    }
    cout << "--- After sort --- \n";

   
    delete[] arr;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    return 0;
}

/* --- Holding Tank ----

    -- print array
    for (int i = 0; i < length; i++){
        cout << arr[i] << endl;
    }


*/

//Precondition:
//Postcondition: 
//Note:
void mergeSort(int * arr, int b, int t)
{
    if (b < t){
        int m = (b + t) / 2;
        mergeSort(arr, b, m);
        mergeSort(arr, m+1, t);
        merge(arr, b, m, t);

    } else {
        //cout << "Base case: arr[" << b << "] = " << arr[b] << "\n";
    }
}

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

bool isSorted(int * arr, int length)
{

    for(int i = 0; i < length - 1; i++){

        if( !(arr[i] <= arr[i+1]) ){
            return false;
        }
    }

    return true;
}