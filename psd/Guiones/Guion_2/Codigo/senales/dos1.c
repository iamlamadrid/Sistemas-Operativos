#include <stdio.h>
#include <stdlib.h>
#define    tamano   40 
main()
{
	char *msg1 = "El primer mensaje";
	char *msg2 = "El segundo mensaje";
	char *msg3 = "El tercer mensaje";
	char buffer[tamano];
	int descriptor[2];
	int i, creado, creado2;
	/* se abre la pipe */
	if (pipe(descriptor) < 0)
	{
		perror("Error en la llamada");
		exit(1);
	}

	if((creado=fork()) < 0)
	{
		perror("Error en el fork");
		exit(2);
	}
	if (creado > 0)
	{

		if((creado2=fork())<0){
			perror("Error en el fork");
			exit(2);
		}	
		if(creado2 == 0){
			close(descriptor[1]);
			for(i=0;i<3;i++){
				read(descriptor[0],buffer,tamano);
				puts(buffer);
	  		}
		}
	}
	if (creado == 0)
	{
		close(descriptor[0]);
		if((creado=fork()) < 0)
		{
			perror("Error en el fork");
			exit(3);
		}
		if (creado > 0)
			write(descriptor[1],msg1, tamano);
		if (creado==0)
		{
			write(descriptor[1],msg2, tamano);
			write(descriptor[1],msg3, tamano);
		}
	}
}

