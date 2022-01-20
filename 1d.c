#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
void* threadEen(){
    int i;
    while(1){
        usleep(0.5 *1e6);
        printf("0.5 sec --- %i\n",i);
        i++;
    }
}

void* threadTwee(){
    int i;
    while(1){
        usleep(1.3 *1e6);
        printf("1.3 sec -- %i \n",i);
        i++;
    }
}

int main() {
    pthread_t tid;
    pthread_attr_t tattr;
    pthread_attr_init(&tattr);
    pthread_create(&tid, &tattr, threadEen, 0);
    pthread_create(&tid, &tattr, threadTwee, 0);
    pthread_join(tid,NULL);
    return 0;
}
