#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    pid_t pid, sid;

    if((pid = fork()) == 0)
    {
        sid = setsid();
        printf("Child id: %d\n", getpid());
        printf("Orphan process running. use \"kill %d\" to stop it.\n", getpid());
        while(1);
    }
    else
        printf("Parent id: %d\n", getpid());
    sleep(1);
    return 0;
}
