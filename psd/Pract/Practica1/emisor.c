#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Funcion main que ejecuta tanto la lectura
 * de datos como la impresion por pantalla
 */
int main( ) {
/*
 * Variables utilizadas para la realizacion
 * de los scans y prints
 */
  int NI;
  int NC;
  float VMAX;
  float VMIN;
  int CAT;
  float NUM;
/*
 * Lectura de los datos
 * introducidos por pantalla o por fichero.
 * En el caso de que se introduzcan mal los numeros
 * se parará la ejecucion para evitar un bucle infinito
 * en la ejecucion
 */
  fscanf(stdin,"%d",&NI );
    if (NI < 10 || NI > 1000) {
      fprintf( stderr,"Se ha equivocado escribiendo el numero de iteraciones\n");
      exit(0);
}

  fscanf(stdin,"%d",&NC );
    if (NC < 10 || NC > 100) {
      fprintf( stderr,"Se ha equivocado escribiendo el numero de categorias\n");
      exit(0);
  }

  fscanf(stdin,"%f",&VMIN );
  fscanf(stdin,"%f",&VMAX );
  if(VMIN>VMAX){
    fprintf( stderr,"Ha escrito mas grande el minimo que el maximo\n");
    exit(0);
  }
/*
 * Generacion aleatoria de numeros
 * floats e impresion de los datos por
 * pantalla
 */
  srand(time(NULL));
  for (int i = 0; i < NI; i++) {
    CAT = rand() % NC;
    double RANGE = (VMAX - VMIN);
    double DIV = (RAND_MAX/RANGE);
    NUM =  VMIN + (rand() / DIV);
    fprintf(stdout,"%d %f\n",CAT,NUM);
  }

  return 0;
}
