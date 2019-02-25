#include <stdlib.h>
#include <unistd.h>

main()
{
	puts("ejecutando echo");
	execl("/bin/echo", "echo","hola" ,(char *)0);
	/* si se ejecuta la siguiente orden la llamada ha fallado */
	perror("execl fallo al intentar correr echo");
	exit(1);
}
