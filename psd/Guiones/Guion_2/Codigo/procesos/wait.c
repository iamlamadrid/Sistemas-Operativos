#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
main()
{
    int codigo,pid;
    puts("Solo un proceso, despues llamo a fork");
    pid = fork();
    if (pid == 0)
    {
         puts("Soy el hijo");
         kill(getpid(),SIGTERM);
    }
    else if (pid > 0)
    {
         printf("Soy el padre, el hijo es %d \n",pid);
         wait(&codigo);
         if(WIFSIGNALED(codigo)){
         printf("El codigo de la señal de fin es %d \n",WTERMSIG(codigo));
       }

    }
    else
         puts("El fork no ha funcionado");
}
