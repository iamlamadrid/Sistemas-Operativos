#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
	int limite;
	// Comprobamos si se le ha pasado un limite como argumento, en caso de no ser asi lo pedimos
	if(argc == 1){
		printf("Por favor introducir límite:\n");
		scanf("%d",&limite);
	}else{
		limite = atoi(argv[1]);
	}

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
