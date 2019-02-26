#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
	int limite = atoi(argv[1]);
    int numero;
    int check;
    check = scanf("%d",&numero);
    while( !(check <= 0) ){
        if(numero>(-limite) &&  numero<limite){
            fprintf(stdout,"%d\n", numero);
        }else{
        	fprintf(stderr,"%d\n", numero);
        }
        check = scanf("%d",&numero);
    }
}
