#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
int fd[2];

void *reading()
{
    while(1){
        int i, result;
        result = read (fd[0],&i,1);
        if (result != 1) {
            perror("read");
            exit(3);
        }
        printf ("| Thread 2 read: %d\n", i);
        sleep(1);
    }

}

void *writing()
{
    int result;
    for (int i = 0; i < 50; ++i) {
        result = write (fd[1], &i,1);
        if (result != 1){
            perror ("write");
            exit (2);
        }
        printf ("Thread 1 send: %d ", i);
        sleep(1);
    }
}

int main()
{
    pthread_t thread_1,thread_2;
    int result;

    result = pipe (fd);
    if (result < 0){
        perror("pipe ");
        exit(1);
    }
    pthread_create(&thread_1,NULL,&reading,NULL);
    pthread_create(&thread_2,NULL,&writing,NULL);
    pthread_join(thread_1,NULL);
    pthread_join(thread_2,NULL);
}
