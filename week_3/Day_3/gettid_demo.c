#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>

int errno;
void*
f(void *arg)
{
    printf("%u,%p, %u\n", getpid(), &errno, syscall(SYS_gettid));
    fflush(stdin);
    return NULL;
}

int
main(int argc, char **argv)
{
    pthread_t tid;
    pthread_create(&tid, NULL, f, NULL);
    printf("%u,%p, %u\n", getpid(), &errno, syscall(SYS_gettid));
    fflush(stdin);
    pthread_join(tid, NULL);
    return 0;
}