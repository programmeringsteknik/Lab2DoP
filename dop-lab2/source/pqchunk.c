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
void insertElement(cellT *cur, int element);
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
* F�r att finna r�tt position f�r ins�ttning m�ste en s�kning utf�ras.
* S�kningar i enkell�nkade listor kan vara 'kn�ligt'. I den h�r
* implementeringen anv�nds tv� 'paralella pekare, en f�ljer ett steg
* bakom den andra, till dess att vi finner korrekt position f�r ins�ttning
* av den nya noden. Notera specialfallet vid ins�ttning vid listans
* huvud.
*/

void Enqueue(pqueueADT pqueue, int newValue){
	int a, b, i, counter;
	cellT *cur, *prev, *newCell;
	counter = 0;
	if (pqueue->head == NULL){
		newCell = New(cellT *);
		newCell->currentNumEle = 0;
		newCell->next = NULL;
		newCell->block[0] = newValue;
		newCell->currentNumEle++;
		pqueue->head = newCell;
	}
	else{
		cur = pqueue->head;
		while (cur->next != NULL){
			if (newValue > cur->block[cur->currentNumEle - 1]){
				break;
			}
			cur = cur->next;
		}
		if (cur->currentNumEle >= MAX_ELEMS_PER_BLOCK){
			newCell = New(cellT *);
			newCell->currentNumEle = 0;
			newCell->next = NULL;

			a = MAX_ELEMS_PER_BLOCK / 2;
			b = MAX_ELEMS_PER_BLOCK - a;
			for (i = a; i < MAX_ELEMS_PER_BLOCK; i++){
				newCell->block[counter] = cur->block[i];
				counter++;
			}
			cur->currentNumEle = a;
			newCell->currentNumEle = b;
			if (newValue < newCell->block[0]){
				insertElement(newCell, newValue);
			}
			else{
				insertElement(cur, newValue);
		}
		newCell->next = cur->next;
		cur->next = newCell;
	}
	else{
			insertElement(cur, newValue);

		}
	}
}
	/* Implementation notes: DequeueMax
	* --------------------------------
	* Det st�rsta v�rdet sparas f�rst i listan s� att det �r
	* enkelt att ta bort. Notera att minne f�r noder frig�rs
	* vid borttagning ur k�n.
	*/

int DequeueMax(pqueueADT pqueue) {
	cellT *toBeDeleted;
	int value, i;

	if (IsEmpty(pqueue))
		Error("Tried to dequeue max from an empty pqueue!");
	
	toBeDeleted = pqueue->head;
	value = pqueue->head->block[0];
	pqueue->head->currentNumEle--;
	if (pqueue->head->currentNumEle == 0){
		pqueue->head = pqueue->head->next;
		FreeBlock(toBeDeleted);

	}
	else{
		//poppar upp
		for (i = 0; i < pqueue->head->currentNumEle; i++){
			pqueue->head->block[i] = pqueue->head->block[i + 1];
		}
	}
	return (value);
}

		/* Implementation notes: BytesUsed
		* -------------------------------
		* Minnes f�rbrukningen utg�rs av minnet f�r en struct pqueueCDT +
		* storleken p� summan av samtliga noder i den l�nkade listan.
		*/

int BytesUsed(pqueueADT pqueue){
			int total;
			cellT *cur;

			total = sizeof(*pqueue);
			for (cur = pqueue->head; cur != NULL; cur = cur->next)
				total += sizeof(*cur);

			return (total);
		}
void insertElement(cellT *cur, int element){
		int i;
		i = cur->currentNumEle - 1;
		while (cur->block[i] < element && i >= 0){
			cur->block[i + 1] = cur->block[i];
			i--;
		}
		cur->block[i + 1] = element;
		cur->currentNumEle++;
}