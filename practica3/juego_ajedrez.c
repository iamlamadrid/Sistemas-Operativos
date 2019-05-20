/* ************************************************************************************** */
/* ----------------------- ASIGNATURA: Sistemas Operativos (G660) ----------------------- */
/* ************************************************************************************** */
/* ---------------------------- AUTOR: ÁLvaro Lamadrid Agudo ---------------------------- */
/* ************************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "constantes.h"

// funciones utilizadas
void * movimiento_blancas(void *arg);
void * movimiento_negras(void *arg);
void empezar_partida();

int tablero[TAB]; // array de 64 posiciones del tablero donde se almacenan los datos:
				  // 0 si es una posicion libre, 1 si es una ficha blanca y 2 si es una ficha negra

pthread_mutex_t mutex; // mutex usado para dar orden a los turnos
pthread_cond_t turno; // variable condicional que establece el turno del jugador

int turno_jugador; // comprobacion del turno del jugador
int ganador=0; // variable para pasarle al thread principal quien ha sido el ganador (o empate) de cada partida

int num_blancas,num_negras; // contadores de las fichas que le quedan a cada jugador

/*
	Estructura con los datos de cada jugador, estos se componen de
	id: identificador de cada jugador
	color: char del color de las fichas de cada jugador 'b'(blanca) o 'n'(negra)
*/
typedef struct{	
	int id;
	char color;
}datos;

/*
	Estructura con los datos de los movimientos de cada jugador compuestos de:
	NUM_MOV: numero de movimientos realizados
	NUM_CAP: numero de fichas comidas
	NUM_MOV_TOT: contador numero de movimientos totales realizados
	NUM_CAP_TOT: contador numero de fichas totales comidas
*/
struct resultados{	
	int NUM_MOV;
	int NUM_CAP;	
	int NUM_MOV_TOT;
	int NUM_CAP_TOT;	
}results;

/*
	El main se compone de 4 partes principales:
		- comprobacion de parametros
		- inicializacion de datos y creacion del mutex y la variable condicional
		- jugar las partidas
		- finalizacion y calculo de resultdos
*/
void main(int argc, char * argn[]){
	pthread_t player1, player2;	// jugadores los cuales cada uno sera un thread
	int *puntosB, *puntosN; // puntos obtenidos de cada jugador
	int victorias_b, victorias_n,empates; // numero de victorias de cada jugaor y empates
	int partidas; // partidas que recibimos por parametro que se van a jugar
	int numero_partida = 0; // contador de partidas que se van mostrando por pantalla
	datos d1, d2; // estructuras de los datos de cada jugador

	// comporbamos si se ha pasado el numero correcto de parametros
	if(argc != 2){
		printf("se debe pasar el numero de partidas que se van a jugar \n");
		exit(1);
	}
	partidas=atoi(argn[1]); // cogemos el parametro como las partidas	
	
	// creamos mutex y comprobamos si hay algun error
	if(pthread_mutex_init(&mutex,NULL) != 0){
		printf("Error en la empezar_partidacion del mutex \n");
	}
	// creamos variable condicional y comprobamos si hay algun error
	if(pthread_cond_init(&turno,NULL) != 0){
		printf("Error en la empezar_partidacion de la condicion \n");
	}
	
	srand(time(NULL)); // función para que genere correctamente los numeros aleatorios
	
	/* inicializamos los datos */
	victorias_b=0; victorias_n=0;
	results.NUM_MOV_TOT=0; results.NUM_CAP_TOT=0;
	d1.id=1; d2.id=2;
	d1.color='b'; d2.color='n';
	
	/* En este bucle se juegan el total de las partidas que hemos pasado por parametro */
	for(int i=0;i<partidas;i++){
		empezar_partida();	// iniciamos el tablero
		
		// creamos los threads y comprobamos si hay algun error
		if(pthread_create(&player1,NULL,movimiento_blancas,&d1) != 0){
			printf("Error al crear el hilo 1 \n");
		}		
		if(pthread_create(&player2,NULL,movimiento_negras,&d2) != 0){
			printf("Error al crear el hilo 2 \n");
		}
		
		// hacemos los join para que los threads 'se esperen'
		if(pthread_join(player1,(void **)&puntosB) != 0){
			printf("Error al sincronizar el hilo 1 \n");
		}
		if(pthread_join(player2, (void **)&puntosN) != 0){
			printf("Error al sincronizar el hilo 2 \n");
		}
		numero_partida++; 

		// mostramos el ganadro dependiendo de quien haya sido segun la variable 'ganador'
		if(ganador == 1){		
			printf("Partida nº: %d | ID blanco: %d | ID negro: %d | Ganador(B/N/=): Blancas | Movimientos: %d \n",numero_partida, d1.id,d2.id,results.NUM_MOV);
			victorias_b++;
		}else if(ganador == 2){
			printf("Partida nº: %d | ID blanco: %d | ID negro: %d | Ganador(B/N/=): Negras  | Movimientos: %d \n",numero_partida, d1.id, d2.id,results.NUM_MOV);
			victorias_n++;
		}else if(ganador == 0){
			printf("Partida nº: %d | ID blanco: %d | ID negro: %d | Ganador(B/N/=): Empate  | Movimientos: %d \n",numero_partida, d1.id, d2.id, results.NUM_MOV);
		}
	}
	
	// finalizamos el mutex y la variable condicional
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&turno);
	
	empates=partidas-(victorias_b+victorias_n); // calculo de empates

	// mostramos datos finales
	printf("NP:%d B:%d N:%d T:%d PM:%f PC:%f \n",partidas,victorias_b, victorias_n,empates,(float)results.NUM_MOV_TOT/partidas,(float)results.NUM_CAP_TOT/partidas);
}

/* Funcion que hace que se mueva una ficha blanca tantas veces hasta ganar o hasta 120 movs */
void * movimiento_blancas (void *arg){
	int pts; // pts que le pasamos al hilo padre dependiendo de si hay victoria o empate
	
	// hacemos el numero d jugadas maximo que podemos hacer (120)
	for(int i=0;i<NUM_JUGADAS_MAX;i++){
		pthread_mutex_lock(&mutex);	// cogemos el mutex

		// si no es mi turno espero
		while(turno_jugador!=((datos*)arg)->id){	
				pthread_cond_wait(&turno,&mutex);
		}
		
		if(num_blancas>0){			// si todavia me quedan fichas juego

			int ficha =rand() % 64 ; // ficha del tablero que voy a mover
			while(tablero[ficha] != 1){	// calculo hasta que sea una ficha blanca
				ficha =rand() % 64 ;
			}
			int mov; // posicion a la que me voy a mover del tablero
			mov=rand() % 64;		

			switch(tablero[mov]){
				case 0: // ficha libre, me muevo actulizando las dos posiciones
					tablero[ficha]=0; 
					tablero[mov]=1;	
					break;
				case 1: // posicion ocupada por una ficha mia, no me muevo
					break;
				case 2: // posicion con ficha negra, la como
					num_negras--;
					// aumento el numero de piezas comidas
					results.NUM_CAP++;
					results.NUM_CAP_TOT++;
					// compruebo si ya he comido todas las negras
					if(num_negras==0){	
						turno_jugador=2;
						pthread_cond_signal(&turno); 
						pthread_mutex_unlock(&mutex);	
						pts=2;
						ganador = 1;
						pthread_exit(&pts);	
					}
					tablero[ficha]=0; 
					tablero[mov]=1;
					break;
			}
						
			// aumento el numero de movimiento
			results.NUM_MOV++;	
			results.NUM_MOV_TOT++;
			
			turno_jugador=2; // cambio de turno
			
			pthread_cond_signal(&turno); // activo el otro hilo (jugador) que estaba esperando mi turno
			pthread_mutex_unlock(&mutex); // libero el mutex
			
		}else{
			pthread_cond_signal(&turno); 
			pthread_mutex_unlock(&mutex);	
			pts=0; // empate
			pthread_exit(&pts); // retorno los puntos ganados	
		}
	}
	
	pts=1;
	ganador = 0;
	pthread_exit(&pts);	
}

/* Funcion que hace que se mueva una ficha blanca tantas veces hasta ganar o hasta 120 movs */
void * movimiento_negras (void *arg){
	int pts; // pts que le pasamos al hilo padre dependiendo de si hay victoria o empate
	
	// hacemos el numero d jugadas maximo que podemos hacer (120)
	for(int i=0;i<NUM_JUGADAS_MAX;i++){
		pthread_mutex_lock(&mutex);	// cogemos el mutex
		// si no es mi turno espero
		while(turno_jugador!=((datos*)arg)->id){	
			pthread_cond_wait(&turno,&mutex);
		}
		
		if(num_negras>0){			// si todavia me quedan fichas juego

			int ficha =rand() % 64 ; // ficha del tablero que voy a mover
			while(tablero[ficha] != 2){	// calculo hasta que sea una ficha negra
				ficha =rand() % 64 ;
			}
			int mov; // posicion a la que me voy a mover del tablero
			mov=rand() % 64;			
			
			switch(tablero[mov]){
				case 0: // ficha libre, me muevo actulizando las dos posiciones
					tablero[ficha]=0; 
					tablero[mov]=2;	
					break;
				case 1: // posicion con ficha negra, la como
					num_blancas--;
					// aumento el numero de piezas comidas
					results.NUM_CAP++;
					results.NUM_CAP_TOT++;
					// compruebo si ya he comido todas las negras
					if(num_blancas==0){	
						turno_jugador=1;
						pthread_cond_signal(&turno); 
						pthread_mutex_unlock(&mutex);	
						pts=2;
						ganador=2;
						pthread_exit(&pts);
					}
					tablero[ficha]=0; 
					tablero[mov]=2;	
					break;
				case 2: // posicion ocupada por una ficha mia, no me muevo
					break;
			}
			
			// aumento el numero de movimiento
			results.NUM_MOV++;	
			results.NUM_MOV_TOT++;
			
			turno_jugador=1; // cambio de turno	
			
			pthread_cond_signal(&turno); // activo el otro hilo (jugador) que estaba esperando mi turno
			pthread_mutex_unlock(&mutex); // libero el mutex
		}else{
			pthread_cond_signal(&turno); 
			pthread_mutex_unlock(&mutex);	
			pts=0; // empate
			pthread_exit(&pts); // retorno los puntos ganados	
		}
	}
	pts=1;
	ganador=0;
	pthread_exit(&pts);	
}	

/*
	Funcion que inicia el tablero colocando las fichas en su sitio (es decir, colocando
	ceros, unos y doses donde toquen en las posiciones del tablero(array)) e inicializando los
	debidos parametros
*/
void empezar_partida(){
	int i;
	// colocamos fichas blancas
	for(i=0; i<16; i++){
		tablero[i]=1;
	}
	// vaciamos las posiciones intermedias
	for(i=16; i<47; i++){
		tablero[i]=0;
	}
	// colocamos las fichas negras
	for(i=48; i<64; i++){
		tablero[i]=2;
	}
	
	turno_jugador=1; // hacemos que empiecen las blancas
	// actualizamos el recuento de fichas de cada jugador
	num_blancas=16; 
	num_negras=16;
	// iniciamos el numero de movimientos
	results.NUM_MOV=0; 
	results.NUM_CAP=0;
}