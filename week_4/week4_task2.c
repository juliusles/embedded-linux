/*
    Julius Lesonen TTV16SA
    20.2.2018
*/

/*
 *  Write a program that shows that the getrusage() RUSAGE_CHILDREN
 *  flag retrieves information about  only the children for which a 
 *  wait() call has been performed
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <math.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    struct rusage ru;
    struct timeval utime;

    if ((pid = fork()) == -1)
        perror("fork");
    
    else if (pid)   /*    Parent    */
    {
        getrusage(RUSAGE_CHILDREN, &ru);
        
        utime = ru.ru_utime;
        
        printf("Before calling wait:\n");
        printf("RUSAGE :ru_utime => %lld [sec] : %lld [usec]\n",
              (long long)utime.tv_sec, (long long)utime.tv_usec);
        wait(NULL);

        getrusage(RUSAGE_CHILDREN, &ru);

        utime = ru.ru_utime;

        printf("After calling wait:\n");
        printf("RUSAGE :ru_utime => %lld [sec] : %lld [usec]\n",
              (long long)utime.tv_sec, (long long)utime.tv_usec);
    } 
    else         /*      Child    */ 
    {
        double myresult = 0.0;
        int i;
        for (i=0; i<50000000; i++)
            myresult += sin(i) * tan(i);
        exit(0);
    }
    return 0;
}