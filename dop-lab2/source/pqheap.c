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
        pqueue->elements      = malloc(sizeof(int) * pqueue->maxElements);

        for (int i = 0; i < index; i++)
            pqueue->elements[i] = oldElements[i];

        free(oldElements);
    }

    int *basePtr = pqueue->elements;

    *(basePtr+index) = newValue;

    while (index > 1) {
        int *child  = basePtr + index;

        index >>= 1;

        int *parent = basePtr + index;

        int parentVal = *parent;
        int childVal  = *child;

        if (parentVal > childVal)
            break;

        *parent = childVal;
        *child  = parentVal;
    }
}

int DequeueMax(pqueueADT pqueue) {
    if (pqueue->numElements <= 0)
        Error("DequeueMax attempted on empty queue.");

    int *basePtr     = pqueue->elements;
    int  minValue    = *(basePtr+pqueue->numElements);
    int  maxValue    = *(basePtr+1);
    int  numElements = --pqueue->numElements;
    int  index = 1;

    *(basePtr+1) = minValue;

    while (TRUE) {
        int *parent = basePtr + index;

        index <<= 1;

        if (index > numElements)
            break;

        int *child    = basePtr + index;
        int  childVal = *child;

        if ((index < numElements) && (*(child+1) > childVal)) {
            child++;
            index++;
            childVal = *child;
        }

        int parentVal = *parent;

        if (childVal < parentVal)
            break;

        *parent = childVal;
        *child  = parentVal;
    }

    return maxValue;
}

int BytesUsed(pqueueADT pqueue) {
    return sizeof(struct pqueueCDT) + pqueue->maxElements * sizeof(int);
}
