/******************************************************************
*   Name:           Fabiola Villanueva                            *
*   Description:    Bucket Sort Algorithm                         *
*   Date:           Aug 25, 2024                                  *
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define SIZE 10

typedef struct {
    float arr[SIZE];                                //! polish later; redundancy
    int size;
} arrType;                                          //array list version3

typedef struct node {
    float data;
    struct node *link;
} *nodePtr;

typedef enum { TRUE, FALSE } Boolean;

Boolean initializeBucket (nodePtr B[]);
void displayBucket (nodePtr B[]);
void displayArray (arrType arrList);
arrType bucketSort (arrType inputList);               //passing the input data and the bucket array

int main (){
    system("CLS");
    printf("START\n");

    arrType inputList = { {0.42,0.75,0.32,0.12,0.85,0.67,0.24,0.93,0.56,0.48}, 10};
    
    printf("\n\n[INPUT ARRAY - unsorted]");
    displayArray (inputList);

    arrType outputList = bucketSort (inputList);
    printf("\n\n[OUTPUT ARRAY - sorted]");
    displayArray (outputList);

    printf("\n\nEND\n");
    return 0;
}

Boolean initializeBucket (nodePtr B[]) {
    int x;
    for (x = 0; x < MAX; ++x) {
        B[x] = NULL;
    }
    return (B[MAX-1] == NULL) ? TRUE: FALSE;        //just for good measure; for checking only
}

void displayBucket (nodePtr B[]) {
    printf("\n[BUCKETS]");

    int x;
    for (x = 0; x < MAX; ++x) {
        printf("\n[%d] :\t", x);
        if (B[x] == NULL) {
            printf("NULL");
        } else {
            nodePtr trav;
            for (trav = B[x]; trav != NULL; trav = trav->link) {
                printf("%.2f  ", trav->data);
            }
        }
    }
}

void displayArray (arrType arrList) {
    int x;
    for (x = 0; x < arrList.size; ++x) {
        printf("\n[%d] :: \t%.2f", x, arrList.arr[x]);
    }
    printf("\nSIZE:: %d", arrList.size);
}

arrType bucketSort (arrType inputList) {
    int x, idx, max = inputList.arr[0];
    
    for (x = 0; x < inputList.size; ++x) {                      //get max element
        if (inputList.arr[x] > max) {
            max = inputList.arr[x];
        }
    }

    nodePtr localBucket[inputList.size];                        //declaring and making of the buckets
    if (initializeBucket (localBucket) == TRUE) {
        printf("\nBuckets have been initialized to NULL.\n");
    } else {
        printf("\nERROR! Buckets are NOT initialized to NULL.\n");
    }

    nodePtr *trav, temp;                                        //insertion sort of elements into buckets
    for (x = 0; x < inputList.size; ++x) {
        idx = (int) (inputList.arr[x] * MAX);                   //! verify formula
        for (trav = &(localBucket[idx]); *trav != NULL && (*trav)->data <= inputList.arr[x]; trav = &(*trav)->link) {}
        temp = malloc (sizeof (struct node));
        if (temp != NULL) {
            temp->data = inputList.arr[x];
            temp->link = *trav;
            *trav = temp;
        }
    }
    displayBucket (localBucket);

    arrType outputList = {.size = inputList.size};                          //outputArray size is proportional inputArray size
    int a, b = 0;
    for (a = 0; a < MAX; ++a) {                                             //visit each bucket
        for (temp = localBucket[a]; temp != NULL; temp = temp->link) {      //visit each bucket list
            outputList.arr[b++] = temp->data;
        }
    }

    return outputList;
}