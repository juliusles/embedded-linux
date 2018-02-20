#include<stdio.h>

int main(int argc, char *argv[]) {
    FILE *fp=NULL;
   
    char buf[1024];
    if(argc != 2)
    {
        printf("Usage: %s command\n",argv[0]);
        return 0;
    }
       
    printf("**********Suorittamassa popen-kutsun...\n");
    fp = popen(argv[1],"r");
   
    if(fp == NULL) { perror("popen"); return -1; }
   
    while(fgets(buf,1024,fp) != NULL)
        printf("popen says: %s",buf);
       
    printf("**********popen suoritettu\n");
       
    return 0;