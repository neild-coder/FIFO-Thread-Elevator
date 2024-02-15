#include "fifo.h"

#define THREAD 2

sem_t empty;
sem_t full;

pthread_mutex_t mutexBuffer;
struct FIFO fifo = {
    .fifo = {},
    .size = 0,
    .max_size = 10,
};

struct ELEVATOR lift = {
    .level = 0,
    .max_level = 10,
    .up = true,
};

void lift_operation(){
    if(lift.up && lift.level < lift.max_level)
        lift.level++;
    else
        lift.level--;
    if(lift.level == lift.max_level)
        lift.up = false;
    else if(lift.level == 1)
        lift.up = true;
    else
        return;
}

void *producer(void* args){
    while(1){
        int x = (rand() % 10) + 1;
        sleep(1);

        sem_wait(&empty);
        pthread_mutex_lock(&mutexBuffer);
        printf("\n\n-- Producer --------\n");        
        printf("Produced: %d\n", x);
        while(fifo.size < fifo.max_size){
            if(fifo_push(&fifo, x)){
                print(fifo);
            }
            else{
                printf("Buffer Full!\n");
            }
        }

        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&full);
    }
}

void *consumer(void* args){
    while(1){
        int y;

        sem_wait(&full);
        pthread_mutex_lock(&mutexBuffer);
        printf("-- Consumer --------\n");
        printf("Lift Level: %d\n", lift.level);
        while(fifo_find(&fifo, lift.level)){
           fifo_delete(&fifo, lift.level); 
        }
        
        lift_operation();

        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&empty);

        print(fifo);
        
        sleep(1);
    }
}



int main(){
    srand(time(NULL));
    pthread_t th[THREAD];
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&empty, 0, 10);
    sem_init(&full, 0, 0);
    int i = 0;
    init_buffer(&fifo);
    for(i = 0; i < THREAD; i++){
        if(i > 0){
            if(pthread_create(&th[i], NULL, &producer, NULL) != 0)
                printf("Failed to create thread!\n");
        }
        else{
            if(pthread_create(&th[i], NULL, &consumer, NULL) != 0)
                printf("Failed to create thread!\n");
        }
    }
    for(i = 0; i < THREAD; i++){
        if(pthread_join(th[i], NULL) != 0)
            printf("Failed to join\n");
    }
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutexBuffer);
    return 0;
}