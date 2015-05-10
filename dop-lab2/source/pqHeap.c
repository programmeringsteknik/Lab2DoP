//------------------------------------------------
// INCLUDES
//------------------------------------------------

#include "pqueue.h"

#include "genlib.h"

//------------------------------------------------
// CONSTANTS
//------------------------------------------------

#define InitialMaxElements 16

//------------------------------------------------
// TYPES
//------------------------------------------------

struct pqueueCDT {
    int* elements;
    int  numElements;
    int  maxElements;
};

//------------------------------------------------
// FUNCTIONS
//------------------------------------------------

pqueueADT NewPQueue() {
    pqueueADT pqueue = malloc(sizeof(struct pqueueCDT));

    pqueue->elements    = malloc(sizeof(int) * InitialMaxElements);
    pqueue->numElements = 0;
    pqueue->maxElements = InitialMaxElements;

    return pqueue;
}

void FreePQueue(pqueueADT pqueue) {
    free(pqueue->elements);
    free(pqueue);
}

bool IsEmpty(pqueueADT pqueue) {
    return (pqueue->numElements==0);
}

bool IsFull(pqueueADT pqueue) {
    return FALSE;
}

void Enqueue(pqueueADT pqueue, int newValue) {
    int index = ++pqueue->numElements;

    if (index >= pqueue->maxElements) {
        int *oldElements = pqueue->elements;
        pqueue->maxElements <<= 1;
        pqueue->elements = malloc(sizeof(int) * pqueue->maxElements);
        for (int i = 0; i < index; i++)
            pqueue->elements[i] = oldElements[i];
        free(oldElements);
    }

    pqueue->elements[index] = newValue;

    while (index > 1) {
        int* parent = &pqueue->elements[index >> 1];
        int* child  = &pqueue->elements[index];

        if (*parent > *child)
            break;

        int tmp     = *child;
            *child  = *parent;
            *parent = tmp;

        index >>= 1;
    }
}

int DequeueMax(pqueueADT pqueue) {
    if (pqueue->numElements <= 0)
        Error("DequeueMax attempted on empty queue.");

    int min = pqueue->elements[pqueue->numElements];
    int max = pqueue->elements[1];

    pqueue->elements[pqueue->numElements] = 0xdead;

    pqueue->elements[1] = min;

    pqueue->numElements--;

    int index = 1;
    while (TRUE) {
        int *parent    = &pqueue->elements[index];
        int leftIndex  = index << 1;
        int rightIndex = leftIndex + 1;

        // Om vänsterbarnet ligger utanför kön så finns det garanterat inte.
        if (leftIndex > pqueue->numElements)
            break;

        int *leftChild  = &pqueue->elements[leftIndex];
        int *rightChild = NULL;

        // Vi använder bara högerbarnet om det finns...
        if (rightIndex <= pqueue->numElements)
            rightChild = &pqueue->elements[rightIndex];

        // Vi börjar med att peka på vänster barn...
        int *child = leftChild;

        index = leftIndex;

        // ..men om höger barn är större än väster barn, så pekar vi på det
        // istället...
        if (rightChild && *rightChild > *leftChild) {
            index = rightIndex;
            child = rightChild;
        }

        // Om barnet är mindre än föräldern så är allt i ordning, så vi
        // behöver inte göra något mer.
        if (*child < *parent)
            break;

        // Här byter vi plats på barn och förälder och upprepar alltihop.
        int tmp     = *parent;
            *parent = *child;
            *child  = tmp;
    }

    return max;
}

int BytesUsed(pqueueADT pqueue) {
    return sizeof(struct pqueueCDT) + pqueue->maxElements * sizeof(int);
}
