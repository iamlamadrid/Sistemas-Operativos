#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/wait.h>
#include <float.h>
#include "datos.h"

//Declaracion de los threads que vamos a utilizar
pthread_t H1;
pthread_t H2;
pthread_t T[M];
pthread_t R;

//Declaracion de los semaforos que vamos a utilizar
pthread_mutex_t mutex[M];
pthread_mutex_t acabados;
pthread_cond_t procesando;

// Estructura con 3 variables:
// estado para saber como esta la fila
// NVP para saber el numero de veces procesado
// SM para saber la suma de las medias
typedef struct data{
  int estado;
  int NVP;
  float SM;
}data;

//Array de M estructuras, una por cada fila de la matriz
data listaEstruc[M];
//Matriz utilizada de M*N
int DATOS[M][N];
// Variable para saber si se han escrito 2*V lineas
int numAcabados;


/*
 * Funcion para H1
 */
void *escribePares(){
  // Variable locales
  int i,j,r;
  // V iteraciones, V filas escritas
  for(i = 0; i<V;i++){
    // Generacion de numero aleatorio entre 0 y M-1 hasta que sea par
    r=rand() % M;
    while(r % 2 != 0){
      r = rand() % M;
    }
    // Cojo el mutex
    pthread_mutex_lock(&mutex[r]);
    // Mientras el estado sea 1 (que ya esta escrito), espero a la señal
    while(listaEstruc[r].estado == 1){
      pthread_cond_wait(&procesando,&mutex[r]);
    }
    // Relleno las filas pares con un valor aleatorio entre -K y K
    for(j = 0;j<N;j++){
      DATOS[r][j] = rand()%(K-(-K)+1)+(-K);
    }
    // La fila ya esta escrita,con lo que cambio el estado
    listaEstruc[r].estado = 1;
    printf("H1: Iteracion %d Fila %d \n",i, r );
    // Cojo el mutex de acabados
    pthread_mutex_lock(&acabados);
    // Añado uno por fila escrita
    numAcabados++;
    // Devuelvo ambos mutex
    pthread_mutex_unlock(&acabados);
    pthread_mutex_unlock(&mutex[r]);

    }
    pthread_exit(NULL);
}

/*
 * Funcion para H2
 */
void* escribeImpares(){
  // Variable locales
  int i,j,r;
  // V iteraciones, V filas escritas
  for(i = 0; i<V;i++){
    // Generacion de numero aleatorio entre 0 y M-1 hasta que sea par
    r=rand() % M;
    while(r % 2 != 1){
      r = rand() % M;
    }
    // Cojo el mutex
    pthread_mutex_lock(&mutex[r]);
    // Mientras el estado sea 1 (que ya esta escrito), espero a la señal
    while(listaEstruc[r].estado == 1){
      pthread_cond_wait(&procesando,&mutex[r]);
    }
    // Relleno las filas pares con un valor aleatorio entre -K y K
    for(j = 0;j<N;j++){
      DATOS[r][j] = rand()%(K-(-K)+1)+(-K);
    }
    // La fila ya esta escrita,con lo que cambio el estado
    listaEstruc[r].estado = 1;
    printf("H2: Iteracion %d Fila %d \n",i, r );
    // Cojo el mutex de acabados
    pthread_mutex_lock(&acabados);
    // Añado uno por fila escrita
    numAcabados++;
    // Devuelvo ambos mutex
    pthread_mutex_unlock(&acabados);
    pthread_mutex_unlock(&mutex[r]);

    }
    pthread_exit(NULL);
}


/*
 * Funcion para threads T
 */
void* calcula(void* row)
{
  // Variables locales
  int i,sum;
  float media;
  // Cast para que no salte warning
  int fila = (intptr_t)row;
  while (1) {
    while (1) {
      pthread_mutex_lock(&acabados);
      //Si la fila esta llena se pone a calcular
      if(listaEstruc[fila].estado == 1){
        pthread_mutex_unlock(&acabados);
        break;
      }
      sum = 0;
      pthread_mutex_lock(&acabados);
      // Si acabados es 2 veces V acaba
      if(numAcabados>=(2*V)){
        pthread_mutex_unlock(&acabados);
        pthread_exit(NULL);
      }
      pthread_mutex_unlock(&acabados);
    }
    // Calculos
    pthread_mutex_lock(&mutex[fila]);
    for(i = 0;i<N;i++){
      sum = sum + DATOS[fila][i];
    }
    media =(float)sum/(float)N;
    listaEstruc[fila].estado = 0;
    listaEstruc[fila].NVP ++ ;
    listaEstruc[fila].SM += media;
    printf("T:  Fila: %d  Media: %f \n" , fila,media);
    //libero mutex y mado señal
    pthread_mutex_unlock(&mutex[fila]);
    pthread_cond_signal(&procesando);
  }
}

/*
 * Funcion para R
 */
void* ganador(){
  float total = FLT_MIN;
  int mayor ;
  int fila;
  for(fila = 0;fila<M;fila++){
    if((listaEstruc[fila].SM/(float)listaEstruc[fila].NVP)>total){
      mayor = fila;
      total = (listaEstruc[fila].SM/(float)listaEstruc[fila].NVP);
    }
  }
  pthread_exit((void*) (intptr_t) mayor);
}

/*
 * Hilo principal
 */
void main(){
  //Varibales auxiliares
  int i;
  int winner;

  //Inicializacion de las filas leidas
  numAcabados = 0;

  // Inicializacion del array de estructuras
  for(i = 0;i < M;i++){
    listaEstruc[i].estado = 0;
    listaEstruc[i].NVP = 0;
    listaEstruc[i].SM = 0.0;
  }
  // Semilla del random
  srand(time(NULL));

  // Inicializaciones de los mutex
  for(i = 0;i < M;i++){
    pthread_mutex_init(&mutex[i],NULL);
  }
  pthread_mutex_init(&acabados,NULL);

  //Inicializacion de la variable condicional
  pthread_cond_init(&procesando,NULL);

  // Creacion de los threads T
  for(i = 0;i < M;i++){
    if(pthread_create(&T[i], NULL, (void *)calcula,(void *)(intptr_t)i)!=0){
      perror("Error en la creacion de los hilos T");
    }
  }

  // Creacion del thread H1
  if(pthread_create(&H1, NULL, (void *)escribePares,NULL)!=0){
    perror("Error en la creacion del hilo H1");
  }
  // Creacion del thread H2
  if(pthread_create(&H2, NULL, (void *)escribeImpares,NULL)!=0){
    perror("Error en la creacion del hilo H2");
  }

  // Joins de H1 y H2
  pthread_join(H1,NULL);
  pthread_join(H2,NULL);
  // Joins de los threads T
  for(i=0;i<M;i++){
    pthread_join(T[i],NULL);
  }

  // Creacion del thread R
  if(pthread_create(&R, NULL, (void*)ganador,NULL)!=0){
    perror("Error en la creacion del hilo 2");
  }
  //Join del thread R
  pthread_join(R,(void**) &winner);

  // Destruccion de los mutex
  for(i=0; i<M; i++){
    pthread_mutex_destroy(&mutex[i]);
  }
  pthread_mutex_destroy(&acabados);
  //Destruccion de la variable condicional
  pthread_cond_destroy(&procesando);

  //Muestra por pantalla las diferentes metricas de cada fila y el ganador
  for(i=0;i<M;i++){
    printf("Soy el %d\n",i );
    printf(" - %d\n",listaEstruc[i].NVP);
    printf(" - %f\n",listaEstruc[i].SM);
    printf("----------------------------------------------\n" );
  }
  printf("El ganador es %d\n",winner );

}
