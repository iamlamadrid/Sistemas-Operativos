#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
	PRACTICA 1 SISTEMAS OPERATIVOS
	GENERADOR DE NUMEROS ALEATORIOS
	Autor: Álvaro Lamadrid Agudo
	Curso: 2018-2019
*/
int main(int argc, const char *argv[])
{

	int numero; // numero que se genera aleatoriamente
	int valor_intervalo; // valor del intervalo en el que generaremos los numeros
	srand( time(NULL) );
	/*
		Comprobamos si le estamos pasando a generador un valor para cogerlo
		como intervale. En caso de que no se lo pasemos, le damos un valor
		predetermiando de 100.000.
	*/
	if(argc == 1){
		valor_intervalo = 100000; // valor predeterminado si no hay parametros
	}else{
		valor_intervalo = atoi(argv[1]); // cogemos primer parametro para darle valor al rango
	}

	/*
		A continuación, generamos 1024 números aleatorios entre el rango que le 
		hemos pasado o el que hemos puesto como predeterminado y los pintamos.
	*/
	int i;
	for (i = 0; i < 1024; i++)
	{
		// rango aleatorio entre -valor_intervalo y valor_intervalo:
		numero = rand () % (valor_intervalo-(-valor_intervalo)+1) + -valor_intervalo; 
		printf("%d\n", numero);
	}

}