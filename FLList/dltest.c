#include "dllist.h"
#include <stdio.h>
#include <string.h>

int main(int argc,char* argv[])
{
   int nbT = atoi(argv[1]);
   DLList* lst = malloc(sizeof(DLList));
   initList(lst);

   for(int i=0;i < 100;i++) {
      insertSortedList(lst,i);
   }

   printListForward(lst);
      
   destroyList(lst);
   free(lst);
   return 0;
}

