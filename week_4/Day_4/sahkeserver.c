/* SERVER */
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define SERV_UDP_PORT 11012
#define SERV_TCP_PORT 11012

#define SERV_HOST_ADDR "127.0.0.1" 

void my_err(char *error)
{
    perror(error);
    exit(1);
}

int main(int argc,char **argv)
{
    int sockfd;
    struct sockaddr_in cli_addr, serv_addr;

    if (( sockfd = socket(PF_INET,SOCK_DGRAM,PF_UNSPEC)) < 0 )
        my_err("socket()");

    memset((void *)&serv_addr,sizeof(serv_addr),0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_UDP_PORT);
    
    if (( bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0))
        my_err("bind()");

    dg_echo(sockfd,(struct sockaddr *)&cli_addr,sizeof(cli_addr));
}

void dg_echo(int sockfd,struct sockaddr *pcliaddr,int clilen)
{
    int n,len;
    char mesg[512];

    for(;;)
    {
        len = clilen;

        if ((n = recvfrom(sockfd,mesg,512,0,pcliaddr,&len)) < 0 )
            my_err("recvfrom()");

        if (sendto(sockfd,mesg,n,0,pcliaddr,len) != n)
            my_err("sendto()");
    }
}


