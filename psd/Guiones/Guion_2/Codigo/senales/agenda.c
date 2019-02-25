#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#define beep   '\007'
#define TRUE   1
#define FALSE  0
int alarma = FALSE;
void coger()                    /* se puede declarar antes */
{
                alarma = TRUE;
}
main(int cuenta, char *argumentos[])
{
        int segundos, creado, j;
        void coger();
        if (cuenta < 3)         /* numero de argumentos */
        {
                perror("agenda: Error argumentos");
                exit(1);
        }
        if ((segundos=atoi(argumentos[1])*60) <= 0)
        {
                perror("agenda: tiempo no valido");
                exit(2);
        }
        switch(creado = fork())
        {
                case -1:
                        perror("Agenda: error en fork");
                        exit(3);
                case 0:   /* en background */
                        break;
                        default :
                        printf("Agenda: process-id %d\n", creado);
                        exit(0);
        }
        signal(SIGALRM, coger);
        alarm(segundos);
        pause();
        if (alarma == TRUE)
        {
                putchar(beep);
                for(j=2; j < cuenta; j++)
                printf("%s ", argumentos[j]);
                printf("\n");
                                                                               }        exit(0);
}
