#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sched.h>
#include <time.h>

void *taskOne ()
{
  int m, n;
  while (1)
    {
      printf ("task 1\n");
      for (m = 0; m <= 1000; m++)
	for (n = 0; n <= 10000; n++);	/* Defor-lussen dienen om een vertraging te realiseren, zodater een aantal keer een context switch naar taak 2 optreedt */
    }
}

void *taskTwo ()
{
  int m, n;
  while (1)
    {
      printf ("task 2\n");
      for (m = 0; m <= 1000; m++)
	for (n = 0; n <= 10000; n++);	/* Defor-lussen dienen om een vertraging te realiseren, zodater een aantal keer een context switch naar taak 2 optreedt */
    }
}

void *taskThree ()
{
  int i, m, n;
  for (i = 0; i < 40; i++)
    {
      printf ("task 3 \n");
      for (m = 0; m <= 1000; m++)
	for (n = 0; n <= 10000; n++);	/* De for-lussen dienen omeen vertraging te realiseren, zodat er een aantal keer een context switchnaar taak 4 optreedt */
    }
}

void *taskFour ()
{
  int i, m, n;
  for (i = 0; i < 40; i++)
    {
      printf ("task 4\n");
      for (m = 0; m <= 1000; m++)
	for (n = 0; n <= 10000; n++);	/* De for-lussen dienen omeen vertraging te realiseren, zodat er een aantal keer een context switch naar taak 4 optreedt */
    }
}

 int main (){
    //run de taken op core nr 0
    cpu_set_t mask;
    CPU_ZERO (&mask);
    CPU_SET (0, &mask);
    sched_setaffinity (0, sizeof (mask), &mask);

    pthread_attr_t tattr, tattr1;
    pthread_attr_init (&tattr);
    pthread_attr_setschedpolicy (&tattr, SCHED_RR);    //sched policy aanpassen


    struct sched_param param1;
    pthread_attr_init (&tattr1);
    pthread_attr_setschedpolicy (&tattr1, SCHED_RR);
    pthread_attr_getschedparam (&tattr1, &param1);

    param1.sched_priority = 1; // 150 is een te lage prioriteit

    pthread_attr_setinheritsched (&tattr1, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedparam (&tattr1, &param1);


    pthread_t thread1, thread2, thread3, thread4;
    pthread_create (&thread3, &tattr1, taskThree, NULL);
    pthread_create (&thread4, &tattr1, taskFour, NULL);
    pthread_create (&thread1, &tattr, taskOne, NULL);
    pthread_create (&thread2, &tattr, taskTwo, NULL);
    pthread_join (thread1, NULL);
}
