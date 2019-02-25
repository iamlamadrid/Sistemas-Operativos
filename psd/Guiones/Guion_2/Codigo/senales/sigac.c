#include <signal.h>
#include <stdio.h>
void coger(int);       /* prototipo manejador */

main()
{
        int i;
        struct sigaction accion, vieja;

        accion.sa_handler=coger;
        sigemptyset(&accion.sa_mask);
        // comportamiento clasico
        accion.sa_flags=SA_NOCLDSTOP|SA_RESTART|SA_ONESHOT|SA_NOMASK;

        if (sigaction(SIGINT, &accion, &vieja) <0 )
                perror("error en sigact");
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
