#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

int veces = 0;     /* variable global */
void padre(int);   /* funciones manejadoras */
void hijo(int);
int i = 0;
void (*antiguo)(int);
main()
{
	pid_t creado, ppid;
	signal(SIGUSR1, padre);      /* pone SIGUSR1*/

	switch(creado = fork())
	{
	case -1:
		perror("fallo en el fork");
		exit(1);
	case 0:     /* el hijo */
		antiguo=signal(SIGUSR1, hijo);
		ppid = getppid();
		for(;;)
		{
			if(i==5){
				antiguo=signal(SIGUSR1,antiguo);
			}
			if(i==10){
				signal(SIGUSR1,antiguo);
			}
			sleep(1); /* el otro hace el pause */
			/* envio signal al proceso padre */
			kill(ppid, SIGUSR1);
			i++;
			pause();	   /* espero la respuesta */
		}
	default :    /* el padre */
		for(;;)
		{
			pause();   /* espero a que me llamen */
			sleep(1); /* el hijo hace pause */
			kill(creado, SIGUSR1); /* aviso al hijo */
		}
	}
}
/* funcion de manejo de la signal para el padre */
void padre (int senal)
{
	/* ambos procesos tienen una copia de veces */
	printf("El padre cogio la signal numero %d\n", ++veces);
	/* de nuevo para recibir la siguiente signal */
	signal(senal, padre);	/* pone SIGUSR1 para el padre */
}


/* funcion de manejo de la signal para el hijo */
void hijo (int senal)
{
	/* ambos procesos tienen una copia de veces */
	printf("El hijo cogio la signal numero %d\n", ++veces);
	/* de nuevo para recibir la siguiente signal */
	signal(senal, hijo);	/* pone SIGUSR1 para el hijo */
}

