#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/* create mapped process address space */
void* create_shared_memory(size_t size) {
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED;
    return mmap(NULL, size, protection, visibility, 0, 0);
}

struct arg_struct {
    void* arg1;
};

/* Prepare for message writing*/
void* thread1(void* argu){
    struct arg_struct *args = argu;
    void* memory= args->arg1;
    for (int i = 0; i < 50; ++i) {
        char message[10];
        sprintf(message,"%d",i);
        char* m = message;
        memcpy(memory, m, sizeof(m));
        printf("thread 1: %s ", memory);
        sleep(1);
    }
}

/* Prepare for message reading*/
void* thread2(void * argu){
    struct arg_struct *args = argu;
    void* memory = args->arg1;
    while(1){
        printf("| thread 2: %s\n", memory);
        sleep(1);
    }
}

int main() {

    void* memory = create_shared_memory(32);

    pthread_t thread_1, thread_2;

    struct arg_struct args;
    args.arg1 = &memory;

    pthread_create(&thread_2, NULL, &thread1, (void *)&args);
    pthread_create(&thread_1, NULL, &thread2, (void *)&args);

    pthread_join(thread_2, NULL);
    pthread_join(thread_1, NULL);
}
