#include "types.h"
#include "user.h"

#define MAX_TICKETS 1000
#define arg 3

int roulette();
void waste_time();

int main(){
   printf(1, "Testing!\n");
   int num;
   int i;
   for(i = 0; i < arg; i++){
      num = roulette() % MAX_TICKETS;
      if(fork(num)== 0){
         waste_time();
         exit();
      }
   }
   for(i = 0; i < arg; i++){
      wait();
   }
   exit();
}

void waste_time(){
   unsigned long i = 0;
   while(i < 100000000000){ // RUN FOREVER!!!!!!!!
      i++;
   }
}

int seed = 3;

int roulette(){
   seed = (seed * 1103515245) + 12345;
   if(seed < 0) seed = seed * (-1);
   //cprintf("%d\n", seed);
   return seed;
}
