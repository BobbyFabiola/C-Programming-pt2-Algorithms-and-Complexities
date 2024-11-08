#include <stdio.h>
#define MAX 10

void getOdd (int arr[], int oddArr[]);
void displayArr (int arr[]);

int main () {
    int arr[MAX] = {5, 12, 4, 7, 21, 6, 10, 9, 1, 3};
    int oddArr[MAX] = {0};

    getOdd (arr, oddArr);
    displayArr (oddArr);

    return 0;
}

void getOdd (int arr[], int oddArr[]) {
    int x, y = 0;
    for (x = 0; x < MAX; ++x) {
        if (arr[x] % 2 != 0) {
            oddArr[y++] = arr[x];
        }
    }
}

void displayArr (int arr[]) {
    int x;
    printf("\nArray: { ");
    for (x = 0; x < MAX; ++x) {
        printf("%d", arr[x]);
        if (x  < MAX-1) {
            printf(", ");
        }
    }
    printf(" }\n\n");
}