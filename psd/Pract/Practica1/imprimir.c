#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "datos.h"

/*
 * Funcion de impresion por
 * pantalla
 */
void imprimir_resultado(Item par[]){
  srand(time(NULL));
/*
 * Dependiendo de si el int al
 * de la estructura es 0 o 1 se
 * imprime primero o despues
 */
  for(int i = 0 ; i<100;i++){
    if(par[i].al==1){
      if(par[i].frecuencia != 0){
      fprintf(stdout,"%d %d %f\n",par[i].categoria,par[i].frecuencia,par[i].suma );
      }
    }
  }
  for(int i = 0 ; i<100;i++){
    if(par[i].al==0){
      if(par[i].frecuencia != 0){
      fprintf(stdout,"%d %d %f\n",par[i].categoria,par[i].frecuencia,par[i].suma );
      }
    }
  }
}
