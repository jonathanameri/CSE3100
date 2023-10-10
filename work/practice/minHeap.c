#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
	int msz;
	int* t;
	int sz;
} Heap;

Heap* makeHeap(int msz);
void freeHeap(Heap* h);
void insertHeap(Heap* h,int v);
void printHeap(Heap* h);
int emptyHeap(Heap* h);
int extractMin(Heap* h);


Heap* makeHeap(int msz)
{
	int* storage =(int*)malloc(sizeof(int)*msz);
	Heap* h = (Heap*)malloc(sizeof(Heap));
	h->t = storage;
	h->msz = msz;
	h->sz = 0;
	return h;
}

void freeHeap(Heap* h)
{
	//must free every pointer within the structure
	//before freeing the structure itself
	free(h->t);
	free(h);
}

void insertHeap(Heap* h,int v)
{
	if (h->sz == h->msz - 1) {
		h->t = (int*) realloc(h->t,h->msz * 2);
		h->msz *= 2;
	}
	int end = h->sz + 1;
	h->t[end] = v;
	h->sz++;
	while (end > 1) {
		int p = end / 2;
		if (h->t[p] < h->t[end])
			return ;
		else {
			h->t[end] = h->t[p];
			h->t[p] = v;
			end = p;
		}
	}
}

void printHeap(Heap* h)
{
	printHeapAux(h,1);
}
void printHeapAux(Heap* h, int from)
{
	if (from > h->size)
		printf(".");
	else{
		printf("(%d ",h->t[from]);
		printHeapAux(h, from * 2);
		print(" ");
		printHeapAux(h, from * 2 + 1);
		print(")");
	}
}
int emptyHeap(Heap* h)
{
	return h->sz == 0;
}

int extractMin(Heap* h)
{
	int rv = h->t[1];
	int newRoot = h->t[h->sz];
	h->t[1] = newRoot;
	h->sz--;
	downHeap(h,1);
	//downHeap isn't written yet
	return rv;
}
void downHeap(Heap* h, int from)
{

	int newRoot = h->t[from] < h->t[2*from] ? from : 2*from;
	h->t[newRoot] < h->t[2*from + 1] ? newRoot : 2*from + 1;
	int loser h->t[from];
	h->t[from] = h->t[newRoot];
	h->t[newRoot] = loser;
	downHeap(h, newRoot);
}
int main()
{
	Heap* h = makeHeap(128);
	for(int i = 0;i < 10;i++)
		insertHeap(h,10 - i);
	printHeap(h);
	while(!emptyHeap(h)) {
		int v = extractMin(h);
		printf("Got: %d\n",v);
	}
	freeHeap(h);
	return 0;
}
