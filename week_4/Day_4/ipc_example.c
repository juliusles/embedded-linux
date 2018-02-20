#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <synch.h>
#include <sys/types.h>
#include <unistd.h>

/* a structure that will be used between processes */
typedef struct {
	sema_t mysema;
	int num;
} buf_t;

main()
{
int 	i, j, fd;
buf_t 	*buf;

/* open a file to use in a memory mapping */
fd = open("/dev/zero", O_RDWR);

/* create a shared memory map with the open file for the data 
   structure that will be shared between processes */
buf=(buf_t *)mmap(NULL, sizeof(buf_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

/* initialize the semaphore -- note the USYNC_PROCESS flag; this makes
   the semaphore visible from a process level */
sema_init(&buf->mysema, 0, USYNC_PROCESS, 0);

/* fork a new process */
if (fork() == 0) {
	/* The child will run this section of code */
	for (j=0;j<5;j++)
		{
		/* have the child "wait" for the semaphore */

		printf("Child PID(%d): waiting...\n", getpid());
		sema_wait(&buf->mysema);

		/* the child decremented the semaphore */

		printf("Child PID(%d): decrement semaphore.\n", getpid());
		}
	/* exit the child process */
 	printf("Child PID(%d): exiting...\n", getpid());
	exit(0);
	}

/* The parent will run this section of code */
/* give the child a chance to start running */

sleep(2);

for (i=0;i<5;i++)
	{
	/* increment (post) the semaphore */

	printf("Parent PID(%d): posting semaphore.\n", getpid());
	sema_post(&buf->mysema);

	/* wait a second */
	sleep(1);
	}

/* exit the parent process */
printf("Parent PID(%d): exiting...\n", getpid());

return(0);
}