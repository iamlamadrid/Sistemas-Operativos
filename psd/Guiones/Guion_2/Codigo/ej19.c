#include <signal.h>
#include <stdio.h>
void coger(int);       /* prototipo manejador */

main()
{
	if (signal(SIGINT, coger) == SIG_ERR)
        	perror("error en signal");
        int i = 0;

        /* si la interrupcion llega ahora se abortara el proceso */
        
        /* si llega ahora se ira a ejecutar la funcion coger */
        while(1)
        {
                printf("Duermo %d segundo \n",i);
                sleep(1);
		i++;
        }
}
void coger(int tipo)
{
        printf("La senal cogida es de tipo %d \n",tipo);
}

