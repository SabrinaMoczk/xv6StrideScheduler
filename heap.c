#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#include "heap.h"


int insert(struct proc *p, int last, struct proc* heap[]){ //Insere um novo elemento na heap
  heap[last] = p;
  return checaHeapPai(last, heap);
}

//target is the process to be removed
struct proc *extract(int target, struct proc* heap[], int last){ //Extrai o elemento target da heap
  struct proc *ans;
  ans = heap[target];
  heap[last]->position = heap[target]->position;
  heap[target] = heap[last];
  checaHeapFilho(target, heap, last);
  return ans;
}


void checaHeapFilho(int i, struct proc* heap[], int last){ //Corrige a heap do elemento i até o nível necessário
  int smallest = i;
  struct proc* tmp;
  if(valido(leftson(i), last) && heap[leftson(i)]->pass < heap[smallest]->pass) smallest = leftson(i);
  if(valido(rightson(i), last) && heap[rightson(i)]->pass < heap[smallest]->pass) smallest = rightson(i);

  if(smallest != i){
    tmp = heap[smallest];
    heap[smallest] = heap[i];
    heap[i] = tmp;
    tmp->position = heap[smallest]->position;
    heap[smallest]->position = heap[i]->position;
    heap[i]->position = tmp->position;
    checaHeapFilho(smallest, heap, last);
  }
  return;
}

int checaHeapPai(int i, struct proc* heap[]){ //Corrige a heap do elemento i até o nivel necessario
  struct proc* tmp;

  if(i == 1) return i; //Caso for a raiz, retorna
  if(heap[dad(i)]->pass > heap[i]->pass){ //Se o pai for maior que o elemento considerado, troca e chama para o pai
    tmp = heap[dad(i)];
    heap[dad(i)] = heap[i];
    heap[i] = tmp;
    tmp->position = heap[dad(i)]->position;
    heap[dad(i)]->position = heap[i]->position;
    heap[i]->position = tmp->position;
  }
  checaHeapPai(dad(i), heap);
  return i;
}
