
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
int getParent(int index);
void increaseArray(pqueueADT pqueue);

pqueueADT NewPQueue(void){
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
bool IsEmpty(pqueueADT pqueue){
	return(pqueue->numOfElements == 0);
}
bool IsFull(pqueueADT pqueue){
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
	int i,temp,temp2,indexParent;
	/*OM DEN ÄR FÖR STOR*/
	if (pqueue->numOfElements >= pqueue->size) {
		increaseArray(pqueue->elements);
	}
	pqueue->elements[pqueue->numOfElements+1] = newValue;
	pqueue->numOfElements += 1;
	i = pqueue->numOfElements;
	while (newValue > pqueue->elements[getParent(i)]){
		temp = getParent(i);
		temp2 = pqueue->elements[temp];
		pqueue->elements[temp] = pqueue->elements[i];
		pqueue->elements[i] = temp;
	}

}
int DequeueMax(pqueueADT pqueue){
	int temp, index, result, maxIndex;
	int leftChild, rightChild;

	if (IsEmpty(pqueue)){
		Error("Tried to dequeue mac from an empty pqueue!");
	}

	index = pqueue->numOfElements;
	result = pqueue->elements[1];
	pqueue->elements[1] = pqueue->elements[index];
	pqueue->numOfElements--;

	getChildren(&leftChild, &rightChild, index);
	if (pqueue->elements[leftChild] > pqueue->elements[rightChild]){
		maxIndex = pqueue->elements[leftChild];
	}
	else{
		maxIndex = pqueue->elements[rightChild];
	}
	while (maxIndex <= pqueue->numOfElements && index < pqueue->numOfElements){
		temp = pqueue->elements[maxIndex];
		pqueue->elements[maxIndex] = pqueue->elements[index];
		pqueue->elements[index] = temp;
		index = maxIndex;
		getChildren(&leftChild, &rightChild, index);
			if (pqueue->elements[leftChild] > pqueue->elements[rightChild]){
			maxIndex = pqueue->elements[leftChild];
			}
			else{
				maxIndex = pqueue->elements[rightChild];
			}
	}



}

int BytesUsed(pqueueADT pqueue)
{
	return (sizeof(*pqueue)+sizeof(int) * pqueue->numOfElements);
}
void increaseArray(pqueueADT pqueue){
	int x;
	int *largerArray;
	largerArray = NewArray(pqueue->size * 2, int);
	pqueue->size = pqueue->size * 2;

	for (x = 1; x < pqueue->numOfElements; x++){
		largerArray[x] = pqueue->elements[x];
	}
	FreeBlock(pqueue->elements);
	pqueue->elements = largerArray;
}