//Read the NOTES section in the wait manual page (man 2 wait) to get a clear
//idea about zombie processes. And tell me why zombie is not welcomed.

//Compile and run this small program. This program can leave a zombie process
//in the system. You can see it on shell with ps u or ps ax command.



#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	pid_t pid;

	int i;
	for(i = 0; i < 5; i++)
	{
		if(pid = fork() == 0)
		{
			printf("Zombie %d id: %d\n", i, getpid());
			exit(0);
		}
	}
	while(1);

	exit(0);
}

/*
Your task:

Write a similar program that leaves 5 zombies.




Tell me the difference between exit() and return and what is differences between zombie and orphan child process?
Learn how to avoid zombies with waitpid() system call. FYI! Consult google!!!

And correct the above program.

Sum up: Please answer the following questions.

    How many hours you spent in this section?
    What's the major problems you met in this section? And,
    How did you solve (or try solving) them?
    Have you learnt anything? Or your time was just wasted?

And,please, attach your solved c-file as tar-ball.

*/
