#include <stdio.h>
#include <sys/types.h>

main()
{
    pid_t pid;
    puts("Solo un proceso");
    puts("Llamo a fork");
    pid = fork();
    if (pid == 0) 
         puts("Soy el hijo");
    else if (pid > 0) 
         printf("Soy el padre, el hijo es %d \n",pid);
    else
         puts("El fork no ha funcionado");
}

