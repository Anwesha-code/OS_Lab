#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct data {
    int* arr;          
    int thread_num;    
} data;

int arrSize = 100; 

void* halfSum(void* p) {
    data* ptr = (data*)p;
    int n = ptr->thread_num;
    int i;

    int* thread_sum = (int*) calloc(1, sizeof(int));

    if (n == 0) {
        for (i = 0; i < arrSize / 2; i++)
            thread_sum[0] += ptr->arr[i];
    } else {
        for (i = arrSize / 2; i < arrSize; i++)
            thread_sum[0] += ptr->arr[i];
    }

    pthread_exit(thread_sum); // Return the partial sum
}

int main(void) {
    int* int_arr = (int*) calloc(arrSize, sizeof(int));
    int i;

    for (i = 0; i < arrSize; i++)
        int_arr[i] = i + 1;

    data thread_data[2];
    thread_data[0].thread_num = 0;
    thread_data[0].arr = int_arr;
    thread_data[1].thread_num = 1;
    thread_data[1].arr = int_arr;

    pthread_t tid[2];

    pthread_create(&tid[0], NULL, halfSum, &thread_data[0]);
    pthread_create(&tid[1], NULL, halfSum, &thread_data[1]);

    int* sum0;
    int* sum1;

    pthread_join(tid[0], (void**)&sum0);
    pthread_join(tid[1], (void**)&sum1);

    printf("Sum of whole array = %d\n", *sum0 + *sum1);

    free(sum0);
    free(sum1);
    free(int_arr);

    return 0;
}
