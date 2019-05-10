#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include "constantes.h"

/* 										EXPLICACION:
	Cada jugador tiene un array de 16 posiciones, y cada posicion cuenta como una ficha.
	Dentro de cada posicion se haya un entero que identifica la posicion del tablera donde
	se encuentra dicha ficha.
	Si alguna de las posiciones del array vale -1 quiere decir que esa ficha ha sido comida.
*/


int movimientoBlancas();
int movimientoNegras();
void empezar_partida();
int comprobar_resultado();

// crear array de posiciones de tablero con fichas
int tablero[TAB];
int blancas[16];
int negras[16];
// creamos los jugadores (hilos)
pthread_t player1, player2;
// mutex
pthread_mutex_t mutex;

int main(){
	// creamos mutex
	if (pthread_mutex_init(&mutex, NULL) != 0)
		perror("mutex_init");
	// creamos thread del jugador 1 (blancas)
	if (pthread_create(&player1, NULL, &movimientoBlancas,NULL) != 0)
		perror("pthread_create");
	// creamos thread del jugador 2 (negras)
	if (pthread_create(&player2, NULL, &movimientoNegras, NULL) != 0)
		perror("pthread_create");

	int control_partida = 0; // controla que la partida sigue en juego si uno de los jugadores se queda sin fichas se pone a 1

	// hacemos un total de 100 partidas entre los dos jugadores (blancas y negras)
	for( int partidas=0; partidas < 100 ; partidas++ ){
		
		// empezamos la partida colocando las fichas en el tablero
		empezar_partida();
		while(control_partida == 0){

		}
	}

}

/*
	Funcion que realiza el movimiento de una ficha
*/
int movimientoBlancas(){
	int ficha; // ficha que va a mover el jugador (= posicion del array)
	ficha = rand () % (16-(0)+1) + 0; // cogemos una de las fichas aleatoriamente
	int mov; // posicion a la que se va a mover
	mov = rand () % (63-(0)+1) + 0;
	int result = 0;
	int i;
	// comprobamos si alguna de las fichas del jugador 1 esta en la posicion que hemos generado aleatoriamente
	for(i=0; i<16; i++){
		if(mov = blancas[i]){
			result = 1;
		}
	}
	// comprobamos si alguna de las fichas del jugador 2 esta en la posicion que hemos generado aleatoriamente
	for(i=0; i<16; i++){
		if(mov = negras[i]){
			result = 2;
		}
	}
	// depende del resultado obtenido elegimos una de las funciones
	switch(result){
		case 0: // posicion vacía, movemos la ficha
			blancas[ficha] = mov;
			break;
		case 1: // posicion ocupada, no hacemos nada
			break;
		case 2: // posicion con ficha rival, la comemos y ponemos valor -1 a la ficha del rival por ser comida
			for(int i=0; i<16; i++){
				if(mov = negras[i]){
					negras[i] = -1;
				}
			}
			break;
	}
}

int movimientoNegras(){
	int ficha; // ficha que va a mover el jugador (= posicion del array)
	ficha = rand () % (16-(0)+1) + 0; // cogemos una de las fichas aleatoriamente
	int mov; // posicion a la que se va a mover
	mov = rand () % (63-(0)+1) + 0;
	int result = 0;
	int i;
	// comprobamos si alguna de las fichas del jugador 1 esta en la posicion que hemos generado aleatoriamente
	for(i=0; i<16; i++){
		if(mov = negras[i]){
			result = 1;
		}
	}
	// comprobamos si alguna de las fichas del jugador 2 esta en la posicion que hemos generado aleatoriamente
	for(i=0; i<16; i++){
		if(mov = blancas[i]){
			result = 2;
		}
	}
	// depende del resultado obtenido elegimos una de las funciones
	switch(result){
		case 0: // posicion vacía, movemos la ficha
			negras[ficha] = mov;
			break;
		case 1: // posicion ocupada, no hacemos nada
			break;
		case 2: // posicion con ficha rival, la comemos y ponemos valor -1 a la ficha del rival por ser comida
			for(int i=0; i<16; i++){
				if(mov = blancas[i]){
					blancas[i] = -1;
				}
			}
			break;
	}
}

/*
	Funcion que coloca todas las fichas de los jugadores en sus posiciones iniciales
*/
void empezar_partida(){
	// 'colocamos' las fichas blancas
	for(int i=0; i<16; i++){
		blancas[i] = i;
	}
	// 'colocamos' las fichas negras
	for(int i= 48; i<64; i++){
		negras[i] = i;
	}
}

/*
	Comprobamos si alguno de los jugadores ya ha perdido todas las fichas
*/
int comprobar_resultado(int jugador[]){
	for(int i=0; i<16; i++){
		if(jugador[i] != -1){
			return 1;
		}
	}
	return 0;
}