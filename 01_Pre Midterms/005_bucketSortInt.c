/******************************************************************
*   Name:           Fabiola Villanueva                            *
*   Description:    Bucket Sort Algorithm but less complex        *
*   Date:           Aug 25, 2024                                  *
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX 15

typedef struct node {
    int data;
    struct node *link;
} *nodePtr;
typedef int elemType;

void displayArr (elemType arr[]);
void displayBucket (nodePtr B[], int size);
void bucketSort (elemType arr[]);

int main () {
    system("CLS");
    printf("START\n");

    int x;
    elemType arr[MAX] = {25, 73, 39, 15, 61, 37, 58, 64, 62, 10, 44, 32, 67, 20, 12};

    printf("\n[ INPUT ARRAY ]\n");
    displayArr (arr);
    
    bucketSort (arr);

    printf("\n\n[ OUTPUT ARRAY ]\n");
    displayArr (arr);

    printf("\n\nEND\n\n");
    return 0;
}

void displayArr (elemType arr[]) {
    int x;
    printf("{");
    for (x = 0; x < MAX; ++x) {
        printf("%d", arr[x]);
        if (x < MAX - 1) {
            printf(", ");
        }
    }
    printf("}");
}

void displayBucket (nodePtr B[], int size) {
    printf("\n\n[ LOCAL BUCKET - SIZE %d ]", size );
    int a;
    for (a = 0; a < size; ++a) {
        printf("\n[%2d] ::", a);
        if (B[a] != NULL) {
            nodePtr trav;
            for (trav = B[a]; trav != NULL; trav = trav->link) {
                printf(" %d ", trav->data);
            }
        } else {
            printf(" ~ ");
        }
    }
}

void bucketSort (elemType arr[]) {
    int x;                                                  //! find the maximum and minimum element from the input array
    elemType maxVal = arr[0], minVal = arr[0];
    for (x = 1; x < MAX; ++x) {
        if (arr[x] > maxVal) maxVal = arr[x];
        if (arr[x] < minVal) minVal = arr[x];
    }

    printf("\n\nMIN = %d :: MAX = %d", minVal, maxVal);

    int bucketSize = (maxVal - minVal) / MAX;               //! declare bucket array or an array of node pointers
    nodePtr localBucket[bucketSize];                        //* integer for getting bucket size
    for (x = 0; x < bucketSize; ++x) {
        localBucket[x] = NULL;
    }
    displayBucket (localBucket, bucketSize);
    
    nodePtr *trav, temp;                                    //! placing each element into the buckets
    for (x = 0; x < MAX; ++x) {                             //* integer formula for indexing; inserted sorted
        int idx =  (arr[x] - minVal) * (bucketSize) / (maxVal - minVal + 1);
        for (trav = &localBucket[idx]; *trav != NULL && (*trav)->data <= arr[x]; trav = &(*trav)->link) {}
        temp = malloc (sizeof (struct node));
        if (temp != NULL) {
            temp->data = arr[x];
            temp->link = *trav;
            *trav = temp;
        }
    }
    displayBucket (localBucket, bucketSize);

    int a, b = 0;                                           //! concatenating the list for each bucket into the output array              
    for (a = 0; a < bucketSize; ++a) {
        for (temp = localBucket[a]; temp != NULL; temp = temp->link) {
            arr[b++] = temp->data;
        }
    }
}