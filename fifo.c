#include "fifo.h"


void print(struct FIFO fifo){
    printf("FIFO: ");
    if(fifo.size == 0)
        printf("Empty!");
    for(int i = 0; i < fifo.size; i++){
        printf("%d ", fifo.fifo[i]);
    }
    printf("\n");
}

void array_shift(int array[], int size){
    for(int i = size; i > 0; i--){
        array[i] = array[i - 1];
    }
}

int fifo_push(struct FIFO* fifo, int value){
    if(fifo->size == fifo->max_size)
        return 0;
    else{
        array_shift(fifo->fifo, fifo->size);
        fifo->size++;
        fifo->fifo[0] = value;
    }
    return 1;
}

int fifo_pop(struct FIFO* fifo){
    if(fifo->size == 0)
        return 0;
    return fifo->fifo[--fifo->size];
}

void init_buffer(struct FIFO* fifo){
    while(fifo->size < fifo->max_size){
        int x = (rand() % 10) + 1;
        fifo_push(fifo, x);
    }
}   

void fifo_delete(struct FIFO* fifo, int value){
    for(int i =  0; i < fifo->size;){
        if(value == fifo->fifo[i]){
            // Shift elements to the left starting from the index of the found value
            for(int j = i; j < fifo->size -  1; j++){
                fifo->fifo[j] = fifo->fifo[j +  1];
            }
            // Decrease the size of the FIFO
            fifo->size--;
            // printf("After delete -> ");
            // print(*fifo);
            break; // Exit the loop since the value was found and removed
        } else {
            i++;
        }// printf("Consumed: %d\n", y);
    }
}

int fifo_find(struct FIFO* fifo, int value){
    for(int i = 0; i < fifo->size; i++){
        if(value == fifo->fifo[i]){
            //printf("Found: %d\n", value);
            return 1;
        }
    }
    return 0;
}