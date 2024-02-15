#ifndef __FIFO_H__
#define __FIFO_H__

#include <stdio.h>
#include <pthread.h>

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

struct FIFO{
    int fifo[10];
    int size;
    int max_size;
};

struct ELEVATOR{
    int level;
    int max_level;
    bool up;
};

void print(struct FIFO);
void array_shift(int[], int);
int fifo_push(struct FIFO*, int);
int fifo_pop(struct FIFO*);
void init_buffer(struct FIFO*);
int fifo_find(struct FIFO*, int);
void fifo_delete(struct FIFO*, int);

#endif