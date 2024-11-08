#include <stdio.h>
#include <stdlib.h>


#define N 19

typedef enum { FALSE, TRUE } Boolean;
typedef int BV_SET[N];

Boolean *makeBitVector (int setArr[], int size);        //making of the bit vector
void displayBV (Boolean SET[], int size);               //display bit vector
Boolean isMember (Boolean S[], int size, int elem);     //check membership
int findSmallElem (BV_SET setArr);

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

    //! 
    int arrSet[10] = {14, 17, 5, 10, 15, 12, 6, 13, 16, 18};

    BV_SET mySet = {0};                                         //making the bit vector
    for (x = 0; x < 10; ++x) {
        if (arrSet[x] < N) {
            mySet[arrSet[x]] = 1;
        }
    }

    printf("\nMY SET = { ");                                    //displaya the bit vector
    for (x = 0; x < N; ++x) {
        printf("%d", mySet[x]);
        if (x < N-1) {
            printf(", ");
        }
    }
    printf(" }\n\n");

    printf("Return value for smallest elem in the BV:: %d\n\n", findSmallElem (mySet)); 

    return 0;
}

Boolean *makeBitVector (int setArr[], int size) {       //returning a boolean array
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

int findSmallElem (BV_SET setArr) {
    int x, retVal = -1;
    for (x = 0; x < N && retVal == -1; ++x) {
        if (setArr[x] == 1) {
            retVal = x;
        }
    }
    return retVal;
}