#include <stdlib.h>
#include <unistd.h>

main()
{
	char *av[3];
	av[0] = "ls";
	av[1] = "-l";
	av[2] = (char *)0;
	execv("/bin/ls", av);
	/* si llega aquí hay error */
	perror("fallo de execv"); exit(-1);
}

