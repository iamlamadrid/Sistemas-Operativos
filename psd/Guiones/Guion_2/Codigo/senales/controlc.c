#include <signal.h>
#include <stdio.h>
void coger(int);       /* prototipo manejador */

main()
{
        int i;

        /* si la interrupcion llega ahora se abortara el proceso */
        if (signal(SIGINT, coger) == SIG_ERR)
                perror("error en signal");
        /* si llega ahora se ira a ejecutar la funcion coger */
        for(i=1;i<5;i++)
        {
                printf("Duermo %d segundo \n",i);
                sleep(1);
        }
}
void coger(int tipo)
{
        printf("La senal cogida es de tipo %d \n",tipo);
}

