#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function(void *ptr);

int main(int argc, char *argv[])
{
    pthread_t   thread1;
    pthread_t   thread2;
    const char* message1 = "Thread 1";
    const char* message2 = "Thread 2";
    int         iret1;
    int         iret2;
    int         err;

    /*TODO:Create independent threads each of which will execute function named print_message_function*/
    err = pthread_create(&thread1, NULL, print_message_function, (void*)message1);
    if (err != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread 1 created\n");

    err = pthread_create(&thread2, NULL, print_message_function, (void*)message2);
    if (err != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread 2 created\n");

    err = pthread_join(thread1, NULL);
    if(err != 0)
    {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread 1 joined\n");

    err = pthread_join(thread2, NULL);
    if(err != 0)
    {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread 2 joined\n");



    //TODO:
    /* Wait that threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */


    printf("Thread 1 returns: %d\n",iret1);
    printf("Thread 2 returns: %d\n",iret2);
    exit(0);
}

void *print_message_function( void *ptr )
{
    char *message;
    message = (char*) ptr;
    printf("%s\n", message);
}
