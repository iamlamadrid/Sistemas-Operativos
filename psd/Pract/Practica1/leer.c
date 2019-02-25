#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "datos.h"

/*
 * Funcion de lectura por
 * teclado o archivo
 */
void leer_entrada(Item par[] ) {
  int categoria;
  float suma;

  while(fscanf(stdin,"%d %f",&categoria,&suma ) != -1){
      par[categoria].categoria = categoria;
      par[categoria].frecuencia += 1;
      par[categoria].suma +=suma;
  }

}
