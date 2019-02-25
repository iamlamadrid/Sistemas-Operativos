// version con los ficheros fuente incluidos
#define  MAXIMO  40
#include "cal.c"
#include "cap.c"


main()
{
    int   numero;
    float pendiente, abcisa, ordenada, correlacion;
    float x[MAXIMO], y[MAXIMO];

    int captura(float [], float []);
    float calculo(int , float [], float [], float * , float * , float * );

    numero = captura(x, y);
    correlacion = calculo(numero, x, y, &pendiente, &abcisa, &ordenada);
    printf("Pendiente %f, Abcisa %f, Ordenada %f, Correlacion %f \n",
				 pendiente, abcisa, ordenada, correlacion);
}

