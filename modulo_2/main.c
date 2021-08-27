//SSC5723 - Sistemas Operacionais (2021) - Modulo - 2
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "list.h"

FILE * logFile;

void * consumer(void * arg) {
    while (1) {
        List* consumerList = (List *) arg;
        sem_wait(Semaphore(consumerList, FULL));
        pthread_mutex_lock(Semaphore(consumerList, MUTEX));
        int itemConsumer = pop(consumerList);
        pthread_mutex_unlock(Semaphore(consumerList, MUTEX));
        sem_post(Semaphore(consumerList, EMPTY));
        fprintf(logFile, "Item %d removido do buffer\n", itemConsumer);
    }
}

void * producer(void * arg) {
    while (1) {
        List * producerList = (List*)arg;
        int itemProducer = rand() % 100;
        sem_wait(Semaphore(producerList, EMPTY));
        pthread_mutex_lock(Semaphore(producerList, MUTEX));
        push(producerList, itemProducer);
        pthread_mutex_unlock(Semaphore(producerList, MUTEX));
        sem_post(Semaphore(producerList, FULL));
        fprintf(logFile, "Item %d inserido no buffer\n", itemProducer);
    }
}

// Code compile "gcc main.c list.c -pthread -o main"
// Code execution ./main firstParameter, secondParameter, thirdParameter
// First parameter: Value referring to the buffer size
// Second parameter: Value referring to the number of producer threads
// Third parameter: Value referring to the number of consumer threads
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Necessita dos valores: %s <tamanho_buffer> <quantidade_produtor> <quantidade_consumidor>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    int i;
    logFile = fopen("log.txt", "w");

    int bufferSize = atoi(argv[1]);
    List *listInited = initList(bufferSize);

    int numberProducers = atoi(argv[2]);
    int numberConsumers = atoi(argv[3]);

    pthread_t * producersThread = malloc(sizeof(pthread_t) * numberProducers);
    pthread_t * consumersThread = malloc(sizeof(pthread_t) * numberConsumers);

    for (i = 0; i < numberProducers; ++i)
        pthread_create(producersThread + i, NULL, producer, listInited);
    for (i = 0; i < numberConsumers; ++i)
        pthread_create(consumersThread + i, NULL, consumer, listInited);

    for (i = 0; i < numberProducers; ++i)
        pthread_join(producersThread[i], NULL);
    for (i = 0; i < numberConsumers; ++i)
        pthread_join(consumersThread[i], NULL);

    destroyList(listInited);
    fclose(logFile);

    return 0;
}
