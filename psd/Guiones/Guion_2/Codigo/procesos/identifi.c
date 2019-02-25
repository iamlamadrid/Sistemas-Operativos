#include <stdio.h>

main()
{
    int pid;
    puts("Solo un proceso");
    puts("Llamo a fork");
    pid = fork();
    if (pid == 0) 
         printf("Hijo pid %d ppid %d grupo %d \n",getpid(),getppid(),getpgrp());
    else if (pid > 0) 
         printf("Padre pid %d ppid %d grupo %d \n",getpid(),getppid(),getpgrp());
    else
         perror("El fork no ha funcionado");
}
