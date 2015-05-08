#include "pqueue.h"
#include "genlib.h"


#define ELEMENTS_START 10


struct pqueueCDT {
	int *elements[ELEMENTS_START];
	int numOfElements;
	int size;
};

pqueueADT newHeap(void){

}