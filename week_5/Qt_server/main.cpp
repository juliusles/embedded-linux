#include <QCoreApplication>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mathstruct.h"
#include <pthread.h>

#define SERV_UDP_PORT 11012
#define SERV_TCP_PORT 11012

#define SERV_HOST_ADDR "10.50.61.202" /* localhost */

#define NUM_THREADS 10


void handleRequest(int sockfd);
float calculate(STRUCT_NUMBERS *numbers);
void my_err(char *error);
void *threadFunction(void *arg);


int main(int argc, char *argv[]){

    QCoreApplication a(argc, argv);


/* SERVER */

    int listenfd, newsockfd,  childpid;
    socklen_t clilen;
    struct sockaddr_in cli_addr, serv_addr;
    pthread_t threads[NUM_THREADS];
    int err;
    int i = 0;

    if (( listenfd = socket(PF_INET,SOCK_STREAM,PF_UNSPEC)) < 0 )
        my_err("socket()");

    memset((void *)&serv_addr,sizeof(serv_addr),0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_TCP_PORT);

    if (( bind(listenfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0))
        my_err("bind()");

    if (( listen(listenfd,5 ) < 0))
        my_err("listen()");

    for(;;)
    {
        clilen = (int)sizeof(cli_addr);

        if (( newsockfd = accept(listenfd,(struct sockaddr *)&cli_addr, &clilen)) < 0)
            my_err("accept()");
        if (( childpid = fork()) < 0)
            my_err("fork()");
        else if ( childpid == 0 ) // Child process
        {
            close(listenfd);
            //handleRequest(newsockfd);
            if (err = pthread_create(&threads[i], NULL, threadFunction, (void*)newsockfd))
                my_err("pthread_create()");
            i++;
            exit(0);
        }
        close(newsockfd);

    }
    return a.exec();
}
void handleRequest(int sockfd){
    char mesg[512];
    char recvdata[sizeof(STRUCT_NUMBERS)];
    int bufLen;
    STRUCT_NUMBERS *numbers;

    for(;;)
    {
        bufLen = sizeof(recvdata);
        if ((bufLen = read(sockfd,recvdata,bufLen)) < 0 )
            my_err("read()");
        numbers = (STRUCT_NUMBERS *)&recvdata;

        sprintf(mesg,"\nSERVER: The result is: %f\n\n",calculate(numbers));
        bufLen = strlen(mesg);
        if (write(sockfd,mesg,bufLen) != bufLen)
            my_err("write()");

    }
}

float calculate(STRUCT_NUMBERS * numbers)
{
    switch(numbers->operation)
    {
        case ADD:
        {
            return numbers->number1 + numbers->number2;
        }

        case SUBSTRACT:
        {
            return numbers->number1 - numbers->number2;
        }

        case DIVIDE:
        {
            return numbers->number1 / numbers->number2;
        }

        case MULTIPLY:
        {
            return numbers->number1 * numbers->number2;
        }

        default:
        {
            return 0.0f;
        }
    }

}
void my_err(char *error)
{
    perror(error);
    exit(1);
}

void *threadFunction(void *arg)
{
    printf("Thread created.\n");
    int sockfd = (int)arg;
    handleRequest(sockfd);
    pthread_exit(NULL);
}


