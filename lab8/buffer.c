#include "buffer.h"
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

SBuffer* makeBuffer(void* z,int sz,size_t mapSize){
   // Given a memory mapping at address z, meant to hold sz Task for a total size (in bytes) of mapSize
   // initialize and return a shared buffer pointer held in that mapping.
   SBuffer* nbuff = (SBuffer*) z;
   nbuff->sz = sz;
   nbuff->enter = 0;
   nbuff->leave = 0;
   nbuff->nb = 0;
   nbuff->mapSize = mapSize;
   return nbuff;
}

void bufferEnQueue(SBuffer* b,Task t){
   // add Task t to the shared buffer b. 
   if(b->nb < b->sz){
		b->data[b->enter] = t;
		b->enter++;
		b->nb++;
	}
	if(b->enter > b->sz)
		b->enter = 0;
//   if (b->sz > b->enter)
//       b->enter = 0;
//   b->data[b->enter] = t;
//   b->nb++;
//   b->enter++;
}

Task bufferDeQueue(SBuffer* b){
   // deQueue and return a task from the shared buffer b.
	Task ct = b->data[b->leave];
	b->leave++;
	b->nb--;
	if(b->leave > b->sz)
		b->leave = 0;
	return ct;
//   if (b->sz < b->leave)
//       b->leave = 0;
//   Task holder = b->data[b->leave];
//   b->leave++;
//   b->nb--;
//   return holder;
}


SBuffer* setupBuffer(char* zone,int nbTasks){
   // return the address of the shared buffer. 
   int md = shm_open(zone, O_RDWR|O_CREAT, S_IRWXU);
   size_t sizeb = sizeof(SBuffer) + nbTasks * sizeof(Task);
   sizeb = ((sizeb / 4096) + 1 ) * 4096;
   ftruncate(md, sizeb);
   void* ptr = mmap(NULL, sizeb, PROT_READ|PROT_WRITE, MAP_SHARED, md, 0);
   close(md);
   return makeBuffer(ptr, nbTasks, sizeb);
}


SBuffer* getBuffer(char* zone,int nbTasks){
   // Given a named memory mapping zone (capable of holding nbTasks), return the address of the
   // shared buffer held at the beginning of that memory map. 
   int md = shm_open(zone, O_RDWR|O_CREAT, S_IRWXU);
   size_t sizeb = sizeof(SBuffer) + nbTasks * sizeof(Task);
   sizeb = ((sizeb / 4096) + 1 ) * 4096;
   ftruncate(md, sizeb);
   void* ptr = mmap(NULL, sizeb, PROT_READ|PROT_WRITE, MAP_SHARED, md, 0);
   close(md);
   return (SBuffer*) ptr;
}

void tearDownBuffer(char* zone,SBuffer* b){
   // Release the resources (map/shared object) needed for the shared buffer b
   munmap(b, b->mapSize);
   shm_unlink(zone);
}
