#include <stdio.h>
#include <sys/types.h>
main()
{
        pid_t creado;
        int comun = 0;          /* comun ? */

        creado = fork();
        if (creado == 0)   /* el hijo */
        {
                printf("Soy hijo, comú7, ahora vale %d\n",comun);
                comun = 7;
                printf("Soy hijo, comúle ahora %d \n",comun);
        }
        else if (creado > 0)    /* el padre */
        {
                sleep(1);
                printf("Soy padre, comú3, ahora vale %d\n", comun);
                comun = 3;
                printf("Soy padre, comúle %d \n",comun);
        }
        else  
        {
                perror("El fork no ha funcionado");
        }
}

