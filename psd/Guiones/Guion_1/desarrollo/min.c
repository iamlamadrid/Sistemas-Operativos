/* hecho en ansi C */
#include <math.h>
#define  MAXIMO  40
#include <stdio.h>

main()
{
    int   numero;
    float pendiente, abcisa, ordenada, correlacion;
    float x[MAXIMO], y[MAXIMO];
    int captura(float [], float []);
    float calculo(int , float [], float [], float * , float * , float * );

/* esto son pruebas para ver el comportamiento peculiar de la libreria 
    pendiente = cos(0.0L);
    printf(" %f \n",pendiente);
    pendiente = pow(2.0L,4.0L);
    printf(" %f \n",pendiente);

    double ang=1.0;
    printf("%lf\n",sin(ang));
    printf("%lf\n",sin(1.0));
*/

    numero = captura(x, y);
    correlacion = calculo(numero, x, y, &pendiente, &abcisa, &ordenada);
    printf("Pendiente %f, Abcisa %f, Ordenada %f, Correlacion %f \n",
				 pendiente, abcisa, ordenada, correlacion);
}


int captura(float x[], float y[])
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



float calculo(int numero, float x[], float y[], float * pendiente, float * abcisa, float * ordenada)
{

   float sumax=0.0, sumay=0.0, sumax2=0.0, sumay2=0.0, sumaxy=0.0;
   float mediax, mediay;
   float correlacion;
   int i;

   for(i=0;i<numero;i++)
   {
	sumax += x[i];
	sumay += y[i];
	/* sumax2 += x[i]*x[i]; */
	sumax2 += pow(x[i],2);
	sumay2 += y[i]*y[i];
	sumaxy += x[i] * y[i];
   }

   mediax = sumax / numero;
   mediay = sumay*sumay / numero;

   *pendiente = (sumaxy - mediax * sumay) / (sumax2 - mediax * sumax);
   *ordenada = (sumay - *pendiente * sumax) / numero;
   *abcisa   = - *ordenada / *pendiente;
   correlacion = (*ordenada * sumay + *pendiente * sumaxy - mediay)
			      / (sumay2 - mediay);
   return(correlacion);
}
