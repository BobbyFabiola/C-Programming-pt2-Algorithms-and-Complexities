/******************************************************************
*   Name:           Fabiola Villanueva                            *
*   Description:    Counting Sort Algorithm                       *
*   Date:           Aug 25, 2024                                  *
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef int arrType[MAX];

void displayArr (arrType arr);
void countingSort (arrType inArr, arrType outArr);

int main () {
    system("CLS");
    printf("START\n\n");

    arrType outputArr, inputArr = {5, 5, 3, 7, 7, 7, 6, 2, 1, 4};

    printf("\n[INPUT ARRAY - unsorted]");
    displayArr (inputArr);

    countingSort (inputArr, outputArr);
    printf("\n[OUTPUT ARRAY - sorted]");
    displayArr (outputArr);

    printf("\n\nEND\n");
    return 0;
}

void displayArr (arrType arr) {
    int x;
    printf("\n{");
    for (x = 0; x < MAX; ++x) {
        printf("%d", arr[x]);
        if (x < MAX - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}

void countingSort (arrType inArr, arrType outArr) {
    int x, maxVal = inArr[0];                           //find the max element from the input array
    for (x = 0; x < MAX; ++x) {
        if (inArr[x] > maxVal) {
            maxVal = inArr[x];
        }
    }

    int countArr[maxVal +1];                            //declare and initialize a count array
    for (x = 0; x < maxVal + 1; ++x) {
        countArr[x] = 0;
    }
    for (x = 0; x < MAX; ++x) {                         //iterate through input array and count occurences
        ++countArr[inArr[x]];
    }
    
    printf("\n[COUNT ARRAY - (elem: count)]");          //printing of the count array
    printf("\n[");
    for (x = 0; x < maxVal + 1; ++x) {
        printf("(%d: %d)", x, countArr[x]);
        if (x < maxVal) {
            printf(", ");
        }
    }
    printf("]\n");

    for (x = 1; x < maxVal + 1; ++x) {                  //accumulate the counts
        countArr[x] += countArr[x - 1];
    }
    
    for (x = MAX-1; x >= 0; --x) {                      //populate and sort the output array
        outArr[--(countArr[inArr[x]])] = inArr[x];
    }
}