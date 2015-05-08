
#include "pqueue.h"
#include "genlib.h"

#define ELEMENTS_START 10

struct pqueueCDT {
	int *elements;
	int numOfElements;
	int size;
}pqueueCDT;
/*funktionsprototyper*/
int getParent(pqueueADT pqueue, int index);

pqueueADT newHeap(void){
	pqueueADT pqueue;

	pqueue = New(pqueueADT);
	pqueue->elements = NewArray(ELEMENTS_START, int);
	pqueue->size = ELEMENTS_START;
	pqueue->numOfElements = 0;

	return(pqueue);
}
void FreePQueue(pqueueADT pqueue){
	FreeBlock(pqueue->elements);
	FreeBlock(pqueue);
}
bool isEmpty(pqueueADT pqueue){
	return(pqueue->numOfElements == 0);
}
bool isFull(pqueueADT pqueue){
	return(pqueue->numOfElements == pqueue->size);
}

int getParent(pqueueADT pqueue, int index){



}
