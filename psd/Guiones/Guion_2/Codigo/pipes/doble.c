#include <stdio.h>
#include <stdlib.h>
#define   tamano   40 
main()
{
	char *msg1 = "El primer mensaje";
	char *msg2 = "El segundo mensaje";
	char *msg3 = "El tercer mensaje";
	char buffer[tamano];
	int descrip1[2];	 
	int descrip2[2];
	int j, creado;

	/* se abre la pipe primera */
	if (pipe(descrip1) < 0)
	{
		perror("Error al crear pipe 1");
		exit(1);
	}
	/* se abre la segunda pipe */
	if (pipe(descrip2) < 0)
	{
		perror("Error al crear pipe 2");
		exit(2);
	}

	if((creado=fork()) < 0)
	{
		perror("Error en el fork");
		exit(3);
	}
	if (creado > 0)
	{
	    close(descrip1[0]);
	    write(descrip1[1], msg1, tamano);
	    write(descrip1[1], msg2, tamano);
	    write(descrip1[1], msg3, tamano);
	    /* el read se bloquea si esta vacia */
	    close(descrip2[1]);
	    for(j=0;j<3;j++)
	    {
		read(descrip2[0], buffer, tamano);
		printf("padre %s \n", buffer);
	    }
	}

	if (creado == 0)
	{
		 close(descrip2[0]);
	    write(descrip2[1], msg1, tamano);
	    write(descrip2[1], msg2, tamano);
	    write(descrip2[1], msg3, tamano);
	    /* el read se bloquea si esta vacia */
	    close(descrip2[1]);
	    for(j=0;j<3;j++)
	    {
		read(descrip1[0], buffer, tamano);
		printf("hijo %s \n", buffer);
	    }
	}
}

