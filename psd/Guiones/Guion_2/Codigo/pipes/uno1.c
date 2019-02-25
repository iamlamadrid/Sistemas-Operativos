#include <stdio.h>
#include <stdlib.h>
#define   tamano   120
main()
{
	char *msg1[2];
	char *msg2[2];
	char *msg3[2];
	
	scanf("%c",msg1);
	scanf("%c",msg2);
	scanf("%c",msg3);
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

