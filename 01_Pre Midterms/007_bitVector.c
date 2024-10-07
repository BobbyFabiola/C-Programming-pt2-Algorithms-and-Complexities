#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE, TRUE } Boolean;

Boolean *makeBitVector (int setArr[], int size);        //making of the bit vector
void displayBV (Boolean SET[], int size);               //display bit vector
Boolean isMember (Boolean S[], int size, int elem);     //check membership

int main () {
    int setC[5] = {1, 7, 8, 9, 10};

    int x, maxElem = setC[0];                           //find the size of the bit vector
    for (x = 1; x < 5; ++x) {
        if (setC[x] > maxElem) {
            maxElem = setC[x];
        }
    }

    printf("\nMAX ELEMENT:: %d\n", maxElem);

    Boolean *setBV = makeBitVector (setC, maxElem);
    displayBV (setBV, maxElem);

    int pos = 4;
    if (isMember (setBV, maxElem, pos) == TRUE) {
        printf("Pos [%d] is a MEMBER\n\n", pos);
    } else {
        printf("Pos [%d] is a NOT a member\n\n", pos);
    }

    return 0;
}

Boolean *makeBitVector (int setArr[], int size) {
    Boolean *arr = calloc (size + 1, sizeof(Boolean));
    if (arr != NULL) {
        int x;
        for (x = 0; x < 5; ++x) {
            arr[setArr[x]] = TRUE;
        }
    }
    return arr;
}

void displayBV (Boolean SET[], int size) {
    int x;
    printf("\nBit-Vector = { ");
    for (x = 0; x < size + 1; ++x) {
        printf("%d", SET[x]);
        if (x <= size-1) {
            printf(", ");
        }
    }
    printf(" }\n\n");
}

Boolean isMember (Boolean S[], int size, int elem) {
    return (S[elem] == TRUE) ? TRUE: FALSE;
}