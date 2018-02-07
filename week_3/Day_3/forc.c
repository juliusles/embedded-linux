#include <stdio.h>
#include <unistd.h>

int main() {
        printf("Luodaan taustaprosessi\n");
        pid_t pid = fork();
        if (pid==0)     /* Lapsiprosessille pid n�kyy nollana */
                printf("Olen lapsiprosessi\n");

        else if (pid>0)    /* Forkkaus onnistui, t�m� on is�nt� */
                printf("Olen is�nt�prosessi\n");
        printf("Terve Linux.fi\n");
        return 0;
}