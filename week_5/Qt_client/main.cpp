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

#define SERV_UDP_PORT 11012
#define SERV_TCP_PORT 11012

#define SERV_HOST_ADDR "10.50.61.202"

void str_cli(/*FILE *fp,*/ int sockfd);
void my_err(char *error);


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

       int sockfd;
       struct sockaddr_in serv_addr;
       char  hostAddr[256] = SERV_HOST_ADDR;

       /* Is the application launched with manual host address option*/
       if (argc > 2)
       {
           if(strcmp(argv[1], "-a") == 0)
           {
               sprintf(hostAddr,"%s",argv[2]);
           }

       }

       /* Open socket */

       if(( sockfd = socket(PF_INET,SOCK_STREAM,PF_UNSPEC)) < 0)
           my_err("socket()");

       memset((void *)&serv_addr,sizeof(serv_addr),0);
       serv_addr.sin_family = AF_INET;
       serv_addr.sin_addr.s_addr = inet_addr(hostAddr);
       serv_addr.sin_port = htons(SERV_TCP_PORT);

       if ( connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0 )
          my_err("connect()");

       str_cli(/*stdin,*/sockfd);

       close(sockfd);
       exit(0);

    return a.exec();
}

void my_err(char *error)
{
    perror(error);
    exit(1);
}

void str_cli(/*FILE *fp,*/int sockfd)
{
    int bufLen;
    int sel = 0;
    char recvline[512];
    STRUCT_NUMBERS numbers;


    for(;;)
    {
        while(1)
        {
            printf("Choose an operation: \n%d: Add\n%d: Substract\n%d: Divide\n%d: Multiply\n\n0: Quit\n",
                   ADD,SUBSTRACT,DIVIDE,MULTIPLY);
            scanf("%d",&sel);

            if (sel == 0)
                return;

            if (sel > 0 && sel < 5)
                break;

        }


        numbers.operation = sel;

        printf("Enter the first number: \n");
        scanf("%f",&numbers.number1);

        printf("Enter the second number: \n");
        scanf("%f",&numbers.number2);

        if ( write(sockfd,&numbers,sizeof(numbers)) != sizeof(numbers))
        my_err("write()");

        if (( bufLen = read(sockfd,recvline,sizeof(recvline))) < 0)
        my_err("read()");

        recvline[bufLen] = '\0';
        printf("%s",recvline);

        sleep(1);


    }
 }


