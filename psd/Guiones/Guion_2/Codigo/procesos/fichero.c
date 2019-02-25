#include <stdio.h>
#include <sys/types.h>
main()
{
	pid_t creado;
	FILE *fiche;


	creado = fork();  		/* creo dos procesos */

	if (creado == 0)   /* hijo */
	{
		fiche = fopen("pepe", "w"); 	/* abro un fichero */

		puts("Soy el hijo"); /* no necesita abrir el fichero */
		fputs("Escribe el hijo\n", fiche);
		fclose(fiche);
	}
	else if (creado > 0)   /* padre */
	{
		fiche = fopen("pepe", "w"); 	/* abro un fichero */

		sleep(4);   /* para asegurar que lo cierra el anterior */
		fputs("Escribe el padre\n", fiche);
		printf("Soy el padre, el hijo es %d \n",creado);
	}
	else
		puts("El fork no ha funcionado");
}
