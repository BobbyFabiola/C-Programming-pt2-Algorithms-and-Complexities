/******************************************************************
*   Name:           Fabiola Villanueva                            *
*   Description:    Bubble Sort, Insertion Sort, Selection Sort   *
                    Shell Sort, Comb Sort, Heap Sort, Tournament  *
                    Sort                                          *
*   Date:           Aug 25, 2024                                  *
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef enum { FALSE ,TRUE } Boolean;

void displayArr (int arr[]);
void swap (int *x, int *y);
void bubbleSort (int arr[]);
void insertionSort (int arr[]);
void selectionSort (int arr[]);
void shellSort (int arr[]);
void combSort (int arr[]);
void heapSort (int arr[], int lastIdx);
// void tournamentSort ();

void heapify (int arr[], int lastIdx, int sRoot);
int deleteMax (int arr[], int *lastIdx);                                //return the root and modify the last index

/******************************************************************
 *  Instructions: Only comment out the function call of a sorting *
 *  algorithm one at a time.                                      *
 ******************************************************************/

int main () {
    system("cls");
    printf("\nSTART\n\n");

    int arrM[MAX] = {99, 33, 12, 54, 88, 65, 23, 94, 11, 10};
    // int arrM[MAX] = {9, 8, 5, 3, 1};
    
    printf("\nINPUT ARRAY::\n");
    displayArr (arrM);
    
    // printf("\nBUBBLE SORT::\n");
    // bubbleSort (arrM);
    // displayArr (arrM);

    // printf("\nINSERTION SORT::\n");
    // insertionSort (arrM);
    // displayArr (arrM);

    // printf("\nSELECTION SORT::\n");
    // selectionSort (arrM);
    // displayArr (arrM);

    // printf("\nSHELL SORT::\n");
    // shellSort (arrM);
    // displayArr (arrM);

    // printf("\nCOMB SORT::\n");
    // combSort (arrM);
    // displayArr (arrM);

    printf("\nHEAP SORT::\n");
    heapSort (arrM, MAX-1);
    displayArr (arrM);

    printf("\n\nEND\n");
    return 0;
}

void displayArr (int arr[]) {
    int x;
    printf("{");
    for (x = 0; x < MAX; ++x ) {
        printf("%d", arr[x]);
        if (x < MAX-1) {
            printf(", ");
        }
    }
    printf("}\n");
}

void swap (int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSort (int arr[]) {
    int a, b;
    for (a = 0; a < MAX-1; ++a) {               //optimized to avoid an extra pass
        for (b = 0; b < MAX-a-1; ++b) {
            if (arr[b] > arr[b+1]) {            //compare adjacent elements
                swap (&arr[b], &arr[b+1]);
            }
        }
    }
}

void insertionSort (int arr[]) {
    int a, b, key;
    for (a = 1; a < MAX; ++a) {
        key = arr[a];                           //compare with previous element
        for (b = a-1; b >= 0 && arr[b] > key; --b) {
            arr[b+1] = arr[b];                  //shift if necessary
        }
        arr[b+1] = key;                         //place key in position
    }
}

void selectionSort (int arr[]) {
    int a, b;
    for (a = 0; a < MAX-1; ++a) {               //we assume last element as sorted
        int minIdx = a;
        for (b = a+1; b < MAX; ++b) {           //find the next minimum element
            if (arr[b] < arr[minIdx]) {
                minIdx = b;
            }
        }
        swap (&arr[a], &arr[minIdx]);
    }
}

void shellSort (int arr[]) {                    //extended from insertion sort
    int a, b, gap;
    for (gap = MAX / 2; gap > 0; gap /= 2) {
        for (a = gap; a < MAX; ++a)  {                                  //gap variable 'a' iterates forward
            int temp = arr[a];                                          //the element to put into its right position
            for (b = a; b >= gap && arr[b - gap] > temp; b -= gap) {    //shifting elements that are gap distances apart
                arr[b] = arr[b - gap];                                  //the farthest b can go is comparing index gap to index 0
            }
            arr[b] = temp;
        }
    }
}

void combSort (int arr[]) {
    int x, gap = MAX;                                       //gap will be initialized to be dependent to size
    Boolean isSwapped = TRUE;                               //assume as the array to be unsorted
    while (gap != 1 || isSwapped == TRUE) {                 //takes into account if gap is < 1; if unsorted then keep sorting
        gap /= 1.3;                                         //new gap per iteration
        if (gap < 1) {                                      //if gap is 0 then make 1
            gap = 1;
        }
        isSwapped = FALSE;                                  //new gap, set isSwapped to false 
        for (x = 0; x < MAX-gap; ++x) {                     //iterate x only until MAX-gap because you compare it with x
            if (arr[x] > arr[x + gap]) {                    //comparing between index x and x+gap
                swap (&arr[x], &arr[x + gap]);
                isSwapped = TRUE;                           //if isSwapped is TRUE then it inidicates an unsorted portion
            }
        }
    }
}

void heapSort (int arr[], int lastIdx) {
    int x;
    for (x = (lastIdx - 1) /2; x >= 0; --x) {               //starting from the lowest level subtree
        heapify (arr, lastIdx, x);                          //make array into a heap
    }
    while (lastIdx > 0) {
        arr[lastIdx] = deleteMax (arr, &lastIdx);
    }
}

void heapify (int arr[], int lastIdx, int sRoot) {
    int idx, trav;                                                          //idx shall be the element to swap with trav
    for (idx = trav = sRoot; ((2 * trav) + 1) <= lastIdx; trav = idx) {     //for as long as there is at least a left child present
        if (((2 * trav) + 2) <= lastIdx) {                                  //if a right child exists, then check
            idx = (arr[(2 * trav) + 2] > arr[trav]) ? (2 * trav) + 2: trav; //assign the index between right child and parent
        }
        idx = (arr[(2 * trav) + 1] > arr[idx]) ? (2 * trav) + 1: idx;       //assign the index between left child and idx (possibly parent itself or right child)
        if (idx != trav) {
            int temp = arr[idx];
            arr[idx] = arr[trav];
            arr[trav] = temp;
        } else {
            idx = lastIdx;
        }
    }
}

int deleteMax (int arr[], int *lastIdx) {
    int temp = arr[0];                      //assign the root to a variable
    arr[0] = arr[(*lastIdx)--];             //overwrite with a new root (the last element in the heap)
    heapify (arr, *lastIdx, 0);             //push down the new root
    return temp;                            //return the previous root
}



