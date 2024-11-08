/******************************************************************
*   Name:           Fabiola Villanueva                            *
*   Description:    Couting sort, Radix sort, Bucket sort,        *
*                   Gnome sort, Strand sort, Quick sort, &        *
*                   Merge sort
*   Date:           Aug 25, 2024                                  *
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

typedef struct {
    int *arrPtr;
    int count;
} arrList;

typedef enum { FALSE ,TRUE } Boolean;

void initList (arrList *L, int size);
void displayList (arrList L);
arrList countingSort (arrList L);
void radixSort (arrList L);
void mergeSort (arrList L, int low, int high);
void gnomeSort (arrList L);

void swap (int *a, int *b);

/******************************************************************
 *  Instructions: Only comment out the function call of a sorting *
 *  algorithm one at a time.                                      *
 ******************************************************************/

int main () {
    system("cls");
    printf("START\n\n");

    arrList minList, maxList;
    initList (&minList, MAX_SIZE);
    initList (&maxList, MAX_SIZE);

    int tempMinList[] = {4, 2, 2, 8, 3, 3, 1, 4, 2, 2};
    int tempMaxList[] = {909, 233, 12, 54, 909, 605, 23, 94, 1, 10};

    int x;
    for (x = 0; x < MAX_SIZE; x++) {
        minList.arrPtr[x] = tempMinList[x];
        maxList.arrPtr[x] = tempMaxList[x];
    }

    printf("\nINPUT ARRAY::\n");
    printf("minArr = ");
    displayList (minList);
    printf("maxArr = ");
    displayList (maxList);

    // printf("\nCOUNTING SORT::\n");
    // minList = countingSort (minList);
    // displayList (minList);

    // printf("\nRADIX SORT::\n");
    // radixSort (maxList);
    // displayList (maxList);

    // printf("\nMERGE SORT::\n");
    // mergeSort (maxList, 0, maxList.count - 1);          // pass the front and the rear
    // displayList (maxList);

    printf("\nGNOME SORT::\n");
    gnomeSort (minList);
    displayList (minList);

    printf("\n\nEND");
    return 0;
}

void initList (arrList *L, int size) {
    L->arrPtr = malloc (sizeof (int) * size);
    if (L->arrPtr != NULL) {
        L->count = MAX_SIZE;                            // made default
    }
}

void displayList (arrList L) {
    int x;
    printf("{");
    for (x = 0; x < L.count; ++x ) {
        printf("%d", L.arrPtr[x]);
        if (x < L.count-1) {
            printf(", ");
        }
    }
    printf("}\n");
}

arrList countingSort (arrList L) {
    int x, maxVal;
    for (x = 0, maxVal = L.arrPtr[0]; x < L.count; ++x) {   // determine the maximum element
        if (L.arrPtr[x] > maxVal) {
            maxVal = L.arrPtr[x];
        }
    }
    printf("Max Value [%d]\n", maxVal);

    arrList temp;                                           // create count array
    initList (&temp, maxVal);
    temp.count = maxVal + 1;

    for (x = 0; x < maxVal; ++x)                            // initialize count array to zero
        temp.arrPtr[x] = 0;

    for (x = 0; x < L.count; ++x)                           // count frequencies
        temp.arrPtr[L.arrPtr[x]]++;

    for (x = 1; x < temp.count; ++x)                        // get prefix sum
        temp.arrPtr[x] += temp.arrPtr[x - 1];

    arrList outputL = {.count = L.count};
    initList (&outputL, MAX_SIZE);

    for (x = L.count - 1; x >= 0; --x)                        // populate your output array
        outputL.arrPtr[--(temp.arrPtr[L.arrPtr[x]])] = L.arrPtr[x];

    return outputL;
}

void radixSort (arrList L) {
    int x, maxVal = L.arrPtr[0];
    for (x = 0; x < L.count;  ++x) {                        // determine the max value
        if (L.arrPtr[x] > maxVal)
            maxVal = L.arrPtr[x];
    }
    printf("Max Value [%d]\n", maxVal);
    
    int base;
    for (base = 1; maxVal / base > 0; base *= 10) {         // implement counting sort
        int countArr[10] = {0};                             // digits 0-9 only
        int outputArr[L.count];

        for (x = 0; x < L.count; ++x)                       // populate count array
            countArr[(L.arrPtr[x] / base) % 10]++;

        for (x = 1;  x < 10; ++x)                           // get prefix sum
            countArr[x] += countArr[x - 1];

        for (x = L.count - 1; x >= 0; --x)                  // map and sort each element into output
            outputArr[--(countArr[(L.arrPtr[x] / base) % 10])] = L.arrPtr[x];

        for (x = 0; x < L.count; ++x)                       // make output new input for next iteration
            L.arrPtr[x] = outputArr[x];
    }
}

void mergeSort (arrList L, int low, int high) {
    if (low >= high) {
        return;
    }

    int middle = (low + high) / 2;
    mergeSort (L, low, middle);             // left branch; reach the leaf (1 sized array)
    mergeSort (L, middle + 1, high);        // right branch; reach the leaf (1 sized array)

    int leftSize = middle - low + 1;
    int rightSize = high - middle;
    int a, b, c;

    int leftArr[leftSize], rightArr[rightSize];

    for (a = 0; a < leftSize; ++a)          // populate left temp arr
        leftArr[a] = L.arrPtr[low + a];
    
    for (a = 0; a < rightSize; ++a)         // populate right temp arr
        rightArr[a] = L.arrPtr[middle + 1 + a];

    for (a = 0, b = 0, c = low; a < leftSize && b < rightSize; ++c) {
        if (leftArr[a] < rightArr[b]) {
            L.arrPtr[c] = leftArr[a++];
        } else {
            L.arrPtr[c] = rightArr[b++];
        }
    }                                       // the comparison and sorting stops when we've iterated through a branch

    while (a < leftSize)                    // copy remaining elements of whichever we haven't iterated through
        L.arrPtr[c++] = leftArr[a++];

    while (b < rightSize) 
        L.arrPtr[c++] = rightArr[b++];
}

void gnomeSort (arrList L) {
    int x = 1;
    while ( x < L.count) {
        if (L.arrPtr[x] < L.arrPtr[x - 1]) {        // look back version
            swap (&L.arrPtr[x], &L.arrPtr[x - 1]);
            if (x > 1)
                --x;
        } else {
            ++x;
        }
    }
}

void swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}