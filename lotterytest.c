//Lottery Scheduling test program
#include "types.h"
#include "stat.h"
#include "user.h"

#define NPROC_T 3
#define TIMEWASTER 11234567890

void timewaster(void);

int main (void){
  int i, num = 5;

  printf(1, "\n\nTest program for Xv6 Lottery Scheduling\n");
  printf(1, "\nPress Ctrl+P during execution to see a list of the processes and\n");
  printf(1, "how many times each one of then was scheduled\n\n");

  for(i = 0; i < NPROC_T; i++, num *= 2){
    if(num > 20) num = 5;
    printf(1, "Process %d is having a baby with priority %d!\n", getpid(), num);
    if(fork(num) == 0){
      timewaster();
      printf(1, "Process %d is over. Number of Tickets: %d\n", getpid(), num);
      exit();
    }
  }
  for(i = 0; i < NPROC_T; i++) wait(); //Wait for Children to exit

  exit();
}

void timewaster(void){
  int j;
  for(j = 0; j < TIMEWASTER; j++);
}
