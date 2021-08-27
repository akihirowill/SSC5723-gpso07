//SSC5723 - Sistemas Operacionais (2021) - Modulo - 2
#ifndef _LIST_H_
#define _LIST_H_

#define MUTEX 0
#define FULL 1
#define EMPTY 2

typedef struct structList List;

List* initList(int capacity);

int pop(List * l);
void push(List * l, int item);
void destroyList(List* l);
void* Semaphore(List* l, int type);

#endif