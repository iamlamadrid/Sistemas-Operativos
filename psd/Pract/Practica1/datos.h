/*
 * Definicion de la variable N
 * que utilizamos para el tamaño
 * de las estructuras
 */
#define N 100

/*
 * Definicion de las estructuras
 * utilizadas en los diferentes apartados
 */
typedef struct stItem {
  int categoria;
  int frecuencia;
  float suma;
  int al;
} Item;

typedef struct stItem2 {
  int categoria;
  float media;
} Item2;
