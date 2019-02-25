#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "datos.h"
/*
 * Metodos que se van a utilizar
 * externos a este fichero
 */
void leer_entrada(Item par[]);
void imprimir_resultado(Item par[]);
/*
 * Funcion main desde la que se
 * va a llamar a las diferentes
 * funciones
 */
int main() {
/*
 * Variable de la estructura creada Item
 */
  Item items[N];
  srand(time(NULL));
/*
 * Inicializacion de la estructura
 */
  for(int i = 0; i<100;i++){
    items[i].categoria = i;
    items[i].frecuencia = 0;
    items[i].suma =0;
    items[i].al = rand()%2;
  }
/*
 * Llamada de las funciones de
 * lectura de datos y de
 * impresion por pantalla de
 * los mismos
 */
  leer_entrada(items);
  imprimir_resultado(items);
  return 0;
}
