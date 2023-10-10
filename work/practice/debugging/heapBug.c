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
  free(h->t);
}

void insertHeap(Heap* h,int v)
{
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

void printHeapAux(Heap* h,int from);
void printHeap(Heap* h)
{
  printHeapAux(h,1);
  printf("\n");//for readability
}

void printHeapAux(Heap* h,int from)
{
  if (from >= h->sz)
    printf(".");
  else {
    printf("( %d ",h->t[from]);
    printHeapAux(h,from * 2);
    printf(" ");
    printHeapAux(h,from * 2 + 1);    
    printf(")");
  }
}

int emptyHeap(Heap* h)
{
  return h->sz == 0;
}

void bubbleDown(Heap* h,int f)
{
  if (f <= h->sz) {  // if position 'f' is within the heap
    // if left child is in heap and smaller than root, newRoot is left child
    // if right child is in heap and smaller than newRoot, newRoot is now right child
    int newRoot = (2*f   < h->sz   && h->t[2*f] < h->t[f])       ? 2*f     : f;
    newRoot     = (2*f+1 < h->sz && h->t[2*f+1] < h->t[newRoot]) ? 2*f + 1 : newRoot;
    if (newRoot != f) {
      // if the newRoot is changing... Then swap and recur!
      int looser = h->t[f];    // sinking value
      h->t[f] = h->t[newRoot]; // promoted value moves up
      h->t[newRoot] = looser;  // sinking value goes to newRoot
      bubbleDown(h,newRoot);   // recur
    }
  }
}

int extractMin(Heap* h) 
{
  int rv = h->t[1];
  int newRoot = h->t[h->sz];
  h->t[1] = newRoot;
  h->sz -= 1;
  bubbleDown(h,1);
  return rv;
}

int main()
{
   Heap* h = makeHeap(10);
   int ttl = 0;
   for(int i = 0;i <= 20;i++) {
     int val = random();
     val = val % 20;
     ttl += val;
     insertHeap(h,val);
   }
   printHeap(h);
   int ttl2 = 0;
   while(!emptyHeap(h)) {
      int v = extractMin(h);
      ttl2 += v;
      printf("Got: %d\n",v);
   }
   freeHeap(h);
   printf("%d is %d\n",ttl,ttl2);
   return 0;
}
