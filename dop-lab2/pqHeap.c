/*
* File: pqHeap.c
* ------------------
*
* Markus Carlsson & Philip Arvidsson
* Senast modifierad: 08/5 - 2015
*/

#include "pqueue.h"
#include "genlib.h"
#define ELEMENTS_START 10
struct pqueueCDT {
	int *elements[ELEMENTS_START];
	int numOfElements;
};