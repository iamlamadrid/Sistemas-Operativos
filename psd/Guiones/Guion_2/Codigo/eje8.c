#include <stdlib.h>
#include <unistd.h>

main()
{
	puts("ejecutando");
	execl("/Users/diego/Dropbox/Universidad/3º/Segundo Cuatrimestre/Sistemas Operativos/Guiones/Guion_2", "./a.out", (char *)0);
	/* si se ejecuta la siguiente orden la llamada ha fallado */
	perror("execl fallo al intentar correr ej8");
	exit(1);
}
