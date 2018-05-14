/*******************************************************************************
**
**  Julius Lesonen 14.5.2018
**
**  Shared memory with semaphores, parent/child
**
*******************************************************************************/

#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

char n[1024];//kriittinen alue
sem_t len;

void *read1()
{
    while (1)
    {
        printf("Enter text > ");
        scanf("%s", n);
        /*Todo: Kirjoita koodi, joka pyytää käyttäjältä merkkijonon,
          lukee sen käyttäen semaphorea ja tallentaa sen kriittiselle alueelle*/
    }
}

void *write1()
{
    while (1)
    {
        sleep(10);
        for (int i = 0; i < 1024; ++i)
        {
            if (n[i] >= 'a' && n[i] <= 'z') /* If lowercase         */
                n[i] -= ('a'-'A');          /* Convert to uppercase */
        }
        printf("%s\n", n);
        break;
        /*Todo. Kirjoita koodi, joka kirjoittaa kriittisen alueen
          sisällön näytölle käyttäen semaphorea.*/
    }
}

int main()
{
    int status;
    pthread_t tr, tw;

    pthread_create(&tr,NULL,read1,NULL);
    pthread_create(&tw,NULL,write1,NULL);

    pthread_join(tr,NULL);
    pthread_join(tw,NULL);
    return 0;
}
