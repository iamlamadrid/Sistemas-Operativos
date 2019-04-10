#include <stdlib.h>
#include <stdio.h>

/*
	PRACTICA 1 SISTEMAS OPERATIVOS
	FILTRO DE NUMEROS GENERADOS
	Autor: Álvaro Lamadrid Agudo
	Curso: 2018-2019
*/
int main(int argc, const char *argv[])
{
	int limite; // intervalo de los limites donde pasaremos el numero a stdout
	/*
		Comprobamos si se le ha pasado un limite como argumento, 
		en caso de no ser asi pedimos introducir un limite
	*/
	if(argc == 1){
		printf("Por favor introducir límite:\n");
		scanf("%d",&limite);
	}else{
		limite = atoi(argv[1]);
	}

	/*
		Comprobamos toda la serie de datos que se nos pasan y dependiendo si
		están en el límite los metemos en stdout o en stderr
	*/
    int numero; // numero que vamos a leer
    int check; // escaner de cada numero
    check = scanf("%d",&numero);
    // mientras siga habiendo numeros seguimos comprobando
    while( !(check <= 0) ){
        if(numero>(-limite) &&  numero<limite){
        	// al estar dentro del limite lo mandamos a stdout
            fprintf(stdout,"%d\n", numero);
        }else{
        	// al estar fuera del limite lo mandamos a stderr
        	fprintf(stderr,"%d\n", numero);
        }
        check = scanf("%d",&numero); // escaneamos siguiente numero
    }
}