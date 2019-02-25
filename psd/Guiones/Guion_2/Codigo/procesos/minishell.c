#include <stdio.h>
#include <unistd.h>

main()
{
    int pid;
    puts("Solo un proceso, despues llamo a fork");
    pid = fork();
    if (pid == 0)
    {
         puts("Soy el hijo");
         puts("Voy a ejecutar el exec de la creacion");
         execlp("/bin/ls","ls","-l", (char *)0);
         //perror("El exec ha fallado");
    }
    else if (pid > 0)
    {
         printf("Soy el padre, el hijo es %d \n",pid);
         sleep(10);
         puts("El padre termina");
    }
    else
         puts("El fork no ha funcionado");
}
