#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

void createLoggerDaemon()
{
    pid_t pid;

    if ((pid = fork()) < 0)  /* Failure */
        exit(EXIT_FAILURE);
    
    if (pid > 0)             /* Parent  */
        exit(EXIT_SUCCESS);
    
    
    if (setsid() < 0)        /* Child   */
        exit(EXIT_FAILURE);

    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    

    if ((pid = fork()) < 0)  /* Second fork */
        exit(EXIT_FAILURE);

    if (pid > 0)  /*  Second parent  */
        exit(EXIT_SUCCESS);

    umask(0);

    chdir("/temp/");

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    

    //int i;
    //for (i = sysconf(_SC_OPEN_MAX); i >= 0; i--)
    //{
    //    close(i);
    //}
    FILE *fp = NULL;

    fp = fopen("Log.txt", "w+");
    

    char *text = "Logging info...\n";

    int n = 0;
    while(n < 30);
    {
        sleep(1);
        //fwrite(text, sizeof(char), sizeof(text), fp);
        fprintf(fp, "%s", text);
        fflush(fp);
        n++;
    }
    fclose(fp);
}

int main(int argc, char *argv[])
{
    createLoggerDaemon();

    return 0;
}
