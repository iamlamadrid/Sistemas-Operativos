#include <stdlib.h>
#include <unistd.h>

main()
{
	puts("ejecutando ls");
	execl("/bin/ls", "ls", "-l", (char *)0);
	/* si se ejecuta la siguiente orden la llamada ha fallado */
	perror("execl fallo al intentar correr ls");
	exit(1);
}

