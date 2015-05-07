#include "pqueue.h"
#include "genlib.h"
#define MAX_ELEMS_PER_BLOCK 10
/* Types */

typedef struct cellT {
	int currentNumEle;
	int block[MAX_ELEMS_PER_BLOCK];
	struct cellT *next;
} cellT;

struct pqueueCDT {
	cellT *head;
};

/* Exported entries */

pqueueADT NewPQueue(void)
{
	pqueueADT pqueue;

	pqueue = New(pqueueADT);
	pqueue->head = NULL;
	return (pqueue);
}

void FreePQueue(pqueueADT pqueue)
{
	cellT *next;

	while (pqueue->head != NULL) {
		next = pqueue->head->next;
		FreeBlock(pqueue->head);
		pqueue->head = next;
	}
	FreeBlock(pqueue);
}

bool IsEmpty(pqueueADT pqueue)
{
	return (pqueue->head == NULL);
}

bool IsFull(pqueueADT pqueue)
{
	return (FALSE);
}

/* Implementation notes: Enqueue
* -----------------------------
* För att finna rätt position för insättning måste en sökning utföras.
* Sökningar i enkellänkade listor kan vara 'knöligt'. I den här
* implementeringen används två 'paralella pekare, en följer ett steg
* bakom den andra, till dess att vi finner korrekt position för insättning
* av den nya noden. Notera specialfallet vid insättning vid listans
* huvud.
*/

void Enqueue(pqueueADT pqueue, int newValue){

	cellT *cur, *prev, *newCell;

	if (pqueue->head == NULL){
		newCell = New(cellT *);
		newCell->currentNumEle = 0;
		newCell->next = NULL;
		newCell->block[0] = newValue;
		newCell->currentNumEle++;
	}
	else{
		cur = pqueue->head;
		while (TRUE){
			if (newValue > cur->block[0]){
				if (prev != NULL) cur = prev;

			}
		}
		for (prev = NULL, cur = pqueue->head; cur != NULL; prev = cur, cur = cur->next) {
			if (newValue > cur->currentNumEle) break;
		}
		newCell->next = cur;
		if (prev){
			prev->next = newCell;
		}
		else{
			pqueue->head = newCell;
			//else
			//hålla koll på block
		}
	}
}
	/* Implementation notes: DequeueMax
	* --------------------------------
	* Det största värdet sparas först i listan så att det är
	* enkelt att ta bort. Notera att minne för noder frigörs
	* vid borttagning ur kön.
	*/

int DequeueMax(pqueueADT pqueue){
	cellT *toBeDeleted;
	int value, i;

	if (IsEmpty(pqueue)){
		Error("Tried to dequeue max from an empty pqueue!");
	}
	//element nr1
	value = pqueue->head->block[0];
	pqueue->head->currentNumEle--;
	//noll? om currentNumEle är det så ta bort block
	if (pqueue->head->currentNumEle == 0){
		//vi får inte deleta sista chunk/block
		if (pqueue->head->next != NULL){
			toBeDeleted = pqueue->head;
			value = pqueue->head->currentNumEle;
			pqueue->head = pqueue->head->next;
			FreeBlock(toBeDeleted);
		}
	}
	else
	{
		for (i = 0; i < pqueue->head->currentNumEle; i++){
			pqueue->head->block[i] = pqueue->head->block[i + 1];
		}
	}
		return (value);
	}

	/* Implementation notes: BytesUsed
	* -------------------------------
	* Minnes förbrukningen utgörs av minnet för en struct pqueueCDT +
	* storleken på summan av samtliga noder i den länkade listan.
	*/

	int BytesUsed(pqueueADT pqueue){
		int total;
		cellT *cur;

		total = sizeof(*pqueue);
		for (cur = pqueue->head; cur != NULL; cur = cur->next)
			total += sizeof(*cur);

		return (total);
	}
}