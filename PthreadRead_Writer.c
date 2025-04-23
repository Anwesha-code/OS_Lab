#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int readcount = 0; 
sem_t mutex;    
sem_t wrt;      

void* reader(void* arg) {
    int id = *(int*)arg;
    while (1) {
        sem_wait(&mutex);
        readcount++;
        if (readcount == 1) {
            sem_wait(&wrt); 
        }
        sem_post(&mutex);

        printf("Reader %d is reading\n", id);
        sleep(1);

        sem_wait(&mutex);
        readcount--;
        if (readcount == 0) {
            sem_post(&wrt); 
        }
        sem_post(&mutex);

        sleep(2); 
    }
}

void* writer(void* arg) {
    int id = *(int*)arg;
    while (1) {
        sem_wait(&wrt); 

        printf("Writer %d is writing\n", id);
        sleep(2);

        sem_post(&wrt); 

        sleep(3); 
    }
}

int main() {
    pthread_t r[3], w[2];
    int reader_ids[3] = {1, 2, 3};
    int writer_ids[2] = {1, 2};

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (int i = 0; i < 3; i++)
        pthread_create(&r[i], NULL, reader, &reader_ids[i]);

    for (int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &writer_ids[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
