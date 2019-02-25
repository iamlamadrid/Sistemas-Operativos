#include <stdio.h>
#include <stdlib.h>
#define   tamano   120
main()
{
	char *msg1 = "El primer mensaje";
	char *msg2 = "El segundo mensaje";
	char *msg3 = "El tercer mensaje";

	char buffer[tamano];
	int descriptor[2];
	int i;

	/* se abre la pipe */
	if (pipe(descriptor) < 0)
	{
		perror("Error en la llamada");
		exit(1);
	}

/* se escribe en la pipe */
write(descriptor[1], msg1, tamano);
write(descriptor[1], msg2, tamano);
write(descriptor[1], msg3, tamano);
/* se lee de la pipe */
for(i=0; i<3; i++)
{
read(descriptor[0],buffer, tamano);
	puts(buffer);  // al ser puts filtra todo lo que hemos metido de mas hasta 40
}
	/* se podrian cerrar */
}

