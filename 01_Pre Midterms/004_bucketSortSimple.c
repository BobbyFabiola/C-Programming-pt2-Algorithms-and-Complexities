/******************************************************************
*   Name:           Fabiola Villanueva                            *
*   Description:    Bucket Sort Algorithm but less complex        *
*   Date:           Aug 25, 2024                                  *
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct node {
    float data;
    struct node *link;
} *nodePtr;
typedef float elemType;

void displayArr (elemType arr[]);
void displayBucket (nodePtr B[], int size);
void bucketSort (elemType inputArr[], elemType outputArr[]);

int main () {
    system("CLS");
    printf("START\n");

    int x;
    elemType inputArr[MAX] = {0.42, 0.65, 0.32, 0.12, 0.12, 0.67, 0.24, 0.93, 0.66, 0.48};
    elemType outputArr[MAX];

    printf("\n[ INPUT ARRAY ]\n");
    displayArr (inputArr);
    
    bucketSort (inputArr, outputArr);

    printf("\n\n[ OUTPUT ARRAY ]\n");
    displayArr (outputArr);

    printf("\n\nEND\n\n");
    return 0;
}

void displayArr (elemType arr[]) {
    int x;
    printf("{");
    for (x = 0; x < MAX; ++x) {
        printf("%.2f", arr[x]);
        if (x < MAX - 1) {
            printf(", ");
        }
    }
    printf("}");
}

void displayBucket (nodePtr B[], int size) {
    printf("\n\n[ LOCAL BUCKET ]");
    int a;
    for (a = 0; a < size; ++a) {
        printf("\n[%2d] ::", a);
        if (B[a] != NULL) {
            nodePtr trav;
            for (trav = B[a]; trav != NULL; trav = trav->link) {
                printf(" %.2f ", trav->data);
            }
        } else {
            printf(" ~ ");
        }
    }
}

void bucketSort (elemType inputArr[], elemType outputArr[]) {
    //! find the maximum element from the input array
    int x;
    elemType maxVal = inputArr[0], minVal = inputArr[0];
    for (x = 1; x < MAX; ++x) {
        if (inputArr[x] > maxVal) maxVal = inputArr[x];
        if (inputArr[x] < minVal) minVal = inputArr[x];
    }

    //! declare bucket array or an array of node pointers
    int bucketSize = (maxVal - minVal) * 10;
    nodePtr localBucket[bucketSize];                
    for (x = 0; x < bucketSize; ++x) {
        localBucket[x] = NULL;
    }
    displayBucket (localBucket, bucketSize);
    
    //! placing each element into the buckets
    nodePtr *trav, temp;
    for (x = 0; x < MAX; ++x) {
        int idx = (int) ((inputArr[x] - minVal) * (bucketSize - 1) / (maxVal - minVal));
        for (trav = &localBucket[idx]; *trav != NULL && (*trav)->data <= inputArr[x]; trav = &(*trav)->link) {}
        temp = malloc (sizeof (struct node));
        if (temp != NULL) {
            temp->data = inputArr[x];
            temp->link = *trav;
            *trav = temp;
        }
    }
    displayBucket (localBucket, bucketSize);

    //! concatenating the list for each bucket into the output array
    int a, b = 0;                       
    for (a = 0; a < bucketSize; ++a) {
        for (temp = localBucket[a]; temp != NULL; temp = temp->link) {
            outputArr[b++] = temp->data;
        }
    }
}