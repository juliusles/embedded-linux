#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;

    if((pid = fork()) < 0)
    {
        printf("Fork failed");
        exit(1);
    }

    else if(pid == 0) /*   Child   */
    {
        execl("/bin/cp", "/bin/cp", argv[1], argv[2], 0);
        exit(0);
    }
    else
        wait(NULL);

    exit(0);

}
