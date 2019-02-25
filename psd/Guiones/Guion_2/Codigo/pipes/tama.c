#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <limits.h>
#define  tamano   1

int cuenta = 0;

main()
{
	char msg = 'A';
	int descriptor[2];
	int creado;
	void alarma();

	/* recojo la senal de alarma */
	signal(SIGALRM, alarma);
	/* se abre la pipe */
	if (pipe(descriptor) < 0)
	{
		perror("Error en la llamada");
		exit(1);
	}
	for(;;)	
	/* se saldra por senal no manejada */
	{
		alarm(1);  /* se activa la alarma */
		write(descriptor[1], &msg, tamano);
		/* si pasa la escritura se desactiva */
		alarm(0);
		/* se aumenta el tamano */
		cuenta++;
		if((cuenta%1000) == 0)
 			 printf("Cuenta %d \n", cuenta);
	}
}

void alarma()
{
	printf("Se paro en %d \n",cuenta);
	printf("No se deberia escribir mas de %d \n",PIPE_BUF);
	exit(0);
}

