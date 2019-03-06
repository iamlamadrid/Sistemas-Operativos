#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main(int argc, const char *argv[])
{
	int numero; // numero que se genera aleatoriamente
	int valor_intervalo; 
	srand( time(NULL) );
	if(argc == 1){
		valor_intervalo = 100000; // valor predeterminado si no hay parametros
	}else{
		valor_intervalo = atoi(argv[1]); // cogemos primer parametro para darle valor al rango
	}

	for (int i = 0; i < 1024; i++)
	{
		numero = rand () % (valor_intervalo-(-valor_intervalo)+1) + -valor_intervalo; // rango aleatorio entre -valor_intervalo y valor_intervalo
		printf("%d\n", numero);
	}
}