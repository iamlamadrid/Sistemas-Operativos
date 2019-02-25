#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, const char *argv[])
{
	int numero;
	int valor_intervalo;

	if(argc == 1){
		valor_intervalo = 100000; // valor predeterminado si no hay parametros
	}else{
		valor_intervalo = atoi(argv[1]);
	}

	for (int i = 0; i < 1024; i++)
	{
		numero = rand () % (valor_intervalo-(-valor_intervalo)+1) + -valor_intervalo; // rango aleatorio entre -valor_intervalo y valor_intervalo
		printf("%d\n", numero);
	}
}