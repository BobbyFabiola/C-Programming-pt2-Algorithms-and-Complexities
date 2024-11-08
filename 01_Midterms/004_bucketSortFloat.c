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
void bucketSort (elemType arr[]);

int main () {
    system("CLS");
    printf("START\n");

    int x;
    // elemType arr[MAX] = {0.42, 0.65, 0.32, 0.12, 0.12, 0.67, 0.24, 0.93, 0.66, 0.48};
    elemType arr[MAX] = {0.942, 0.965, 0.932, 0.912, 0.912, 0.967, 0.924, 0.993, 0.966, 0.948};

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
        printf("%.2f", arr[x]);
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
                printf(" %.2f ", trav->data);
            }
        } else {
            printf(" ~ ");
        }
    }
}

void bucketSort (elemType arr[]) {
    int x;
    elemType maxVal = arr[0], minVal = arr[0];                  //! find the maximum and minimum element from the input array
    for (x = 1; x < MAX; ++x) {
        if (arr[x] > maxVal) maxVal = arr[x];
        if (arr[x] < minVal) minVal = arr[x];
    }

    printf("\n\nMIN = %.2f :: MAX = %.2f", minVal, maxVal);

    int bucketSize = (maxVal - minVal) * 10;                    //! declare bucket array or an array of node pointers
    nodePtr localBucket[bucketSize];                            //* float point number for bucket size
    for (x = 0; x < bucketSize; ++x) {
        localBucket[x] = NULL;
    }
    displayBucket (localBucket, bucketSize);
    
    nodePtr *trav, temp;                                        //! placing each element into the buckets
    for (x = 0; x < MAX; ++x) {                                 //* getting index of float point number values
        int idx = (int) ((arr[x] - minVal) * (bucketSize - 1) / (maxVal - minVal));
        for (trav = &localBucket[idx]; *trav != NULL && (*trav)->data <= arr[x]; trav = &(*trav)->link) {}
        temp = malloc (sizeof (struct node));
        if (temp != NULL) {
            temp->data = arr[x];
            temp->link = *trav;
            *trav = temp;
        }
    }
    displayBucket (localBucket, bucketSize);

    int a, b = 0;                                               //! concatenating the list for each bucket into the output array              
    for (a = 0; a < bucketSize; ++a) {
        for (temp = localBucket[a]; temp != NULL; temp = temp->link) {
            arr[b++] = temp->data;
        }
    }
}

