//-----------------------------------------------------------------------------
// QueueTest.c
// Another test client for Queue ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Queue.h"

int main(int argc, char* argv[]){

   int i;
   Queue Q = newQueue();
   Queue R = newQueue();

   printf("\n");

   for(i=1; i<=10; i++){
      Enqueue(Q, i);
   }
   printQueue(Q);

   for(i=1; i<=5; i++){
      Dequeue(Q);
   }
   printQueue(Q);

   for(i=11; i<=15; i++){
      Enqueue(Q, i);
   }
   printQueue(Q);

   for(i=16; i<=19; i++){
      Enqueue(Q, i);
   }
   printQueue(Q);
   printf("\n");

   for(i=13; i<=19; i++){
      Dequeue(Q);
      Enqueue(R, i);
   }
   printQueue(Q);
   printQueue(R);
   printf("Q==R is %s\n\n", equals(Q, R)?"true":"false");

   Enqueue(Q, 20);
   Enqueue(R, 200);
   printQueue(Q);
   printQueue(R);
   printf("Q==R is %s\n\n", equals(Q, R)?"true":"false");

   freeQueue(&Q);
   freeQueue(&R);
   return(EXIT_SUCCESS);
}
/* Output:

1 2 3 4 5 6 7 8 9 10
6 7 8 9 10
6 7 8 9 10 11 12 13 14 15
6 7 8 9 10 11 12 13 14 15 16 17 18 19

13 14 15 16 17 18 19
13 14 15 16 17 18 19
Q==R is true

13 14 15 16 17 18 19 20
13 14 15 16 17 18 19 200
Q==R is false

*/