#include <stdio.h>
#include <unistd.h>

int main() {
        printf("Luodaan taustaprosessi\n");
        pid_t pid = fork();
        if (pid==0)     /* Lapsiprosessille pid näkyy nollana */
                printf("Olen lapsiprosessi\n");

        else if (pid>0)    /* Forkkaus onnistui, tämä on isäntä */
                printf("Olen isäntäprosessi\n");
        printf("Terve Linux.fi\n");
        return 0;
}