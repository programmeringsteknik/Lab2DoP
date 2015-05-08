/*
* File: pqHeap.c
* ------------------
*
* Markus Carlsson & Philip Arvidsson
* Senast modifierad: 08/5 - 2015
*/

#include "genlib.h"
#include "pqueue.h"

#define ELEMENTS_START 10


struct pqueueCDT {
	int *elements[ELEMENTS_START];
	int numOfElements;
	int size;
};

pqueueADT newHeap(void){


}