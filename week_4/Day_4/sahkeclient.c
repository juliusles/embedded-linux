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

/* CLIENT */
int main(int argc,char **argv)
{
    int sockfd;
    struct sockaddr_in serv_addr;
    
    /* Open socket */

    if(( sockfd = socket(PF_INET,SOCK_DGRAM,PF_UNSPEC)) < 0)
        my_err("socket()");

    memset((void *)&serv_addr,sizeof(serv_addr),0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
    serv_addr.sin_port = htons(SERV_UDP_PORT);
    
    dg_cli(stdin,sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

    close(sockfd);
    exit(0);
}

void dg_cli(FILE *fp,int sockfd,const struct sockaddr *pservaddr,int servlen)
{
    int n;
    char sendline[512],recvline[512];

    while(fgets(sendline,512,fp) != NULL )
    {
        n = strlen(sendline);

        if ( sendto(sockfd,sendline,n,0,pservaddr,servlen) != n)
            my_err("sendto()");

        if (( n = recvfrom(sockfd,recvline,512,0,NULL,NULL)) < 0)
            my_err("recvfrom()");

        recvline[n] = '\0';
        fputs(recvline,stdout);
    }

    if ( ferror(fp) )
        my_err("fgets()");
}

