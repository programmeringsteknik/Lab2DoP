
#include "pqueue.h"
#include "genlib.h"

#define ELEMENTS_START 10

struct pqueueCDT {
	int *elements;
	int numOfElements;
	int size;
}pqueueCDT;
/*funktionsprototyper*/
int getParent(int index);
void getChildren(int *left, int *right, int parent);

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

int getParent(int index){
	int result;
	result = index / 2;
	return(result);
}
/*värden*/
void getChildren(int *left, int *right, int parent){

	*left = parent * 2;
	*right = (parent * 2) +1;

}
void Enqueue(pqueueADT pqueue, int newValue){
	int i,temp,temp2;
	/*OM DEN ÄR FÖR STOR*/
	if (pqueue->numOfElements >= pqueue->size) {
		//utökning av kön
	}
	pqueue->elements[pqueue->numOfElements+1] = newValue;
	i = pqueue->numOfElements+1;
	while (newValue > pqueue->elements[getParent(i)]){
		temp = getParent(i);
		temp2 = pqueue->elements[temp];
		pqueue->elements[temp2] = pqueue->elements[i];
		pqueue->elements[i] = temp;
	}

}

