#include <stdio.h>

int captura(x, y)
    float x[], y[];
{
    int i;
    int numero;

     printf("Introduce el numero de datos : ");
     scanf("%d", &numero);
     for( i=0; i<numero; i++)
     {
	 printf("%d   Dato x  Dato y : ",i);
	 scanf("%f %f",&x[i],&y[i] );
     }
     return(numero);
}


