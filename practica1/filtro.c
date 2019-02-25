#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, const char *argv[])
{
	int limite = atoi(argv[1]);
    printf("limite: %d\n", limite);  
    int numero;
    int check;
    check = scanf("%d",&numero);
    while(!(check <= 0)){
        if(numero>(-limite) &&  numero<limite){
            fprintf(stdout,"%d\n", numero);
	    	printf("numero dentro del limite");
        }else{
        	fprintf(stderr,"%d\n", numero);
			printf("numero fuera del limite");
        }
        check = scanf("%d",&numero);
    }
}
