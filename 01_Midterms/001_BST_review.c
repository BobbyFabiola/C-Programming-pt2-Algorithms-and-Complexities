#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// STRUCTURE DEFINTIONS
typedef struct {
    char FN[15];
    char LN[20];
    char MI;
} nameType;

typedef struct {
    int idNum;          //bst is sorted by this order
    nameType name;
    char course[10];
    int yearLvl;
} studentType;

typedef struct node {
    studentType data;
    struct node *link;
} *nodePtr, nodeType;

typedef enum { TRUE, FALSE } Boolean;

// FUNCTION PROTOTYPES
Boolean initializeTree (nodePtr *BST);
void createDataSet (nodePtr *BST);
Boolean insertNode (nodePtr *BST, studentType stud);


int main () {
    system ("cls");
    printf("START\n\n");

    nodePtr root;

    if ( initializeTree(&root) == TRUE ) {
        printf("Root is successfully initialized.\n");
    }

    createDataSet (&root);





    printf("\n\nEND");
    return 0;
}

// FUNCTION DEFINITIONS
Boolean initializeTree (nodePtr *BST) {
    printf("INITIALIZE\n");
    *BST = NULL;
    return (*BST == NULL) ? TRUE: FALSE;
}

void createDataSet (nodePtr *BST) {
    printf("STUDENT LIST TO BST\n");
    
    studentType students[15] = {
        {2023001, "Alice Johnson", "CS", 1},
        {2023002, "Bob Smith", "IT", 2},
        {2023003, "Charlie Brown", "CS", 3},
        {2023004, "David Lee", "ECE", 2},
        {2023005, "Emma Davis", "CS", 4},
        {2023006, "Fiona Harris", "IT", 1},
        {2023007, "George Clark", "CS", 2},
        {2023008, "Hannah Martin", "ECE", 3},
        {2023009, "Isaac White", "CS", 4},
        {2023010, "Jack Thompson", "IT", 2},
        {2023011, "Katie Lewis", "ECE", 1},
        {2023012, "Liam Walker", "CS", 3},
        {2023013, "Mia Scott", "IT", 4},
        {2023014, "Nathan Young", "ECE", 2},
        {2023015, "Olivia King", "CS", 1}
    };

    int x;
    for (x = 0; x < 15; ++x) {
        if ( insertNode (BST, students[x]) == TRUE ) {
            printf("Student %d is inserted\n", students[x].idNum);
        } else {
            printf("Failed to insert student %d\n", students[x].idNum);
        }
    }
}

Boolean insertNode (nodePtr *BST, studentType stud) {
    nodePtr *trav, temp = malloc (sizeof (nodeType));
    if (temp != NULL) {
        
    }
}