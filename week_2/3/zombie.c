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
        printf("Child id: %d\n", getpid());
        exit(0);
    }
    else             /*   Parent   */
    {
        printf("Parent id: %d\n", getpid());
        printf("Wait 20 seconds...\n");
        sleep(20);
        wait(NULL);
    }
    printf("\nProgram terminated.\n");
    return 20;

}
