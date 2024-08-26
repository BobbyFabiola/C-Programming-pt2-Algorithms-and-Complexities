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

typedef nodePtr bucketType[MAX];
typedef float elemType;

void displayArr (elemType arr[]);
void initializeBucket (bucketType B);
void displayBucket (bucketType B);
void bucketSort (elemType inputArr[], elemType outputArr[], bucketType B);

int main () {
    system("CLS");
    printf("START\n");

    int x;
    elemType inputArr[MAX] = {0.42, 0.65, 0.32, 0.12, 0.12, 0.67, 0.24, 0.93, 0.66, 0.48};
    elemType outputArr[MAX];

    printf("\n[ INPUT ARRAY ]\n");
    displayArr (inputArr);
    
    bucketType localBucket;             //declare bucket array or an array of node pointers
    initializeBucket (localBucket);
    displayBucket (localBucket);    

    bucketSort (inputArr, outputArr, localBucket);
    displayBucket (localBucket);

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

void initializeBucket (bucketType B) {
    int a;
    for (a = 0; a < MAX; ++a) {
        B[a] = NULL;
    }
}

void displayBucket (bucketType B) {
    printf("\n\n[ LOCAL BUCKET ]");
    int a;
    for (a = 0; a < MAX; ++a) {
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

void bucketSort (elemType inputArr[], elemType outputArr[], bucketType B) {
    int x;
    elemType maxVal = inputArr[0];      //find the maximum element from the input array
    for (x = 0; x < MAX; ++x) {
        if (inputArr[x] > maxVal) {
            maxVal = inputArr[x];
        }
    }
    
    nodePtr *trav, temp;
    for (x = 0; x < MAX; ++x) {         //placing each element into the buckets
        int idx = (int) (inputArr[x] * MAX);
        for (trav = &(B[idx]); *trav != NULL && (*trav)->data <= inputArr[x]; trav = &(*trav)->link) {}
        temp = malloc (sizeof (struct node));
        if (temp != NULL) {
            temp->data = inputArr[x];
            temp->link = *trav;
            *trav = temp;
        }
    }

    int a, b = 0;                       //concatenating the list for each bucket into the output array
    for (a = 0; a < MAX; ++a) {
        for (temp = B[a]; temp != NULL; temp = temp->link) {
            outputArr[b++] = temp->data;
        }
    }
}