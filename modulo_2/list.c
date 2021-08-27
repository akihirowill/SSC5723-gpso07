//SSC5723 - Sistemas Operacionais (2021) - Modulo - 2
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include "list.h"

struct structList {
	int * buffer;
	int seek, end, capacity;
	pthread_mutex_t threadMutex;
	sem_t complete, empty;
};

void* Semaphore(List* l, int type) {
	switch(type) {
		case MUTEX:
			return &l->threadMutex;
		case FULL:
			return &l->complete;
		case EMPTY:
			return &l->empty;
	}
	return NULL;
}

List* initList(int capacity) {
	List* l = (List*) malloc(sizeof(List));
	l->buffer = (int*) malloc(sizeof(int) * capacity);
	l->seek = l->end = 0;
	l->capacity = capacity;
	pthread_mutex_init(&l->threadMutex, NULL);
	sem_init(&l->complete, 0, 1);
	sem_init(&l->empty, 0, capacity);
	sem_wait(&l->complete);
	return l;
}

int pop(List * l) {
	int item = l->buffer[l->seek];
	l->seek = (l->seek + 1) % l->capacity;
	return item;
}

void push(List * l, int item) {
	l->buffer[l->end] = item;
	l->end = (l->end + 1) % l->capacity;
}

void destroyList(List* l) {
	pthread_mutex_destroy(&l->threadMutex);
	sem_destroy(&l->complete);
	sem_destroy(&l->empty);
	free(l->buffer);
	free(l);
}