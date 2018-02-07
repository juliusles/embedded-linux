#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    pid_t pid, sid;
    int status;

    if((pid = fork()) < 0)
    {
        printf("Fork failed");
        exit(1);
    }

    else if(pid == 0) /*   Child   */
    {

        printf("Child process PID: %d, PPID: %d\n", getpid(), getppid());

        execlp("geany", "geany", 0);
        exit(0);
    }

    else             /*   Parent   */
    {
        printf("Parent process PID: %d, PPID: %d\n", getpid(), getppid());
        printf("Waiting for child...\n");
        
        if(waitpid(pid, &status, 0) < 0)
        {
            perror("Waitpid failed\n");
            exit(EXIT_FAILURE);
        }

        if(WIFEXITED(status))
        {
            int e = WEXITSTATUS(status);
            printf("Child process %d terminated with exit code %d\n", pid, e);
        }

        
    }

    return 0;
}
