////////////////////////////////
//  AUTOR: DIEGO GARCÍA COSÍO //
////////////////////////////////

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <float.h>
#include <sys/wait.h>
#include "datos.h"

//Declaraciones de las funciones programadas
void siguiente();
void fin();
void gestor();
void map();
void hijo();
void reduce();

// Declaracion de la pipe global para el apartado 4
int	pipe4[2];

/*
 * Funcion principal
 */
void main(){
  // Declaracion de la variable para el proceso hijo
  pid_t creado;
  srand(time(NULL));
  // Declaracion de variables utilizadas en el apartado 4, el proceso reduce
  float nMuestras = 0;
  float media = 0;
  float maximo = 0;
  float minimo = 0;
  // Creacion y comprobacion del proceso hijo
  if((creado = fork()) < 0){
    // Si hay error muestra el mensaje por el canal de error
    fprintf(stderr,"Error en la creacion del fork");
    exit(2);
  }
  // Ejecucion realizada por el padre
  if(creado > 0){
    // Inicializacion de las señales, para que cuando lleguen las diferentes señales
    // se ejecuten sus correspondientes funciones de manejo
    signal(SIGUSR1,siguiente);
    signal(SIGUSR2,fin);
    // Ejecucion del apartado 1, el proceso gestor
    gestor();
    // Ejecucion del apartado 2, el proceso map
    map();
    // Ejecucion del apartado 3, el proceso reduce
    reduce();
    // Apartado 4, uso de una pipe global para conectar el proceso principal y reduce
    // Cierro canal de escritura
    close(pipe4[1]);
    // Leo el numero de muestras
    read(pipe4[0], &nMuestras,sizeof(int));
    // Leo la media
    read(pipe4[0], &media,sizeof(int));
    // Leo el maximo alcanzado
    read(pipe4[0], &maximo,sizeof(int));
    // Leo el minimo alcanzado
    read(pipe4[0], &minimo,sizeof(int));
    // Cierro el canal de lectura
    close(pipe4[0]);
    // Muestra por pantalla los diferentes resultados
    printf("Numero de muestras: %10.3f\nMedia total: %14.3f\nMaximo alcanzado: %13.3f\nMinimo alcanzado: %13.3f\n",nMuestras,media,maximo,minimo);
  }else{
    // Ejecucion de la funcion hijo
    hijo();
    exit(0);
  }
  exit(0);
}

/*
 * Funcion gestor, correspondiente al apartado 1
 */
void gestor(){
  // Creacion e inicializacion de variables utilizadas durante la funcion
  int i = 0;
  int num;
  int contador = 0;
  FILE *file;
  char nombre[16];
  // Mientras no se haya producido la señal SIGUSR2
  while(flag2 == 0){
    // Avanzo el contador
    i++;
    // Creo el nombre del fichero a crear
    sprintf(nombre,"F%d.txt",i);
    // Creo un fichero con el nombre anteriormente definido
    file=fopen(nombre,"w");
    // Mientras no se haya producido la señal SIGUSR1
    while(flag1 == 0){
      // Creo un numero aleatorio entre M y -M
      num = rand() % (M-(-M)+1) + (-M);
      // Escribo ese numero en el fichero anteriormente creado
      fprintf(file, "%d\n",num );
      // Avanzo el contador del numero de datos introducidos en el fichero
      contador ++;
    }
    // Muestro informacion necesaria por pantalla
    printf("Generado el fichero %d con %d datos\n",i,contador);
    // Cierro el fichero
    fclose(file);
    // Restablezco variables para poder repetir la operacion
    flag1 = 0;
    contador = 0;
  }
}
/*
 * Funcion map, utilizada en el apartado 2
 */
void map(){
  // Declaracion e inicializacion de variables utilizadas en la funcion
  int i, dato, finalizados;
	int numDatos = 0;
	int suma = 0;
	float media = 0;
	int max = INT_MIN;
	int min = INT_MAX;
	char nombreFich[16];
	char nombreFichMap[16];
	FILE *file;
	pid_t map;
	int pipes[N][2];

  // Creo las N pipes necesarias y su correspondente hijo
  for (i = 0; i < N; i++) {
    if(pipe(pipes[i]) == 0){
      map = fork();
    }
    //Paro la ejecucion del bucle para los hijos
    if(map == 0){
      break;
    }
  }
  // Solo para el padre i llega a N, con lo que solo lo ejecuta el
  if(i == N){
    // Itero sobre cada pipe para escribir el nombre en la pipe de cada hijo
    for(i=0; i<N;i++){
      // Crea el nombre del fichero
      sprintf(nombreFich,"F%d.txt",i+1);
      // Cierra el canal de lectura
      close(pipes[i][0]);
      // Escribe en cada pipe el nombre del fichero correspondiente a cada hijo
      write(pipes[i][1], &nombreFich,sizeof(int));
      // Cierra el canal de escritura
      close(pipes[i][1]);
    }
  }
  // Esto solo lo ejecutan los hijos, que es donde crean el fichero y lo escriben
  if(i<N){
    // Cierra el canal de escritura
    close(pipes[i][1]);
    // Cada hijo lee el nombre del fichero
    read(pipes[i][0], &nombreFich,sizeof(int));
    // Cierra el canal de lectura
    close(pipes[i][0]);
    // Abre el fichero con el nombre leido en la pipe
    file = fopen(nombreFich, "r");
    // Mientras siga leyendo datos, va calculando
    while (fscanf(file, "%d", &dato) > 0) {
      if(dato > max){
        max = dato;
      }
      if(dato < min){
        min = dato;
      }
      suma = suma + dato;
      numDatos++;
    }
    // Calculo de la media de la suma
    media = (float)suma/numDatos;
    // Prepara el nombre del fichero que se va a crear
    sprintf(nombreFichMap,"MAP_%s",nombreFich);
    // Crea el fichero con el nombre creado previamente
    file = fopen(nombreFichMap, "w");
    // Escribe en el fichero los datos previamente calculados
    fprintf(file, "%d\n %f\n %d\n %d\n", numDatos, media, max, min);
    // Cierra el fichero
    fclose(file);
    exit(0);
  }
  // Ejecucion del padre
  if(map > 0){
    finalizados = 0;
    // El padre espera a que acaben sus N hijos
    while(finalizados<N){
      wait(NULL);
      finalizados++;
    }
    printf("Procesos map finalizados: %d\n", N);
  }
}

/*
 * Funcion reduce, utilizada en el apartado 3
 */
void reduce(){
  // Creacion e inicializacion de las variables utilizadas durante la funcion
  int i;
  int numDatos = 0;
  float suma = 0;
  float media = 0;
  float mediaTotal=0;
  int max = 0;
  int min = 0;
  float maxT = FLT_MIN;
  float minT = FLT_MAX;
  char nombreFich[16];
  FILE *file;
  // Creacion de la pipe global
  pipe(pipe4);
  // Creacion del hijo
  pid_t reduce;
  if((reduce = fork())<0){
    printf("Error al crear el proceso\n");
    exit(2);
  }
  // En esta funcion, el padre se queda esperando
  if(reduce > 0){
    wait(NULL);
  }else{
    // Lectura de todos los fichero generados en map
    for (i = 0; i < N; i++) {
      // Crea el nombre del fichero
      sprintf(nombreFich,"MAP_F%d.txt",i+1);
      // Abre el fichero
      file = fopen(nombreFich, "r");
      // Lee los datos del fichero
      fscanf(file, "%d %f %d %d", &numDatos, &media, &max, &min);
      // Calcula los resultados finales
      suma = suma + (float)numDatos;
      mediaTotal = mediaTotal+(media*(float)numDatos);
      if((float)max > maxT){
        maxT = (float)max;
      }
      if((float)min < minT){
        minT = (float)min;
      }
      // Cierra el fichero
      fclose(file);
    }
    // Calculo final de la media total
    mediaTotal = mediaTotal/suma;
    // Cierra el canal de lectura
    close(pipe4[0]);
    // Escribe el resultado de la suma en la pipe
    write(pipe4[1], &suma,sizeof(int));
    // Escribe el resultado de la media total en la pipe
    write(pipe4[1], &mediaTotal,sizeof(int));
    // Escribe el resultado del mayor maximo encontrado
    write(pipe4[1], &maxT,sizeof(int));
    // Escribe el resultado del menor minimo encontrado
    write(pipe4[1], &minT,sizeof(int));
    // Cierra el canal de escritura
    close(pipe4[1]);
    exit(0);
  }
}

/*
 * Funcion hijo utilizada en el apartado 1
 */
void hijo(){
  int milisegundos;
  for (int j = 0; j < N-1; j++) {
    milisegundos = rand() % (800-200+1)+200;
    //Espera de un numero aleatorio de milisegundos entre 200 y 800
    usleep(milisegundos*1000);
    kill(getppid(), SIGUSR1);
  }
  sleep(1);
  kill(getppid(),SIGUSR2);
}

/*
 * Funcion de manejo de la señal para el padre
 */
void siguiente(){
  printf("P: Fase1, trato SIGUSR1\n");
  flag1 = 1;
}

/*
 * Funcion de manejo de la señal para el hijo
 */
 void fin(){
  printf("P: Fase1, trato SIGUSR2\n");
  flag2 = 1;
  flag1 = 1;
}
