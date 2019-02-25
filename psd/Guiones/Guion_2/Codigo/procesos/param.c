#include <stdio.h>
#include <stdlib.h>
main(int argc, char *argv[], char **entorno)
{
    int i;
    char *valor;

    valor = malloc(100);

    for (i = 0; i < argc; i++)
	puts(argv[i]);
    valor = getenv(argv[1]);    // no puede ser un array 
    if (valor)                 // si valor es NULL no puede escribirse
       printf("El valor de %s es %s \n",argv[1],valor);

    while(*entorno != (char *)0)
	puts(*entorno++);

}
