#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include "datos.h"

/*
 * Funcion de lectura de datos
 */
void leer_entrada(Item2 par[] ) {
  int categoria;
  int frecuencia;
  float suma;
  int i = 0;
  while(fscanf(stdin,"%d %d %f",&categoria,&frecuencia, &suma ) != -1){
      par[i].categoria = categoria;
      par[i].media = suma/frecuencia;
      i++;

  }
}

/*
 * Funcion de impresion por pantalla
 */
void imprimir_resultado(Item2 par[],int min, int max){
  for(int i = 0 ; i<100;i++){
    if(par[i].media != 0){
    fprintf(stdout,"%2d %f\n", par[i].categoria, par[i].media );
    }
  }
  fprintf(stderr, "Categoria con el valor minimo: %d\nCategoria con el valor maximo: %d\n", min,max );
}

/*
 * Funcion main
 */
int main() {
  Item2 items[N];
/*
 * Inicializacion de la estructura items
 */
  for(int i =0 ; i<100;i++){
    items[i].categoria = 0;
    items[i].media = 0;
  }
/*
 * Proceso de lectura que almacena los
 * datos en la estructura items
 */
  leer_entrada(items);
/*
 * Creacion de variables auxiliares para
 * determinar la categoria con valor mas
 * grande y mas pequeño
 */
  float maxV = -FLT_MAX;
  float minV = FLT_MAX;
  int max = 0;
  int min = 0;
  for (int i = 0; i < 100; i++) {
    if(items[i].media > maxV){
      maxV = items[i].media;
      max = items[i].categoria;
    }
    if(items[i].media < minV&& items[i].media>0){
      minV = items[i].media;
      min = items[i].categoria;
    }
  }
  /*
   * Proceso de impresion de los datos
   */
  imprimir_resultado(items,min,max);
  return 0;
}
