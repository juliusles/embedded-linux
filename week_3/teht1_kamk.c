#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

char str[5];

void *threadFunction(void *arg);

int main(int argc, char *argv[])
{
    int err;
    pthread_t threads[5];
    char letter;
    int i;

    for(i = 0; i < 5; i++)
    {
        switch(i)
        {
            case 0: letter = 'k'; break;
            case 1: letter = 'a'; break;
            case 2: letter = 'm'; break;
            case 3: letter = 'k'; break;
            case 4: letter = '\0';break;
            default: break;
        }
        // Create thread
        err = pthread_create(&threads[i], NULL, threadFunction, (void*)letter);
        if (err)
        {
            printf("Thread creation failed\n");
            exit(EXIT_FAILURE);
        }
        // Wait for threads to finish
        err = pthread_join(threads[i], NULL);
        if (err)
        {
            printf("Thread join failed\n");
        }
    }
    // Print global array contents
    printf("%s\n", str);

    exit(EXIT_SUCCESS);
}

// Write chars to global array here
void *threadFunction(void *arg)
{
    static int i = 0;
    str[i] = (char)arg;
    i++;
    pthread_exit(NULL);
}
