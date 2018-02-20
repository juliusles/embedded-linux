/*
    Julius Lesonen TTV16SA
    20.2.2018
*/

/*
 *  Write a program that uses two pipes to enable bidirectional 
 *  communication between a parent and child process.
 *  
 *  The parent process should loop reading a block of text from
 *  standard input and use one of the pipes to send the text to
 *  the child, which converts it to uppercase and sends it back
 *  to the parent via the other pipe. The parent reads the data
 *  coming back from the child and echoes it on standard output
 *  before continuing around the loop once more.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 1024

#define READ     0
#define WRITE    1

void toUpperCase(char *str);

int main(int argc, char *argv[])
{
    int parentPipe[2];
    int childPipe[2];
    pid_t pid;

     // Create two pipes
    if (pipe(parentPipe) || pipe(childPipe)) {
        perror("opening stream socket pair");
        exit(1);
    }

    if ((pid = fork()) == -1)
        perror("fork");
    
    else if (pid)   /*    Parent    */
    {
        close(parentPipe[READ]);
        close(childPipe[WRITE]);
        
        char buf[BUF_SIZE];

        printf("Enter text to convert to uppercase.\nType \'Q\' to exit\n");
        
        while (1)
        {
            printf("> ");
            // Get message from stdin
            //scanf("%s", buf);
            fgets(buf, BUF_SIZE, stdin);
            if (write(parentPipe[WRITE], buf, BUF_SIZE) < 0) // Write to child
                perror("writing message");
            if ((buf[0] == 'q' || buf[0] == 'Q') && buf[1] == '\n'){
                close(parentPipe[WRITE]);
                close(childPipe[READ]);
                wait(NULL); // Wait for child
                return 0; // Exit program
            }
            if (read(childPipe[READ], buf, BUF_SIZE) < 0) // Read from child
                perror("reading message");
            // Print uppercase text
            printf("  %s", buf);
        }
    } 
    else         /*      Child    */ 
    {
        close(parentPipe[WRITE]);
        close(childPipe[READ]);
        
        char buf[BUF_SIZE];

        while (1)
        {
            if (read(parentPipe[READ], buf, BUF_SIZE) < 0) // Read from parent
                perror("reading message");
            if ((buf[0] == 'q' || buf[0] == 'Q') && buf[1] == '\n'){
                close(parentPipe[READ]);
                close(childPipe[WRITE]);
                exit(0); // Exit child process
            }
            
            toUpperCase(buf);

            if (write(childPipe[WRITE], buf, BUF_SIZE) < 0) // Write to parent
                perror("writing message");
        }
    }
}

void toUpperCase(char *str)
{
    int i;

    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 0x20;
    }
}