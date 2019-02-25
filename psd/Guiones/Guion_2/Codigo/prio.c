#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

int main()
{
    int prioridad, control;
    pid_t pid;
    puts("Solo un proceso");
    puts("Llamo a fork");
    pid = fork();
    if (pid == 0) 
    { 
    		prioridad=getpriority(PRIO_PROCESS, 0);
      	printf("Hijo pid %d con prioridad %d \n",getpid(),prioridad);
      	control=setpriority(PRIO_PROCESS, 0, 10);
		prioridad=getpriority(PRIO_PROCESS, 0);
      	printf("Hijo pid %d con prioridad %d control %d\n",getpid(),prioridad, control);
    }

    else if (pid > 0)
    { 
    		prioridad=getpriority(PRIO_PROCESS, 0);
      	printf("Padre pid %d con prioridad %d \n",getpid(),prioridad);
    		control=setpriority(PRIO_PROCESS, 0, -10);
  		prioridad=getpriority(PRIO_PROCESS, 0);
      	printf("Padre pid %d con prioridad %d control %d\n",getpid(),prioridad, control);
    }
    else
         perror("El fork no ha funcionado");
}
